#pragma once
#include <qlabel.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;
class PreviewBlockBase : public QWidget {
  Q_OBJECT
public:
  explicit PreviewBlockBase(const string &name, const QPixmap &image,
                            const QString &label, QWidget *parent = nullptr);
  string getName();
  QLabel *getLabel();
  QLabel *getImg();

protected:
  string name;
  QLabel *blockLabel;
  QLabel *blockImg;
};
