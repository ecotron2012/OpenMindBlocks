#include "sounplayer.h"
#include <QDebug>
#include <QMimeDatabase>
#include <QtMultimedia/qaudiooutput.h>
#include <QtMultimedia/qmediaplayer.h>
#include <qanystringview.h>
#include <qobject.h>
#include <qurl.h>

SoundPlayer::SoundPlayer(QObject *parent)
    : QMediaPlayer(parent), audioOutput(new QAudioOutput(this)) {
  setAudioOutput(audioOutput);
  audioOutput->setVolume(0.8);
}

SoundPlayer::SoundPlayer(const QUrl &fileUrl, QObject *parent)
    : SoundPlayer(parent) {
  setSource(fileUrl);
}

void SoundPlayer::setVolume(float vol) { audioOutput->setVolume(vol); }

void SoundPlayer::setResource(const QString &rccPath, const QString &mime) {
  // cierra/elimina el dispositivo previo si existiera
  if (device) {
    if (device->isOpen())
      device->close();
    device->deleteLater();
    device = nullptr;
  }

  device = new QFile(rccPath, this); // aquí sí se usa ":/..."
  if (!device->open(QIODevice::ReadOnly)) {
    qWarning() << "No se pudo abrir recurso" << rccPath;
    device->deleteLater();
    device = nullptr;
    return;
  }

  QString mt = mime;
  if (mt.isEmpty()) {
    QMimeDatabase db;
    mt = db.mimeTypeForFile(rccPath).name(); // p.ej. "audio/mpeg"
  }

  // QUrl vacío para evitar interpretar un "protocolo"
  setSourceDevice(device, QUrl());
}

void SoundPlayer::playSound() { play(); }
