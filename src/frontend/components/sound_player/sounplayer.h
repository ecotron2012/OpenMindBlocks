#include <QFile>
#include <QtMultimedia/qaudiooutput.h>
#include <QtMultimedia/qmediaplayer.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include <qurl.h>

using namespace std;
class SoundPlayer : public QMediaPlayer {
  Q_OBJECT
public:
  explicit SoundPlayer(QObject *parent = nullptr);
  explicit SoundPlayer(const QUrl &fileUrl, QObject *parent = nullptr);
  void setResource(const QString &rccPath, const QString &mime = QString());
  void setVolume(float vol);
  void playSound();

private:
  QAudioOutput *audioOutput;
  QFile *device = nullptr;
};
