#include "whileblockprev.h"
#include <components/preview_blocks/base/previewblockbase.h>
#include <QWidget>
#include <QPixmap>
#include <QString>

using namespace std;

WhileBlockPrev::WhileBlockPrev(QWidget *parent)
    : PreviewBlockBase("while_cond", QPixmap(":/blocks/while_block.png"),
                       QString::fromStdString("Repetir n veces..."), parent) {}
