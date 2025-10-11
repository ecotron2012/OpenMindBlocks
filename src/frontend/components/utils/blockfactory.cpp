#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/programming_blocks/stopprogramblock.h"
#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/moveforwardblock.h"
#include "components/programming_blocks/startprogramblock.h"
#include "blockfactory.h"
#include <memory>
#include <qjsonobject.h>
#include <unordered_map>

using Factory = function<BlockItem*(const QJsonObject &)>;

const unordered_map<string, Factory> BLOCK_FACTORY = {
    {"move_fwd", [](const QJsonObject &) { return  new MoveForwardBlock(); }},
    {"move_bwd", [](const QJsonObject &) { return new MoveBackwardBlock(); }},
    {"start_program", [](const QJsonObject &) { return new StartProgramBlock(); }},
    {"stop_program", [](const QJsonObject &) { return new StopProgramBlock(); }}
};
