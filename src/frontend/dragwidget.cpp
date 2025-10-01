#include "dragwidget.h"
#include "blockitem.h"
#include <QApplication>
#include <QDrag>
#include <QLabel>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <qnamespace.h>
DragWidget::DragWidget(QWidget *parent) : QFrame(parent) {
  setMinimumSize(200, 100);
  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
  setAcceptDrops(true);

  QLabel *boatIcon = new QLabel(this);
  boatIcon->setPixmap(QPixmap(":/blocks/start_program.png")
                          .scaledToHeight(80, Qt::SmoothTransformation));
  boatIcon->move(10, 10);
  boatIcon->show();
  boatIcon->setAttribute(Qt::WA_DeleteOnClose);

  QLabel *carIcon = new QLabel(this);
  carIcon->setPixmap(QPixmap(":/blocks/move_forward.png")
                         .scaledToHeight(80, Qt::SmoothTransformation));
  carIcon->move(100, 10);
  carIcon->show();
  carIcon->setAttribute(Qt::WA_DeleteOnClose);

  QLabel *houseIcon = new QLabel(this);
  houseIcon->setPixmap(QPixmap(":/blocks/move_backward.png")
                           .scaledToHeight(80, Qt::SmoothTransformation));
  houseIcon->move(190, 10);
  houseIcon->show();
  houseIcon->setAttribute(Qt::WA_DeleteOnClose);
}
void DragWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
    if (event->source() == this) {
      // event->setDropAction(Qt::MoveAction);
      // event->accept();
      event->ignore();

    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DragWidget::dropEvent(QDropEvent *event) {
  if (!event->mimeData()->hasFormat("application/x-dnditemdata")) {
    event->ignore();
    return;
  }
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->ignore();
      return;
    }
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    QLabel *newIcon = new QLabel(this);
    newIcon->setPixmap(pixmap);
    newIcon->move(event->position().toPoint() - offset);
    newIcon->show();
    newIcon->setAttribute(Qt::WA_DeleteOnClose);

    if (event->source() == this) {
      // event->setDropAction(Qt::MoveAction);
      // event->accept();
      event->ignore();
      return;
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}
void DragWidget::mousePressEvent(QMouseEvent *event) {
  //    QLabel *child =
  //    static_cast<QLabel*>(childAt(event->position().toPoint())); if (!child)
  //        return;
  //
  //    QPixmap pixmap = child->pixmap();
  //
  //    QByteArray itemData;
  //    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  //    dataStream << pixmap << QPoint(event->position().toPoint() -
  //    child->pos());
  // QMimeData *mimeData = new QMimeData;
  //    mimeData->setData("application/x-dnditemdata", itemData);QDrag *drag =
  //    new QDrag(this); drag->setMimeData(mimeData); drag->setPixmap(pixmap);
  //    drag->setHotSpot(event->position().toPoint() - child->pos());
  m_pressPos = event->position().toPoint(); // guarda punto inicial
  QFrame::mousePressEvent(event);
}
void DragWidget::mouseMoveEvent(QMouseEvent *event) {
  // inicia drag sólo si se superó el umbral
  if (!(event->buttons() & Qt::LeftButton))
    return;
  if ((event->position().toPoint() - m_pressPos).manhattanLength() <
      QApplication::startDragDistance())
    return;

  // encuentra el QLabel bajo el cursor
  QLabel *child = qobject_cast<QLabel *>(childAt(m_pressPos));
  if (!child || !child->pixmap())
    return;

  // OJO en Qt6: pixmap() devuelve const QPixmap*, hay que desreferenciar
  QPixmap pixmap = child->pixmap();

  // empaqueta datos (pixmap + offset)
  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  const QPoint offset = m_pressPos - child->pos();
  dataStream << pixmap << offset;

  auto *mimeData = new QMimeData;
  mimeData->setData("image/x-puzzle-piece", itemData);

  auto *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(offset);

  // ¡LANZA EL DRAG!
  Qt::DropAction dropAction = drag->exec(Qt::CopyAction);

  // si fue copia, muestra el original; si fue move interno, puedes borrarlo
  if (dropAction == Qt::MoveAction && drag->source() == this) {
    child->close(); // gracias a WA_DeleteOnClose, se destruye
  } else {
    child->show();
  }
}
