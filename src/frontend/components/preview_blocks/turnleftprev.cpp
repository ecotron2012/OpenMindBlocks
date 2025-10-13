#include "turnleftprev.h"
#include "base/previewblockbase.h"

#include <qlabel.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

TurnLeftPrev::TurnLeftPrev(QWidget *parent)
    : PreviewBlockBase("turn_left", QPixmap(":/blocks/turn_left.png"),
                       parent) {}
