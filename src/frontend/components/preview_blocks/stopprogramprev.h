#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

class StopProgramPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit StopProgramPrev(QWidget* parent = nullptr);
};
