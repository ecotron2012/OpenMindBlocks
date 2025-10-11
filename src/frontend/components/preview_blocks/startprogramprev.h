#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

class StartProgramPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit StartProgramPrev(QWidget* parent = nullptr);
};
