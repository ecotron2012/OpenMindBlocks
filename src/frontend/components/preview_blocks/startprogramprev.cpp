#include "base/previewblockbase.h"
#include "startprogramprev.h"

#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

StartProgramPrev::StartProgramPrev(QWidget *parent)
    : PreviewBlockBase("start_program", QPixmap(":/blocks/start_program.png")
                .scaledToHeight(80, Qt::SmoothTransformation), parent) {
}
