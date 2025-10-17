#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <qcontainerfwd.h>
#include <qicon.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/appIcons/AppIcon.png"));
  a.setApplicationName(QString::fromStdString("OpenMindBlocks"));
  a.setApplicationDisplayName(QString::fromStdString("OpenMindBlocks"));

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "frontend_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  MainWindow w;
  w.setWindowTitle(QString::fromStdString("Program Canvas"));
  w.show();
  return a.exec();
}
