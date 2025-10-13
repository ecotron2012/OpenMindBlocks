#include "base/previewblockbase.h"
#include "stopprogramprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

StopProgramPrev::StopProgramPrev(QWidget *parent)
    : PreviewBlockBase("stop_program", QPixmap(":/blocks/stop_program.png"), parent) {
}
