#include <unordered_map>
#include <functional>

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

unordered_map<string, function<json()>> prims {
	{"move_fwd", move_fwd},
	{"move_bwd", move_bwd},
	{"if_cond", if_cond},
	{"while_cond", while_cond},
	{"color_sensor", color_sensor},
	{"n_times", n_times},
};
