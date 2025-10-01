#include "programcanvas.h"
#include "blockitem.h"
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

ProgramCanvas::ProgramCanvas(int width, int height, QWidget *parent)
    : QGraphicsView(parent), m_PieceSize(80), startingPiece(nullptr)
{
    // Configurar la escena
    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width, height);
    setScene(scene);

    // Opciones de vista
    setRenderHint(QPainter::Antialiasing);
    setAcceptDrops(true);              // 👈 importante
    viewport()->setAcceptDrops(true);  // 👈 por si acaso
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void ProgramCanvas::addPiece(const QPixmap &pixmap, const QPoint &location)
{
    if (!scene()) return;

    // Aquí puedes usar tu BlockItem en lugar de un pixmap plano
    BlockItem *piece = new BlockItem(pixmap, true, true);
    piece->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    piece->setPos(location);
    scene()->addItem(piece);

    // Guardar referencia si es la primera pieza
    if (!startingPiece) {
        startingPiece = piece;
    }
}

void ProgramCanvas::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(puzzleMimeType())) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void ProgramCanvas::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(puzzleMimeType())) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void ProgramCanvas::dropEvent(QDropEvent *event)
{
    if (!event->mimeData()->hasFormat(puzzleMimeType())) {
        event->ignore();
        return;
    }

    QByteArray itemData = event->mimeData()->data(puzzleMimeType());
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    addPiece(pixmap, event->position().toPoint() - offset);

    event->acceptProposedAction();
}

// No lo necesitas si no implementas arrastrar desde la escena, pero lo dejo de placeholder
void ProgramCanvas::startDrag(Qt::DropActions supportedActions)
{
    Q_UNUSED(supportedActions);
    qDebug() << "Start drag from ProgramCanvas (no implementado aún)";
}
