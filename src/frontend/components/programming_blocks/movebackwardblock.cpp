#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include "movebackwardblock.h"
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <qnamespace.h>
#include <qpixmap.h>

MoveBackwardBlock::MoveBackwardBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/move_backward.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, true, 0, "move_bwd",
                QJsonObject{{"params", QJsonObject{}}}, parent) {}
