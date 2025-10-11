#include "previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>
#include <qwidget.h>

using namespace std;

PreviewBlockBase::PreviewBlockBase(const string &name, const QPixmap &image,
                                   QWidget *parent) : QLabel(parent) {
  this->name = name;
  this->setPixmap(image);
}

string PreviewBlockBase::getName() { return this->name; }
