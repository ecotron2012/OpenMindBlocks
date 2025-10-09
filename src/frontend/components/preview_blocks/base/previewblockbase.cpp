#include "previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

PreviewBlockBase::PreviewBlockBase(const string &name, const QPixmap &image,
                                   QWidget *parent) : QLabel(parent) {
  this->name = name;
  this->setPixmap(image);
}

string PreviewBlockBase::getName() { return this->name; }
