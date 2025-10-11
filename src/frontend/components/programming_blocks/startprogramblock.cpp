#include "startprogramblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>

StartProgramBlock::StartProgramBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/start_program.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                false, true, 0, "start_program", QJsonObject{{"params", QJsonObject{}}},
                parent) {}
