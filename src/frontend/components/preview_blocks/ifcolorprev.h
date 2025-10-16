#include "components/preview_blocks/base/previewblockbase.h" 
#include <QItemSelection>
#include <qtmetamacros.h>
#include <qwidget.h>
class IfColorPrev : public PreviewBlockBase {
  Q_OBJECT
public:
  IfColorPrev(QWidget *parent = nullptr);
};
