#include "stopprogramblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>

StopProgramBlock::StopProgramBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/stop_program.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, false, 0, "stop_program", QJsonObject{{"params", QJsonObject{}}},
                parent) {}
