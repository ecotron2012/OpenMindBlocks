#include "base/previewblockbase.h"
#include "stopprogramprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

StopProgramPrev::StopProgramPrev(QWidget *parent)
    : PreviewBlockBase("stop_program", QPixmap(":/blocks/stop_program.png")
                .scaledToHeight(80, Qt::SmoothTransformation), parent) {
}
