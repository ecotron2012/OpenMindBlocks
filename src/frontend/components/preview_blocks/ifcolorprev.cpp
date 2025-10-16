#include "ifcolorprev.h"
#include "components/preview_blocks/base/previewblockbase.h"
IfColorPrev::IfColorPrev(QWidget *parent): PreviewBlockBase("if_color", QPixmap(":/blocks/if_color_sensor.png"),
                       QString::fromStdString("Al leer el color..."), parent){
}
