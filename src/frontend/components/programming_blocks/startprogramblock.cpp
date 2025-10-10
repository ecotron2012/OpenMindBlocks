#include "startprogramblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <nlohmann/json.hpp> // incluir el header principal
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>
using json = nlohmann::json; // alias de conveniencia

StartProgramBlock::StartProgramBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/start_program.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                false, true, 0, "start_program", {{"params", json::object()}},
                parent) {}
