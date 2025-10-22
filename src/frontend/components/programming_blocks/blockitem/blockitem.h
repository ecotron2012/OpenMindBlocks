#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <QGraphicsObject>
#include <QJsonObject>
#include <QPointer>
#include <qevent.h>
#include <qobject.h>
#include <memory_resource> 

using namespace std;
class BlockItem : public QGraphicsObject {
  Q_OBJECT
public:
  explicit BlockItem(const QPixmap &skin, bool hasLeftKnob, bool hasRightKnob,
                     int position, string name, QJsonObject params, QGraphicsItem *parent = nullptr);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *p, const QStyleOptionGraphicsItem *opt,
             QWidget *w) override;

  // Encadenamiento vertical
  BlockItem *left() const { return m_left; }
  BlockItem *right() const { return m_right; }
  void attachRight(BlockItem *child); // conecta this → child
  void detachRight();                 // rompe conexión con el de abajo
  bool isFullyBridged() const {
    return (hasLeftKnob ? (m_left != nullptr) : true) &&
           (hasRightKnob ? (m_right != nullptr) : true);
  }

  // Conectores (en coords locales)
  QPointF rightConnector() const; // donde se engancha otro por arriba
  QPointF leftConnector() const;  // para engancharse debajo de otro

  // Apariencia
  void setSkin(const QPixmap &px);
  int getPosition();
  void updatePosition(int pos);
  string getName();
  QJsonObject getParams();

protected:
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;
  void setParams(QJsonObject &p);
  int position;
  string name;
  QJsonObject params;

private:
  // búsqueda de candidato para snap
  BlockItem *findSnapCandidate(qreal maxDistPx = 18.0) const;
  void
  moveChainBy(QPointF delta); // mueve este bloque y todo lo que tenga debajo
  void updateChainZ(qreal baseZ);
  BlockItem *leftmost();
  void checkCollision();
  QPixmap m_skin;
  QSizeF m_size;         // tamaño de “cuerpo” rectangular del bloque
  qreal m_radius = 12.0; // radio de la perilla lateral (solo visual)
  qreal m_gap = 6.0;     // separación vertical entre bloques encajados

  bool hasLeftKnob;
  bool hasRightKnob;
  bool m_previewSnap = false; // verde mientras hay candidato cerca

  QPointer<BlockItem> m_left;
  QPointer<BlockItem> m_right;

  QPointF m_dragStartScene;
  QPointF m_grabOffset;
};

#endif // BLOCKITEM_H
