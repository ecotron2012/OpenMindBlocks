#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/programming_blocks/stopprogramblock.h"
#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/moveforwardblock.h"
#include "components/programming_blocks/startprogramblock.h"
#include "blockfactory.h"
#include <memory>
#include <nlohmann/json.hpp> // incluir el header principal
#include <unordered_map>
using json = nlohmann::json; // alias de conveniencia
using namespace std;

using Factory = function<BlockItem*(const json &)>;

const unordered_map<string, Factory> BLOCK_FACTORY = {
    {"move_fwd", [](const json &) { return  new MoveForwardBlock(); }},
    {"move_bwd", [](const json &) { return new MoveBackwardBlock(); }},
    {"start_program", [](const json &) { return new StartProgramBlock(); }},
    {"stop_program", [](const json &) { return new StopProgramBlock(); }}
};
