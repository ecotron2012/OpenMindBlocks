#include "components/programming_blocks/movebackwardblock.h"
#include "movebackwardblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <nlohmann/json.hpp> // incluir el header principal
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>
using json = nlohmann::json; // alias de conveniencia

MoveBackwardBlock::MoveBackwardBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/move_backward.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, true, 0, "move_bwd", {{"params", json::object()}},
                parent) {}
