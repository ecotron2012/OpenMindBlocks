#pragma once
#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;
class PreviewBlockBase : public QLabel {
  Q_OBJECT
public:
  explicit PreviewBlockBase(const string &name, const QPixmap &image,
                            QWidget *parent = nullptr);
  string getName();

protected:
  string name;
};
