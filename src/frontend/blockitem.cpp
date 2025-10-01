#include "blockitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

BlockItem::BlockItem(const QPixmap& skin, bool hasLeftKnob, bool hasRightKnob, QGraphicsItem* parent)
    : QGraphicsObject(parent), m_skin(skin)
{
    // Si no hay skin, define tamaño base; si hay, úsalo
    m_size = m_skin.isNull() ? QSizeF(160, 80) : m_skin.size();

    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setZValue(1.0);
}

BlockItem* BlockItem::leftmost() {
    BlockItem* n = this;
    // límite de seguridad para evitar bucles en desarrollo
    int guard = 0;
    while (n->m_left && guard++ < 1024) n = n->m_left;
    return n;
}

void BlockItem::setSkin(const QPixmap& px) {
    prepareGeometryChange();
    m_skin = px;
    if (!m_skin.isNull()) m_size = m_skin.size();
    update();
}

QRectF BlockItem::boundingRect() const {
    // cuerpo + margen para perilla lateral
    QRectF r(0, 0, m_size.width(), m_size.height());
    r.adjust(-m_radius*2, -2, m_radius*2, 2); // deja sobresalir la perilla
    return r;
}

QPainterPath BlockItem::shape() const {
    QPainterPath path;
    QRectF body(0, 0, m_size.width(), m_size.height());
    QPainterPath rectPath; rectPath.addRoundedRect(body, 16, 16);

    // Perilla lateral derecha (estética, como Scratch Jr)
    QPointF c(body.right() + m_radius, body.center().y());
    QPainterPath knob; knob.addEllipse(c, m_radius, m_radius);

    path = rectPath.united(knob);
    return path;
}

void BlockItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    p->setRenderHint(QPainter::Antialiasing, true);
    if (!m_skin.isNull()) {
        // Dibuja skin dentro del rectángulo del cuerpo
        p->drawPixmap(QRectF(0,0,m_size.width(),m_size.height()).toRect(), m_skin);
    } else {
        p->setBrush(QColor("#2ecc71"));
        p->setPen(Qt::NoPen);
        p->drawRoundedRect(QRectF(0,0,m_size.width(),m_size.height()),16,16);
        // Botón play decorativo (opcional)
        p->setBrush(QColor("#f1c40f"));
        p->drawEllipse(QPointF(m_size.width()*0.28, m_size.height()*0.5), 22, 22);
        p->setBrush(Qt::white);
        QPolygonF tri; tri<<QPointF(m_size.width()*0.26, m_size.height()*0.5-12)
            <<QPointF(m_size.width()*0.26, m_size.height()*0.5+12)
            <<QPointF(m_size.width()*0.26+18, m_size.height()*0.5);
        p->drawPolygon(tri);
    }

    // Opcional: guía de conectores (solo si seleccionado)
    if (isSelected()) {
        p->setPen(QPen(QColor(245,243,0,60), 1, Qt::DashLine));
        p->setBrush(Qt::NoBrush);
	if (this->hasLeftKnob == true){
			p->drawEllipse(leftConnector(), 3, 3);
	}
	if(this->hasRightKnob == true){
			p->drawEllipse(rightConnector(), 3, 3);
	}
    }
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

void BlockItem::attachRight(BlockItem* child) {
    if (!child || child == this) return;

    // evita ciclos
    for (BlockItem* n = this; n; n = n->m_right)
        if (n == child) return;

    // rompe enlaces previos
    if (m_right) m_right->m_left = nullptr;
    if (child->m_left) child->m_left->m_right = nullptr;

    m_right = child;
    child->m_left = this;

    const QPointF childLeftScene = child->mapToScene(child->leftConnector());
    const QPointF thisRightScene = this->mapToScene(this->rightConnector());
    const QPointF delta = (thisRightScene + QPointF(m_gap, 0)) - childLeftScene;
    child->moveBy(delta.x(), delta.y());
}

void BlockItem::detachRight() {
    if (!m_right) return;
    m_right->m_left = nullptr;
    m_right = nullptr;
}

void BlockItem::mousePressEvent(QGraphicsSceneMouseEvent* ev) {
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
    for (BlockItem* n = m_right; n; n = n->m_right)
        n->moveBy(delta.x(), delta.y());
}

void BlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent* ev) {
    QPointF delta = ev->scenePos() - ev->lastScenePos();
    // arrastra la cadena completa si hay hijos
BlockItem* root = leftmost();
root->moveChainBy(delta);

    // (opcional) previsualizar snap: elevar Z cuando hay candidato cerca
    BlockItem* candidate = findSnapCandidate();
    setZValue(candidate ? 3.0 : 2.0);

    QGraphicsObject::mouseMoveEvent(ev);
}

void BlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev) {
	setZValue(1.0);

    if (BlockItem* candidate = findSnapCandidate()) {
        // evita ciclos (no enganchar a un descendiente)
        for (BlockItem* cur = this; cur; cur = cur->m_right)
            if (cur == candidate) { candidate = nullptr; break; }

        // requisitos correctos de conectividad:
        if (candidate && candidate->hasRightKnob && this->hasLeftKnob)
            candidate->attachRight(this);
    }

    QGraphicsObject::mouseReleaseEvent(ev);
}

BlockItem* BlockItem::findSnapCandidate(qreal maxDistPx) const {
	if (!scene()) return nullptr;

    const QPointF myLeftScene = mapToScene(leftConnector());
    const QRectF probe(myLeftScene - QPointF(maxDistPx,maxDistPx),
                       QSizeF(maxDistPx*2, maxDistPx*2));

    BlockItem* best = nullptr;
    qreal bestD2 = maxDistPx*maxDistPx;

    for (QGraphicsItem* it : scene()->items(probe)) {
        if (it == this) continue;
        auto* blk = qgraphicsitem_cast<BlockItem*>(it);
        if (!blk) continue;

        // evita vecinos inmediatos
        if (blk == m_left || blk == m_right) continue;

        if (!blk->hasRightKnob) continue; // el candidato debe tener right knob

        const QPointF theirRightScene = blk->mapToScene(blk->rightConnector());
        const QPointF d = theirRightScene - myLeftScene;
        const qreal d2 = d.x()*d.x() + d.y()*d.y();
        if (d2 < bestD2) { bestD2 = d2; best = blk; }
    }
    return best;
}

QVariant BlockItem::itemChange(GraphicsItemChange change, const QVariant& v) {
    if (change == ItemSelectedChange) setZValue(2.0);
    if (change == ItemSelectedHasChanged && !isSelected()) setZValue(1.0);
    return QGraphicsObject::itemChange(change, v);
}
