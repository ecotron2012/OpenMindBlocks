#include "moveforwardblock.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include <nlohmann/json.hpp> // incluir el header principal
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qpixmap.h>
using json = nlohmann::json; // alias de conveniencia

MoveForwardBlock::MoveForwardBlock(QGraphicsItem *parent)
    : BlockItem(QPixmap(":/blocks/move_forward.png")
                    .scaledToHeight(80, Qt::SmoothTransformation),
                true, true, 0, "move_fwd", {{"params", json::object()}},
                parent) {}
