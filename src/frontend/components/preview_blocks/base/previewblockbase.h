#pragma once
#include <qlabel.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>

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
