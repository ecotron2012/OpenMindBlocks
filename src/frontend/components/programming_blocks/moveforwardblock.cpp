#include "moveforwardblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>

MoveForwardBlock::MoveForwardBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/move_forward.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, true, 0, "move_fwd", QJsonObject{{"params", QJsonObject{}}},
                parent) {}
