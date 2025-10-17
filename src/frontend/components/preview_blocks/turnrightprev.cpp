#include "turnrightprev.h"
#include "base/previewblockbase.h"

#include <qlabel.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

TurnRightPrev::TurnRightPrev(QWidget *parent)
    : PreviewBlockBase("turn_right", QPixmap(":/blocks/turn_right.png"),
                       QString::fromStdString("Girar derecha"), parent) {}
