#include "ifcolorwidget.h"
#include "components/programming_blocks/ifcolorblock.h"
#include <QComboBox>
#include <QGraphicsWidget>
#include <components/graphics/colorcombo.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qgraphicswidget.h>
#include <qgridlayout.h>
#include <qitemselectionmodel.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qwidget.h>

IfColorWidget::IfColorWidget(QWidget *parent) : QWidget(parent) {
  QGridLayout *lyt = new QGridLayout(this);
  this->ifBlock = new IfColorBlock();
  this->colorList = createColorCombo(this);

  auto *scene = new QGraphicsScene(this);
  auto blockWidget = qgraphicsitem_cast<QGraphicsWidget *>(this->ifBlock);

  auto *view = new QGraphicsView(scene, this);
  view->setRenderHint(QPainter::Antialiasing, true);

  lyt->addWidget(view, 0, 0, Qt::AlignCenter);
  lyt->addWidget(this->colorList, 0, 1, Qt::AlignCenter);
}
