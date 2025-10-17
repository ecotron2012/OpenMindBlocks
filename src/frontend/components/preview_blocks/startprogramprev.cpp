#include "startprogramprev.h"
#include "base/previewblockbase.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

StartProgramPrev::StartProgramPrev(QWidget *parent)
    : PreviewBlockBase("start_program", QPixmap(":/blocks/start_program.png"),
                       QString::fromStdString("Comenzar programa"), parent) {}
