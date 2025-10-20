#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QProcess>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QTextStream>
#include <QThread>
#include <memory>

#if defined(Q_OS_WIN)
#include <windows.h>
static HANDLE g_job = NULL;

static void attachJobToProcess(qint64 pid) {
  if (!g_job) {
    g_job = CreateJobObjectW(NULL, NULL);
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info = {};
    info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    SetInformationJobObject(g_job, JobObjectExtendedLimitInformation, &info,
                            sizeof(info));
  }
  HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(pid));
  if (hProc) {
    AssignProcessToJobObject(g_job, hProc);
    CloseHandle(hProc);
  }
}
#endif

// ============= Utils =============

static QString exeDir() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return QCoreApplication::applicationDirPath();
#else
  return QCoreApplication::applicationDirPath();
#endif
}

static void sleepMs(int ms) { QThread::msleep(ms); }

static bool waitForPort(const QString &host, quint16 port, int timeoutMs) {
  QElapsedTimer t;
  t.start();
  while (t.elapsed() < timeoutMs) {
    QTcpSocket s;
    s.connectToHost(host, port);
    if (s.waitForConnected(400)) {
      s.close();
      return true;
    }
    sleepMs(200);
  }
  return false;
}

static QString timestamp() {
  return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

static QFile *openLogFile(const QString &baseName) {
  const QString logDir = exeDir() + QDir::separator() + "logs";
  QDir().mkpath(logDir);
  QString fn =
      QString("%1/%2_%3.log")
          .arg(logDir, baseName,
               QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
  QFile *f = new QFile(fn);
  if (f->open(QIODevice::WriteOnly | QIODevice::Text))
    return f;
  delete f;
  return nullptr;
}

static void writeLine(QFile *f, const QString &line) {
  if (!f)
    return;
  QTextStream ts(f);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  ts.setEncoding(QStringConverter::Utf8);
#else
  ts.setCodec("UTF-8");
#endif
  ts << "[" << timestamp() << "] " << line << "\n";
  ts.flush();
}

#ifdef Q_OS_WIN
constexpr const char* kBackendDefault = "backend.exe";
constexpr const char* kGuiDefault     = "frontend.exe";
#else
constexpr const char* kBackendDefault = "backend";
constexpr const char* kGuiDefault     = "frontend";
#endif

// ============= App Launcher =============

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("OpenMindBlocks Launcher");
  QCoreApplication::setOrganizationName("Cristobal Carreno");

  // Parámetros
  QCommandLineParser parser;
  parser.setApplicationDescription("Orquestador de Backend (Flask) + GUI (Qt)");
  parser.addHelpOption();

  QCommandLineOption hostOpt(
      QStringLiteral("backend-host"), QStringLiteral("Host del backend"),
      QStringLiteral("host"), QStringLiteral("127.0.0.1"));
  QCommandLineOption portOpt(QStringLiteral("backend-port"),
                             QStringLiteral("Puerto del backend"),
                             QStringLiteral("port"), QStringLiteral("5000"));
  QCommandLineOption startTimeoutOpt(
      QStringLiteral("start-timeout"),
      QStringLiteral("Timeout para que el backend escuche (ms)"),
      QStringLiteral("ms"), QStringLiteral("20000"));
  QCommandLineOption gracefulMsOpt(
      QStringLiteral("graceful-ms"),
      QStringLiteral("Tiempo de espera tras terminate() (ms)"),
      QStringLiteral("ms"), QStringLiteral("3000"));
  QCommandLineOption backendPathOpt(
      QStringLiteral("backend"), QStringLiteral("Nombre o ruta del backend"),
      QStringLiteral("path"), QString::fromLatin1(kBackendDefault));
  QCommandLineOption guiPathOpt(
      QStringLiteral("gui"), QStringLiteral("Nombre o ruta de la GUI"),
      QStringLiteral("path"), QString::fromLatin1(kGuiDefault));
  parser.addOption(hostOpt);
  parser.addOption(portOpt);
  parser.addOption(startTimeoutOpt);
  parser.addOption(gracefulMsOpt);
  parser.addOption(backendPathOpt);
  parser.addOption(guiPathOpt);

  parser.process(app);

  const QString host = parser.value(hostOpt);
  const quint16 port = parser.value(portOpt).toUShort();
  const int startTimeout = parser.value(startTimeoutOpt).toInt();
  const int gracefulMs = parser.value(gracefulMsOpt).toInt();
  QString backendProg = parser.value(backendPathOpt);
  QString guiProg = parser.value(guiPathOpt);

  if (QDir::isRelativePath(backendProg))
    backendProg = exeDir() + QDir::separator() + backendProg;
  if (QDir::isRelativePath(guiProg))
    guiProg = exeDir() + QDir::separator() + guiProg;

#ifdef Q_OS_WIN
  auto ensureExe = [](QString p) -> QString {
    if (!p.endsWith(".exe", Qt::CaseInsensitive)) {
      const QString withExe = p + ".exe";
      if (QFile::exists(withExe) && !QFile::exists(p))
        return withExe;
    }
    return p;
  };
  backendProg = ensureExe(backendProg);
  guiProg     = ensureExe(guiProg);
#endif

  // Logs
  std::unique_ptr<QFile> backendLog(openLogFile("backend"));
  std::unique_ptr<QFile> launcherLog(openLogFile("launcher"));
  writeLine(launcherLog.get(), "Launcher iniciado");
  writeLine(launcherLog.get(), "Usando backend: " + backendProg);
  writeLine(launcherLog.get(), "Usando GUI: " + guiProg);
  writeLine(launcherLog.get(),
            QString("Esperando backend en %1:%2").arg(host).arg(port));

  // ========== Inicia Backend ==========
  QProcess backend;
  backend.setProgram(backendProg);
  backend.setWorkingDirectory(exeDir());
  backend.setProcessChannelMode(
      QProcess::MergedChannels); 

#if defined(Q_OS_WIN)
  backend.setCreateProcessArgumentsModifier(
      [](QProcess::CreateProcessArguments *args) {
        args->flags |= CREATE_NO_WINDOW;
      });
#endif

  QObject::connect(&backend, &QProcess::readyReadStandardOutput, [&]() {
    const QByteArray data = backend.readAllStandardOutput();
    writeLine(backendLog.get(), QString::fromLocal8Bit(data));
  });

  backend.start();
#if defined(Q_OS_WIN)
  attachJobToProcess(backend.processId());
#endif
  if (!backend.waitForStarted(5000)) {
    writeLine(launcherLog.get(),
              "ERROR: backend no arrancó (timeout en waitForStarted).");
    return 1;
  }

  if (!waitForPort(host, port, startTimeout)) {
    writeLine(launcherLog.get(),
              "ERROR: backend no abrió el puerto a tiempo. Matando backend.");
    backend.kill();
    backend.waitForFinished(2000);
    return 2;
  }
  writeLine(launcherLog.get(), "Backend OK: puerto arriba.");

  // ========== Launch GUI ==========
  QProcess gui;
  gui.setProgram(guiProg);
  gui.setWorkingDirectory(exeDir());
  gui.setProcessChannelMode(QProcess::MergedChannels);

#if defined(Q_OS_WIN)
  gui.setCreateProcessArgumentsModifier(
      [](QProcess::CreateProcessArguments *args) {
        args->flags |= CREATE_NO_WINDOW;
      });
#endif

  gui.start();
  if (!gui.waitForStarted(5000)) {
    writeLine(launcherLog.get(), "ERROR: GUI no arrancó. Terminando backend.");
    backend.terminate();
    backend.waitForFinished(gracefulMs);
    if (backend.state() != QProcess::NotRunning)
      backend.kill();
    backend.waitForFinished(2000);
    return 3;
  }

  gui.waitForFinished(-1);
  writeLine(launcherLog.get(), "GUI finalizó. Cerrando backend...");

  // ========== Backend shutdown ==========

  // QProcess curl; curl.start("curl", QStringList() << "-s" << "-X" << "POST"
  //                                                 <<
  //                                                 QString("http://localhost:5000/shutdown").arg(host).arg(port));
  // curl.waitForFinished(1500);

  backend.terminate();
  if (backend.waitForFinished(gracefulMs)) {
    writeLine(launcherLog.get(), "Backend terminó con terminate().");
    return 0;
  }

#if defined(Q_OS_WIN)
  writeLine(launcherLog.get(), "Usando TerminateJobObject() para matar árbol.");
  if (g_job) {
    TerminateJobObject(g_job, 1);
    // esperar a que muera:
    backend.waitForFinished(2000);
  }
#endif

  if (backend.state() != QProcess::NotRunning) {
    writeLine(launcherLog.get(),
              "Backend aún vivo tras terminate(); enviando kill().");
    backend.kill(); 
    backend.waitForFinished(2000);
  }

  writeLine(launcherLog.get(), "Launcher terminado.");
  return 0;
}
