#include "prevblockfactory.h"
#include "components/preview_blocks/base/previewblockbase.h"
#include "condlblockendprev.h"
#include "ifcolorprev.h"
#include "movebwdprev.h"
#include "movefwdprev.h"
#include "startprogramprev.h"
#include "stopprogramprev.h"
#include "turnleftprev.h"
#include "turnrightprev.h"
#include <QJsonObject>
#include <qjsonobject.h>
#include <string>
using namespace std;

using Factory = function<PreviewBlockBase *(QWidget *)>;

const map<string, Factory> PREV_BLOCK_FACTORY = {
    {"start_program_prev",
     [](QWidget *parent) { return new StartProgramPrev(parent); }},
    {"move_fwd_prev", [](QWidget *parent) { return new MoveFwdPrev(parent); }},
    {"move_bwd_prev", [](QWidget *parent) { return new MoveBwdPrev(parent); }},
    {"turn_left_prev",
     [](QWidget *parent) { return new TurnLeftPrev(parent); }},
    {"turn_right_prev",
     [](QWidget *parent) { return new TurnRightPrev(parent); }},
    {"if_color_prev", [](QWidget *parent) { return new IfColorPrev(parent); }},
    {"cond_block_end_prev",
     [](QWidget *parent) { return new CondBlockEndPrev(parent); }},
    {"stop_program_prev",
     [](QWidget *parent) { return new StopProgramPrev(parent); }},
};
