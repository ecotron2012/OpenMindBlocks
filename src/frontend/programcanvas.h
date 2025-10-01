#ifndef PROGRAMCANVAS_H
#define PROGRAMCANVAS_H

#include "blockitem.h"
#include <QGraphicsView>
#include <qgraphicsview.h>

class ProgramCanvas : public QGraphicsView {
  Q_OBJECT

public:
  explicit ProgramCanvas(int width, int height, QWidget *parent = nullptr);
  void addPiece(const QPixmap &pixmap, const QPoint &location);

  static QString puzzleMimeType() {
    return QStringLiteral("image/x-puzzle-piece");
  }

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void startDrag(Qt::DropActions supportedActions);

  int m_PieceSize;
  BlockItem *startingPiece;
};

#endif
