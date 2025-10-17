#include <components/preview_blocks/base/previewblockbase.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class WhileBlockPrev: public PreviewBlockBase {
	Q_OBJECT
public:
	WhileBlockPrev(QWidget* parent = nullptr);
};
