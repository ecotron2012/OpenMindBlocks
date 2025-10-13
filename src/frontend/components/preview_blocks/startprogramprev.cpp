#include "base/previewblockbase.h"
#include "startprogramprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

StartProgramPrev::StartProgramPrev(QWidget *parent)
    : PreviewBlockBase("start_program", QPixmap(":/blocks/start_program.png"), parent) {
}
