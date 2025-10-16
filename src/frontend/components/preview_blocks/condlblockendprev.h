#include <components/preview_blocks/base/previewblockbase.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class CondBlockEndPrev: public PreviewBlockBase {
	Q_OBJECT
public:
	CondBlockEndPrev(QWidget* parent = nullptr);
};
