#include <qjsonobject.h>
#include <string>
#include "base/previewblockbase.h"
#include <QJsonObject>
using namespace std;
using Factory = function<PreviewBlockBase*(QWidget*)>;

extern const map<string, Factory> PREV_BLOCK_FACTORY;
