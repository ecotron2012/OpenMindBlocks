#include <unordered_map>
#include <functional>

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia
//
using namespace std;

json move_fwd();


json move_bwd();

json if_cond();

json while_cond();

json color_sensor(string color);

json n_times(int n);

extern const unordered_map<string, function<json(const json&)>> prims;

