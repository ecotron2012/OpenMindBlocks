#include "blockfactory.h"
#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/programming_blocks/condblockendblock.h"
#include "components/programming_blocks/ifcolorblock.h"
#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/moveforwardblock.h"
#include "components/programming_blocks/startprogramblock.h"
#include "components/programming_blocks/stopprogramblock.h"
#include "components/programming_blocks/turnleftblock.h"
#include "components/programming_blocks/turnrightblock.h"
#include "components/programming_blocks/whileblock.h"
#include <components/widgets/ifcolorwidget.h>
#include <memory>
#include <qgraphicsitem.h>
#include <qjsonobject.h>
#include <unordered_map>

using Factory = function<BlockItem *(const QJsonObject &)>;

const unordered_map<string, Factory> BLOCK_FACTORY = {
    {"move_fwd", [](const QJsonObject &) { return new MoveForwardBlock(); }},
    {"move_bwd", [](const QJsonObject &) { return new MoveBackwardBlock(); }},
    {"start_program",
     [](const QJsonObject &) { return new StartProgramBlock(); }},
    {"stop_program",
     [](const QJsonObject &) { return new StopProgramBlock(); }},
    {"turn_left", [](const QJsonObject &) { return new TurnLeftBlock(); }},
    {"turn_right", [](const QJsonObject &) { return new TurnRightBlock(); }},
    {"if_color", [](const QJsonObject &) { return new IfColorBlock(); }},
    {"while_cond", [](const QJsonObject &) { return new WhileBlock(); }},
    {"cond_block_end",
     [](const QJsonObject &) { return new CondBlockEndBlock(); }},
};
