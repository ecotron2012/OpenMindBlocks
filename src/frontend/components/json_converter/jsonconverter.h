#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "../../components/programming_blocks/blockitem.h"

#include <vector>
using namespace std;

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia

class JSONConverter {
public:
  explicit JSONConverter();
  json convertCodeToJSON(vector<BlockItem *> blocks);
};

#endif
