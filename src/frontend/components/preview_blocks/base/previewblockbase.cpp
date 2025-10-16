#include "previewblockbase.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qwidget.h>

using namespace std;

PreviewBlockBase::PreviewBlockBase(const string &name, const QPixmap &image,
                                   const QString &label, QWidget *parent)
    : QWidget(parent) {
  this->name = name;
  this->blockImg = new QLabel();
  this->blockImg->setPixmap(
      image.scaledToHeight(160, Qt::SmoothTransformation));
  this->blockLabel = new QLabel();
  this->blockLabel->setText(label);
  this->blockLabel->setFont(QFont("Calibri", 15));
  this->blockLabel->setAlignment(Qt::AlignHCenter);
  QVBoxLayout *lyt = new QVBoxLayout(this);
  lyt->addWidget(this->blockImg);
  lyt->addWidget(this->blockLabel);
  lyt->setSpacing(0);
  this->blockLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
  this->blockImg->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

string PreviewBlockBase::getName() { return this->name; }

QLabel *PreviewBlockBase::getLabel() {
  QLabel *labelCopy = this->blockLabel;
  return labelCopy;
}

QLabel *PreviewBlockBase::getImg() { return this->blockImg; }
