#include "endprogramblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <nlohmann/json.hpp> // incluir el header principal
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>
using json = nlohmann::json; // alias de conveniencia

EndProgramBlock::EndProgramBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/end_program.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, false, 0, "end_program", {{"params", json::object()}},
                parent) {}
