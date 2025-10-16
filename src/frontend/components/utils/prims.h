#include <unordered_map>
#include <functional>
#include <QJsonObject>

using namespace std;

QJsonObject move_fwd();


QJsonObject move_bwd();

QJsonObject if_cond();

QJsonObject while_cond();

QJsonObject color_sensor(const QString& color);

QJsonObject n_times(int n);

extern const unordered_map<string, function<QJsonObject(const QJsonObject&)>> prims;

