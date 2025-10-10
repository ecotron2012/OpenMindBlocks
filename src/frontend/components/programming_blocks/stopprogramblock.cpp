#include "stopprogramblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <nlohmann/json.hpp> // incluir el header principal
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>
using json = nlohmann::json; // alias de conveniencia

StopProgramBlock::StopProgramBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/stop_program.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, false, 0, "stop_program", {{"params", json::object()}},
                parent) {}
