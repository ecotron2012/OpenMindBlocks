#include "programcanvas.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/json_converter/jsonconverter.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QGraphicsScene>
#include <QMimeData>
#include <memory>
#include <qjsondocument.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpoint.h>
#include <qurl.h>
#include <utils/blockfactory.h>
#include <vector>
#include <components/http/httprequest.h>

using namespace std;

ProgramCanvas::ProgramCanvas(int width, int height, QWidget *parent)
    : QGraphicsView(parent), m_PieceSize(80), startingPiece(nullptr) {
  // Configurar la escena
  auto *scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, width, height);
  setScene(scene);

  // Opciones de vista
  setRenderHint(QPainter::Antialiasing);
  setAcceptDrops(true);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  viewport()->setAcceptDrops(true);
  // setDragMode(QGraphicsView::RubberBandDrag);
}

void ProgramCanvas::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);
  scene()->setSceneRect(QRectF(QPointF(0, 0), viewport()->size()));
}

void ProgramCanvas::addPiece(const QString &name, const QPoint &location) {
  if (!scene())
    return;

  // Aquí puedes usar tu BlockItem en lugar de un pixmap plano
  BlockItem* piece =
      BLOCK_FACTORY.at(name.toUtf8().constData())(QJsonObject{});
  piece->setFlags(QGraphicsItem::ItemIsMovable |
                  QGraphicsItem::ItemIsSelectable);
  scene()->addItem(piece);
  const QPointF targetScenePt = mapToScene(location);
  // Guardar referencia si es la primera pieza
  if (!startingPiece) {
    startingPiece = piece;
    lastPiece = piece;
    piece->setPos(targetScenePt);
  } else {
    QPointF scenePos = lastPiece->scenePos();
    piece->setPos(targetScenePt + scenePos);
    lastPiece->attachRight(piece);
    lastPiece = piece;
  }

  // Add BlockItem to pieces array
  this->pieces.push_back(piece);
  this->pieceAmount++;
}

void ProgramCanvas::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat(puzzleMimeType())) {
    event->acceptProposedAction();
  } else {
    event->ignore();
  }
}

void ProgramCanvas::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat(puzzleMimeType())) {
    event->acceptProposedAction();
  } else {
    event->ignore();
  }
}

void ProgramCanvas::dropEvent(QDropEvent *event) {
  if (!event->mimeData()->hasFormat(puzzleMimeType())) {
    event->ignore();
    return;
  }

  QByteArray itemData = event->mimeData()->data(puzzleMimeType());
  QDataStream dataStream(&itemData, QIODevice::ReadOnly);

  QPixmap pixmap;
  QPoint offset;
  QPoint position = QPoint(0, 250);
  QString name;
  dataStream >> pixmap >> offset >> name;

  qDebug() << "Position del evento: " << event->position().toPoint() << "Offset: " << offset;

  addPiece(name,
           // event->position().toPoint() - offset);
           position);

  event->acceptProposedAction();
}

// No lo necesitas si no implementas arrastrar desde la escena, pero lo dejo de
// placeholder
void ProgramCanvas::startDrag(Qt::DropActions supportedActions) {
  Q_UNUSED(supportedActions);
  qDebug() << "Start drag from ProgramCanvas (no implementado aún)";
}

void ProgramCanvas::deleteAt(int pos) {
  this->pieces.erase(this->pieces.begin() + pos);
  this->pieceAmount--;
  // update positions of the rest of the pieces
  for (BlockItem *block : this->pieces) {
    int position = block->getPosition();
    if (position >= pos) {
      block->updatePosition(position - 1);
    }
  }
}

void ProgramCanvas::runProgram() {
	HTTPRequest* req = new HTTPRequest(QUrl(QString::fromStdString("http://127.0.0.1:5000/execute")), this);
	JSONConverter* converter = JSONConverter::getInstance();
	QJsonObject programJson = converter->convertCodeToJSON(this->pieces);
	QJsonDocument doc(programJson);
	qDebug().noquote() << doc.toJson(QJsonDocument::Indented);
	req->postRequest(programJson);
}
