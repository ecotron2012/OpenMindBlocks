#include "base/previewblockbase.h"
#include "movefwdprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

MoveFwdPrev::MoveFwdPrev(QWidget *parent)
    : PreviewBlockBase("move_fwd", QPixmap(":/blocks/move_forward.png")
                .scaledToHeight(80, Qt::SmoothTransformation), parent) {
}
