#include "whileblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>
#include <QString>
#include <components/graphics/colorswatchdelegate.h>
#include <components/utils/prims.h>
#include <map>
#include <qbrush.h>
#include <qcontainerfwd.h>
#include <qgraphicsitem.h>
#include <qgridlayout.h>
#include <qicon.h>
#include <qjsonobject.h>
#include <qlist.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qoverload.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <string>

static const int cols[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

WhileBlock::WhileBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/while_block.png"), true, true, 0,
                "while_cond", QJsonObject{{"params", if_cond()}}, parent) {
  QJsonObject whileCondStatement = while_cond();
  QJsonObject whileCondParams = whileCondStatement["params"].toObject();
  QJsonObject condValue = n_times(1);
  whileCondParams["cond"] = condValue;
  whileCondStatement["params"] = whileCondParams;
  setParams(whileCondStatement);
  setFlag(ItemIsMovable, true);
  setFlag(ItemIsSelectable, true);
  setupCombo();
  ensureCombo();
  layoutOverlay();
}

void WhileBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *opt,
                       QWidget *w) {
  BlockItem::paint(p, opt, w);

  layoutOverlay();
}

void WhileBlock::setupCombo() {
  m_combo = new QComboBox();
  for (auto &nc : cols) {
    int idx = m_combo->count();
    m_combo->addItem(QString::fromStdString(to_string(nc)));
    m_combo->setItemData(idx, nc, Qt::UserRole);
    m_combo->setItemData(idx, QString::fromStdString(to_string(nc)),
                         Qt::ToolTipRole);
  }
  m_combo->setFixedHeight(30);
  m_combo->setMinimumWidth(92);
  m_combo->setStyleSheet(
      QString("QComboBox { font-size: 18px; }"
              "QComboBox QAbstractItemView { font-size: 18px; }"));

  m_comboProxy = new QGraphicsProxyWidget(this);
  m_comboProxy->setWidget(m_combo);
  m_comboProxy->setZValue(1);

  connect(m_combo, qOverload<int>(&QComboBox::currentIndexChanged), this,
          [this](int idx) {
            const QVariant v = m_combo->itemData(idx, Qt::UserRole);
            const int c = v.value<int>();

            qDebug() << "Numero seleccionado: " << c;
            m_times = c;
            QJsonObject whileCondStatement = while_cond();
            QJsonObject whileCondParams =
                whileCondStatement["params"].toObject();
            QJsonObject condValue = n_times(c);
            whileCondParams["cond"] = condValue;
            whileCondStatement["params"] = whileCondParams;
            qDebug() << whileCondParams;
            setParams(whileCondStatement);
            qDebug() << "Nuevos params" << params;

            update();
          });
}

void WhileBlock::ensureCombo() {
  if (m_comboProxy)
    return;
  for (auto &nc : cols) {
    int idx = m_combo->count();
    m_combo->addItem(QString::fromStdString(to_string(nc)));
    m_combo->setItemData(idx, nc, Qt::UserRole);
    m_combo->setItemData(idx, QString::fromStdString(to_string(nc)),
                         Qt::ToolTipRole);
  }
  m_combo->setFixedHeight(30);
  m_combo->setMinimumWidth(92);
  m_combo->setStyleSheet(
      QString("QComboBox { font-size: 18px; }"
              "QComboBox QAbstractItemView { font-size: 18px; }"));

  m_comboProxy = new QGraphicsProxyWidget(this);
  m_comboProxy->setWidget(m_combo);
  m_comboProxy->setZValue(1);

  connect(m_combo, qOverload<int>(&QComboBox::currentIndexChanged), this,
          [this](int idx) {
            const QVariant v = m_combo->itemData(idx, Qt::UserRole);
            const int c = v.value<int>();

            qDebug() << "Numero seleccionado: " << c;
            m_times = c;
            QJsonObject whileCondStatement = while_cond();
            QJsonObject whileCondParams =
                whileCondStatement["params"].toObject();
            QJsonObject condValue = n_times(c);
            whileCondParams["cond"] = condValue;
            whileCondStatement["params"] = whileCondParams;
            qDebug() << whileCondParams;
            setParams(whileCondStatement);
            qDebug() << "Nuevos params" << params;

            update();
          });
}

void WhileBlock::layoutOverlay() {
  const QRectF r = boundingRect();
  const QSize h = m_combo->sizeHint();
  const qreal pad = 12.0;

  const QPointF pos(r.right() - pad - h.width(),
                    r.top() + (r.height() - h.height()) / 2.0);

  m_comboProxy->setPos(pos + QPointF(-84, 37));
}
