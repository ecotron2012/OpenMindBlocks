#include "components/programming_blocks/turnrightblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <qnamespace.h>
#include <qpixmap.h>

TurnRightBlock::TurnRightBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/turn_right.png"), true, true, 0,
                "turn_right", QJsonObject{{"params", QJsonObject{}}}, parent) {}
