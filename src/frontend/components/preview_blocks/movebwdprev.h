#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <qtmetamacros.h>
#include <qwidget.h>

using namespace std;

class MoveBwdPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit MoveBwdPrev(QWidget* parent = nullptr);
};
