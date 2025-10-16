#include "ifcolorblock.h"
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

struct NamedColor {
  const char *name;
  QColor c;
};

static const NamedColor cols[] = {{"Rojo", Qt::red},
                                  {"Verde", Qt::green},
                                  {"Azul", Qt::blue},
                                  {"Amarillo", Qt::yellow},
                                  {"Negro", Qt::black}};

static const pmr::map<const QString, const QString> colorCodes = {
    {QString::fromStdString("#00ff00"), QString::fromStdString("green")},

    {QString::fromStdString("#ff0000"), QString::fromStdString("red")},

    {QString::fromStdString("#000000"), QString::fromStdString("black")},

    {QString::fromStdString("#0000ff"), QString::fromStdString("blue")},

    {QString::fromStdString("#ffff00"), QString::fromStdString("yellow")}

};

static QIcon makeSwatchIcon(const QColor &c, const QSize &sz = QSize(24, 24)) {
  QPixmap px(sz);
  px.fill(Qt::transparent);
  QPainter p(&px);
  p.setRenderHint(QPainter::Antialiasing, true);
  p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p.setBrush(c);
  p.drawRoundedRect(QRectF(1, 1, sz.width() - 2, sz.height() - 2), 4, 4);
  return QIcon(px);
}

IfColorBlock::IfColorBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/if_color_sensor.png"), true, true, 0,
                "if_color", QJsonObject{{"params", if_cond()}}, parent) {
  QJsonObject ifCondStatement = if_cond();
  QJsonObject ifCondParams = ifCondStatement["params"].toObject();
  QJsonObject condValue = color_sensor(QString::fromStdString("red"));
  ifCondParams["cond"] = condValue;
  ifCondStatement["params"] = ifCondParams;
  setParams(ifCondStatement);
  setFlag(ItemIsMovable, true);
  setFlag(ItemIsSelectable, true);
  setupCombo();
  ensureCombo();
  layoutOverlay();
}

void IfColorBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *opt,
                         QWidget *w) {
  BlockItem::paint(p, opt, w);

  layoutOverlay();
}

void IfColorBlock::setupCombo() {
  m_combo = new QComboBox();
  m_combo->setItemDelegate(new ColorSwatchDelegate(m_combo));
  for (auto &nc : cols) {
    QIcon ic = makeSwatchIcon(nc.c, QSize(24, 24));
    int idx = m_combo->count();
    m_combo->addItem(QString("■■■■■■■"));
    m_combo->setItemData(idx, nc.c, Qt::UserRole);
    m_combo->setItemData(idx, QString::fromLatin1(nc.name), Qt::ToolTipRole);
  }
  m_combo->setStyleSheet("QComboBox { color: red; }");
  m_combo->setFixedHeight(30);
  m_combo->setMinimumWidth(90);

  m_comboProxy = new QGraphicsProxyWidget(this);
  m_comboProxy->setWidget(m_combo);
  m_comboProxy->setZValue(1);

  connect(m_combo, qOverload<int>(&QComboBox::currentIndexChanged), this,
          [this](int idx) {
            const QVariant v = m_combo->itemData(idx, Qt::UserRole);
            const QColor c = v.value<QColor>();
            if (!c.isValid())
              return;

            qDebug() << "Nombre del color" << m_color.name();
            m_color = c;
            QJsonObject ifCondStatement = if_cond();
            QJsonObject ifCondParams = ifCondStatement["params"].toObject();
            QJsonObject condValue = color_sensor(colorCodes.at(c.name()));
            ifCondParams["cond"] = condValue;
            ifCondStatement["params"] = ifCondParams;
            qDebug() << ifCondParams;
            setParams(ifCondStatement);
            qDebug() << "Nuevos params" << params;

            const QString hex = c.name(QColor::HexRgb);
            m_combo->setStyleSheet(
                QString("QComboBox { color: %1; }"
                        "QComboBox QAbstractItemView { color: %1; }")
                    .arg(hex));

            update();
          });
}

void IfColorBlock::ensureCombo() {
  if (m_comboProxy)
    return;
  m_combo->setItemDelegate(new ColorSwatchDelegate(m_combo));
  for (auto &nc : cols) {
    QIcon ic = makeSwatchIcon(nc.c, QSize(24, 24));
    int idx = m_combo->count();
    m_combo->addItem(QString("■■■■■■■"));
    m_combo->setItemData(idx, nc.c, Qt::UserRole);
    m_combo->setItemData(idx, QString::fromLatin1(nc.name), Qt::ToolTipRole);
  }
  m_combo->setStyleSheet("QComboBox { color: red; }");
  m_combo->setFixedHeight(30);
  m_combo->setMinimumWidth(90);

  m_comboProxy = new QGraphicsProxyWidget(this);
  m_comboProxy->setWidget(m_combo);
  m_comboProxy->setZValue(1);

  connect(m_combo, qOverload<int>(&QComboBox::currentIndexChanged), this,
          [this](int idx) {
            const QVariant v = m_combo->itemData(idx, Qt::UserRole);
            const QColor c = v.value<QColor>();
            if (!c.isValid())
              return;

            m_color = c;

            const QString hex = c.name(QColor::HexRgb);
            m_combo->setStyleSheet(
                QString("QComboBox { color: %1; }"
                        "QComboBox QAbstractItemView { color: %1; }")
                    .arg(hex));

            update();
          });
}

void IfColorBlock::layoutOverlay() {
  const QRectF r = boundingRect();
  const QSize h = m_combo->sizeHint();
  const qreal pad = 12.0;

  const QPointF pos(r.right() - pad - h.width(),
                    r.top() + (r.height() - h.height()) / 2.0);

  m_comboProxy->setPos(pos + QPointF(-48, 33));
}

void IfColorBlock::setColorFromName(const QString &name) {
  QColor c = Qt::red;
  if (name.compare("Verde", Qt::CaseInsensitive) == 0)
    c = Qt::green;
  else if (name.compare("Azul", Qt::CaseInsensitive) == 0)
    c = Qt::blue;
  else if (name.compare("Amarillo", Qt::CaseInsensitive) == 0)
    c = Qt::yellow;
  else if (name.compare("Negro", Qt::CaseInsensitive) == 0)
    c = Qt::black;

  if (c != m_color) {
    m_color = c;
    update();
    emit colorChanged(m_color);
  }
}
