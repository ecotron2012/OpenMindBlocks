#include "base/previewblockbase.h"
#include "movebwdprev.h"

#include <qlabel.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

MoveBwdPrev::MoveBwdPrev(QWidget *parent)
    : PreviewBlockBase("move_bwd", QPixmap(":/blocks/move_backward.png")
                .scaledToHeight(80, Qt::SmoothTransformation), parent) {
}
