#include "dragwidget.h"
#include "../preview_blocks/movebwdprev.h"
#include "../preview_blocks/movefwdprev.h"
#include "../preview_blocks/startprogramprev.h"
#include "../preview_blocks/stopprogramprev.h"
#include "components/preview_blocks/base/previewblockbase.h"
#include <components/preview_blocks/turnleftprev.h>
#include <components/preview_blocks/turnrightprev.h>
#include <QApplication>
#include <QDrag>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QVBoxLayout>
#include <QWidget>
#include <qnamespace.h>
#include <qobject.h>
#include <qpixmap.h>
using namespace std;

DragWidget::DragWidget(QWidget *parent) : QFrame(parent) {
  setMinimumSize(200, 180);
  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

  StartProgramPrev *startProgram = new StartProgramPrev(this);
  startProgram->move(10, 10);
  startProgram->show();
  startProgram->setAttribute(Qt::WA_DeleteOnClose);

  MoveFwdPrev *moveForward = new MoveFwdPrev(this);
  moveForward->move(180, 10);
  moveForward->show();
  moveForward->setAttribute(Qt::WA_DeleteOnClose);

  MoveBwdPrev *moveBackward = new MoveBwdPrev(this);
  moveBackward->move(350, 10);
  moveBackward->show();
  moveBackward->setAttribute(Qt::WA_DeleteOnClose);

  StopProgramPrev *stopBlock = new StopProgramPrev(this);
  stopBlock->move(520, 10);
  stopBlock->show();
  stopBlock->setAttribute(Qt::WA_DeleteOnClose);

  TurnLeftPrev *turnLeft = new TurnLeftPrev(this);
  turnLeft->move(690, 10);
  turnLeft->show();
  turnLeft->setAttribute(Qt::WA_DeleteOnClose);

  TurnRightPrev *turnRight = new TurnRightPrev(this);
  turnRight->move(860, 10);
  turnRight->show();
  turnRight->setAttribute(Qt::WA_DeleteOnClose);
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
  PreviewBlockBase *child = qobject_cast<PreviewBlockBase *>(childAt(m_pressPos));
  if (!child || !child->pixmap())
    return;

  // OJO en Qt6: pixmap() devuelve const QPixmap*, hay que desreferenciar
  QPixmap pixmap = child->pixmap();
  QString name = QString::fromStdString(child->getName());

  // empaqueta datos (pixmap + offset)
  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  const QPoint offset = m_pressPos - child->pos();
  dataStream << pixmap << offset << name;

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
