#include "base/previewblockbase.h"
#include "movebwdprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

MoveBwdPrev::MoveBwdPrev(QWidget *parent)
    : PreviewBlockBase("move_bwd", QPixmap(":/blocks/move_backward.png")
                .scaledToHeight(80, Qt::SmoothTransformation), parent) {
}
