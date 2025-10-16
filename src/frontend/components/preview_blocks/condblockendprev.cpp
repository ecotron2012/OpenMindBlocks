#include "condlblockendprev.h"
#include <components/preview_blocks/base/previewblockbase.h>
#include <QWidget>
#include <QPixmap>
#include <QString>

using namespace std;

CondBlockEndPrev::CondBlockEndPrev(QWidget *parent)
    : PreviewBlockBase("cond_end", QPixmap(":/blocks/cond_block_end.png"),
                       QString::fromStdString("Terminar bloque condicional"), parent) {}
