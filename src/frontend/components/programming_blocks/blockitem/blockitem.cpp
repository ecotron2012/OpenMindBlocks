#include "blockitem.h"
#include <QApplication>
#include <QDrag>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QJsonObject>
#include <QLabel>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpixmap.h>
BlockItem::BlockItem(const QPixmap &skin, bool hasLeftKnob, bool hasRightKnob,
                     int position, string name, QJsonObject params,
                     QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_skin(skin.scaledToHeight(160, Qt::SmoothTransformation)) {
  // Si no hay skin, define tamaño base; si hay, úsalo
  m_size = m_skin.isNull() ? QSizeF(160, 80) : m_skin.size();

  this->position = position;
  this->name = name;
  this->params = params;

  setFlags(ItemIsSelectable | ItemSendsGeometryChanges);
  setAcceptHoverEvents(true);
  setZValue(1.0);
}

BlockItem *BlockItem::leftmost() {
  BlockItem *n = this;
  // límite de seguridad para evitar bucles en desarrollo
  int guard = 0;
  while (n->m_left && guard++ < 1024)
    n = n->m_left;
  return n;
}

void BlockItem::setSkin(const QPixmap &px) {
  prepareGeometryChange();
  m_skin = px;
  if (!m_skin.isNull())
    m_size = m_skin.size();
  update();
}

QRectF BlockItem::boundingRect() const {
  // cuerpo + margen para perilla lateral
  QRectF r(0, 0, m_size.width(), m_size.height());
  r.adjust(-m_radius * 2, -2, m_radius * 2, 2); // deja sobresalir la perilla
  return r;
}

QPainterPath BlockItem::shape() const {
  QPainterPath path;
  QRectF body(0, 0, m_size.width(), m_size.height());
  QPainterPath rectPath;
  rectPath.addRoundedRect(body, 16, 16);

  // Perilla lateral derecha (estética, como Scratch Jr)
  QPointF c(body.right() + m_radius, body.center().y());
  QPainterPath knob;
  knob.addEllipse(c, m_radius, m_radius);

  path = rectPath.united(knob);
  return path;
}

void BlockItem::paint(QPainter *p, const QStyleOptionGraphicsItem *,
                      QWidget *) {
  p->setRenderHint(QPainter::Antialiasing, true);

  // 1) Dibuja la piel o el bloque base
  if (!m_skin.isNull()) {
    p->drawPixmap(QRectF(0, 0, m_size.width(), m_size.height()).toRect(),
                  m_skin);
  } else {
    p->setBrush(QColor("#2ecc71"));
    p->setPen(Qt::NoPen);
    p->drawRoundedRect(QRectF(0, 0, m_size.width(), m_size.height()), 16, 16);
    // ... (decorativo opcional)
  }

  // 2) Overlay de estado (rojo si separada, verde si unida o si hay
  // previewSnap)
  // Use for debug purposes
  // const bool ok = isFullyBridged() || m_previewSnap;
  //
  // const QColor stroke = ok ? QColor(0, 180, 0, 220) : QColor(200, 0, 0, 220);
  // const QColor fill = ok ? QColor(0, 180, 0, 40) : QColor(200, 0, 0, 40);
  //
  // // mismo contorno que el cuerpo (sin las perillas), para que se vea “por
  // // encima”
  // QRectF body(0, 0, m_size.width(), m_size.height());
  // body.adjust(1, 1, -1, -1); // margen visual
  //
  // p->setPen(QPen(stroke, 3));
  // p->setBrush(fill);
  // p->drawRoundedRect(body, 12, 12);
  //
  // // (opcional) guías de conectores cuando está seleccionado
  // if (isSelected()) {
  //   p->setPen(QPen(QColor(245, 243, 0, 120), 1, Qt::DashLine));
  //   p->setBrush(Qt::NoBrush);
  //   if (hasLeftKnob)
  //     p->drawEllipse(leftConnector(), 10, 10);
  //   if (hasRightKnob)
  //     p->drawEllipse(rightConnector(), 10, 10);
  // }
}

// Conectores tipo Scratch Jr.: centrados, arriba/abajo
QPointF BlockItem::leftConnector() const {
  const qreal extra = hasLeftKnob ? m_radius : 0.0;
  return QPointF(-2, m_size.height() * 0.5);
}
QPointF BlockItem::rightConnector() const {
  const qreal extra = hasRightKnob ? m_radius : 0.0;
  return QPointF(m_size.width(), m_size.height() * 0.5);
}

void BlockItem::attachRight(BlockItem *child) {
  if (!child || child == this)
    return;
  for (BlockItem *n = this; n; n = n->m_right)
    if (n == child)
      return;

  if (m_right) {
    m_right->m_left = nullptr;
    m_right->update();
  }
  if (child->m_left) {
    child->m_left->m_right = nullptr;
    child->m_left->update();
  }

  m_right = child;
  child->m_left = this;

  // alinear
  const QPointF childLeftScene = child->mapToScene(child->leftConnector());
  const QPointF thisRightScene = this->mapToScene(this->rightConnector());
  const QPointF delta =
      (thisRightScene /*+ QPointF(m_gap, 0)*/) - childLeftScene;
  child->moveBy(delta.x() - 45, delta.y());

  // repintar ambos por cambio de estado
  this->update();
  child->update();
}

void BlockItem::detachRight() {
  if (!m_right)
    return;
  m_right->m_left = nullptr;
  m_right->update();
  m_right = nullptr;
  this->update();
}

void BlockItem::mousePressEvent(QGraphicsSceneMouseEvent *ev) {
  m_dragStartScene = ev->scenePos();
  m_grabOffset = ev->pos();
  // Si este bloque estaba en medio de una cadena y se toma por el medio,
  // puedes decidir cortar la cadena aquí. Por ahora, si arrastras el “padre”,
  // arrastra su cadena completa.
  QGraphicsObject::mousePressEvent(ev);
}

void BlockItem::moveChainBy(QPointF delta) {
  // mueve this y recorre hacia abajo
  this->moveBy(delta.x(), delta.y());
  for (BlockItem *n = m_right; n; n = n->m_right)
    n->moveBy(delta.x(), delta.y());
}

void BlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent *ev) {
  const QPointF delta = ev->scenePos() - ev->lastScenePos();

  // mover SIEMPRE desde el nodo raíz
  BlockItem *root = leftmost();
  // root->moveChainBy(delta);

  // preview verde si hay candidato cerca
  BlockItem *candidate = findSnapCandidate();
  const bool preview = (candidate != nullptr);

  if (m_previewSnap != preview) {
    m_previewSnap = preview;
    update(); // repinta para cambiar de rojo↔verde
  }

  setZValue(preview ? 3.0 : 2.0);
  QGraphicsObject::mouseMoveEvent(ev);
}

void BlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev) {
  setZValue(1.0);

  BlockItem *candidate = findSnapCandidate();
  if (candidate) {
    // evita ciclos
    for (BlockItem *cur = this; cur; cur = cur->m_right)
      if (cur == candidate) {
        candidate = nullptr;
        break;
      }

    // if (candidate && candidate->hasRightKnob && this->hasLeftKnob)
    //     candidate->attachRight(this);
  }

  // apaga el preview y repinta
  if (m_previewSnap) {
    m_previewSnap = false;
    update();
  }

  // tras conectar/desconectar, actualiza también vecinos para que cambie su
  // color
  if (m_left)
    m_left->update();
  if (m_right)
    m_right->update();

  QGraphicsObject::mouseReleaseEvent(ev);
}
void BlockItem::dropEvent(QGraphicsSceneDragDropEvent *ev) {
  if (!ev->mimeData()->hasFormat("application/x-dnditemdata")) {
    ev->ignore();
    return;
  }

  QByteArray itemData = ev->mimeData()->data("application/x-dnditemdata");
  QDataStream dataStream(&itemData, QIODevice::ReadOnly);

  QPixmap px;
  QPoint offset;
  dataStream >> px >> offset;

  // QGraphicsPixmapItem *it = QPixmap>addPixmap(px);
  // it->setFlags(QGraphicsItem::ItemIsMovable |
  // QGraphicsItem::ItemIsSelectable); it->setPos(ev->scenePos() -
  // QPointF(offset));  // posición soltada ev->setDropAction(Qt::CopyAction);
  // ev->accept();
}
BlockItem *BlockItem::findSnapCandidate(qreal maxDistPx) const {
  if (!scene())
    return nullptr;

  const QPointF myLeftScene = mapToScene(leftConnector());
  const QRectF probe(myLeftScene - QPointF(maxDistPx, maxDistPx),
                     QSizeF(maxDistPx * 2, maxDistPx * 2));

  BlockItem *best = nullptr;
  qreal bestD2 = maxDistPx * maxDistPx;

  for (QGraphicsItem *it : scene()->items(probe)) {
    if (it == this)
      continue;
    auto *blk = qgraphicsitem_cast<BlockItem *>(it);
    if (!blk)
      continue;

    // evita vecinos inmediatos
    if (blk == m_left || blk == m_right)
      continue;

    if (!blk->hasRightKnob)
      continue; // el candidato debe tener right knob
    if (this->collidesWithItem(blk)) {
      best = blk;
      break;
    }
  }
  return best;
}

QVariant BlockItem::itemChange(GraphicsItemChange change, const QVariant &v) {
  if (change == ItemSelectedChange)
    setZValue(2.0);
  if (change == ItemSelectedHasChanged && !isSelected())
    setZValue(1.0);
  return QGraphicsObject::itemChange(change, v);
}

void BlockItem::checkCollision() {
  // if (!scene()) return nullptr;
  //
  //    const QPointF myLeftScene = mapToScene(leftConnector());
  //    const QRectF probe(myLeftScene - QPointF(maxDistPx,maxDistPx),
  //                       QSizeF(maxDistPx*2, maxDistPx*2));
  //
  //    BlockItem* best = nullptr;
  //    qreal bestD2 = maxDistPx*maxDistPx;
  //
  //    for (QGraphicsItem* it : scene()->items(probe)) {
  //        if (it == this) continue;
  //        auto* blk = qgraphicsitem_cast<BlockItem*>(it);
  //        if (!blk) continue;
  //
  //        // evita vecinos inmediatos
  //        if (blk == m_left || blk == m_right) continue;
  //
  //        if (!blk->hasRightKnob) continue; // el candidato debe tener right
  //        knob if (this->collidesWithItem(blk)) { best = blk; break; }
  //    }
  //    return best;
  //
}

int BlockItem::getPosition() { return this->position; }

void BlockItem::updatePosition(int pos) { this->position = pos; }

string BlockItem::getName() { return this->name; }

QJsonObject BlockItem::getParams() { return this->params; }

void BlockItem::setParams(QJsonObject &p) { this->params = p; }
