#include "components/programming_blocks/condblockendblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <qnamespace.h>
#include <qpixmap.h>

CondBlockEndBlock::CondBlockEndBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/cond_block_end.png"), true, true, 0,
                "cond_block_end", QJsonObject{{"params", QJsonObject{}}},
                parent) {}
