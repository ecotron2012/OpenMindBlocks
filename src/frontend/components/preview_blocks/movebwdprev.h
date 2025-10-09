#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

class MoveBwdPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit MoveBwdPrev(QWidget* parent = nullptr);
};
