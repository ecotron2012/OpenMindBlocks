#include "base/previewblockbase.h"
#include <qlabel.h>
#include <qpixmap.h>

#include <nlohmann/json.hpp> // incluir el header principal
#include <qtmetamacros.h>
#include <qwidget.h>
using json = nlohmann::json; // alias de conveniencia

using namespace std;

class StopProgramPrev : public PreviewBlockBase {
	Q_OBJECT
public:
	explicit StopProgramPrev(QWidget* parent = nullptr);
};
