#include "prims.h"
#include <QJsonArray>
#include <QJsonObject>
#include <functional>
#include <qcontainerfwd.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <unordered_map>

using namespace std;

QJsonObject move_fwd() {
  QJsonObject j;
  j["name"] = "move_fwd";
  j["params"] = QJsonObject{};
  return j;
}

QJsonObject move_bwd() {
  QJsonObject j;
  j["name"] = "move_bwd";
  j["params"] = QJsonObject{};
  return j;
}

QJsonObject turn_left() {
  QJsonObject j;
  j["name"] = "turn_left";
  j["params"] = QJsonObject{};
  return j;
}

QJsonObject turn_right() {
  QJsonObject j;
  j["name"] = "turn_right";
  j["params"] = QJsonObject{};
  return j;
}

QJsonObject if_cond() {
  QJsonObject j;
  j["name"] = "if_cond";
  QJsonObject params;
  params["cond"] = QJsonObject{};
  params["body"] = QJsonArray{};
  j["params"] = params;
  return j;
}

QJsonObject while_cond() {
  QJsonObject j;
  j["name"] = "while_cond";
  QJsonObject params;
  params["cond"] = QJsonObject{};
  params["body"] = QJsonArray{};
  j["params"] = params;
  return j;
}

QJsonObject color_sensor(const QString &color) {
  QJsonObject j;
  j["name"] = "color_sensor";
  j["value"] = color;
  return j;
}

QJsonObject n_times(int n) {
  QJsonObject j;
  j["name"] = "n_times";
  j["value"] = n;
  return j;
}

const unordered_map<string, function<QJsonObject(const QJsonObject &)>> prims =
    {
        {"move_fwd", [](const QJsonObject &) { return move_fwd(); }},
        {"move_bwd", [](const QJsonObject &) { return move_bwd(); }},
        {"turn_left", [](const QJsonObject &) { return turn_left(); }},
        {"turn_right", [](const QJsonObject &) { return turn_right(); }},
        {"if_cond", [](const QJsonObject &) { return if_cond(); }},
        {"while_cond", [](const QJsonObject &) { return while_cond(); }},
        {"color_sensor",
         [](const QJsonObject &a) {
           return color_sensor(a.value("color").toString());
         }},
        {"n_times",
         [](const QJsonObject &a) { return n_times(a.value("n").toInt(1)); }},
};
