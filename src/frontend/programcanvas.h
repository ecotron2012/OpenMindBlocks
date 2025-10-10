#ifndef PROGRAMCANVAS_H
#define PROGRAMCANVAS_H

#include "components/programming_blocks/blockitem/blockitem.h"
#include <QGraphicsView>
#include <qevent.h>
#include <qgraphicsview.h>
#include <qobject.h>
#include <vector>
using namespace std;

class ProgramCanvas : public QGraphicsView {
  Q_OBJECT

public:
  explicit ProgramCanvas(int width, int height, QWidget *parent = nullptr);
  void addPiece(const QString &name, const QPoint &location);
  void deleteAt(int pos);
  void render();
  void runProgram();

  static QString puzzleMimeType() {
    return QStringLiteral("image/x-puzzle-piece");
  }

  static int getPieceAmount();
  static int getPieceSize();
  static BlockItem *getStartingPiece();
  static BlockItem *getLastPiece();

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void startDrag(Qt::DropActions supportedActions);
  void resizeEvent(QResizeEvent *event) override;

  int m_PieceSize;
  int pieceAmount = 0;
  BlockItem *startingPiece;
  BlockItem *lastPiece;
  vector<BlockItem *> pieces;

};

#endif
