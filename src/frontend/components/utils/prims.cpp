#include "prims.h"
#include <functional>
#include <unordered_map>

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia
//
using namespace std;

json move_fwd() {
  json j;
  j["name"] = "move_fwd";
  j["params"] = json::object();
  return j;
}

json move_bwd() {
  json j;
  j["name"] = "move_bwd";
  j["params"] = json::object();
  return j;
}

json if_cond() {
  json j;
  j["name"] = "if_cond";
  json params;
  params["cond"] = json::object();
  params["body"] = json::array();
  j["params"] = params;
  return j;
}

json while_cond() {
  json j;
  j["name"] = "while_cond";
  json params;
  params["cond"] = json::object();
  params["body"] = json::array();
  j["params"] = params;
  return j;
}

json color_sensor(string color) {
  json j;
  j["name"] = "color_sensor";
  j["value"] = color;
  return j;
}

json n_times(int n) {
  json j;
  j["name"] = "n_times";
  j["value"] = n;
  return j;
}

const unordered_map<string, function<json(const json &)>> prims = {
    {"move_fwd", [](const json &) { return move_fwd(); }},
    {"move_bwd", [](const json&){ return move_bwd(); }},
    {"if_cond", [](const json&){return if_cond(); }},
    {"while_cond", [](const json&){ return while_cond(); }},
    {"color_sensor", [](const json& a) { return color_sensor(a.value("color", string())); }},
    {"n_times", [](const json& a) { return n_times(a.value("n", 1)); }},
};
