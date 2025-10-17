#include "components/programming_blocks/turnleftblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <qnamespace.h>
#include <qpixmap.h>

TurnLeftBlock::TurnLeftBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/turn_left.png"), true, true, 0,
                "turn_left", QJsonObject{{"params", QJsonObject{}}}, parent) {}
