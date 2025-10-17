#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

class TurnRightPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit TurnRightPrev(QWidget* parent = nullptr);
};
