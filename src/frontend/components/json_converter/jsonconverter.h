#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "../../components/programming_blocks/blockitem/blockitem.h"

#include <iostream>
#include <mutex>
#include <vector>
using namespace std;

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia

class JSONConverter {
private:
  static JSONConverter *instancePtr;
  static mutex mtx;

protected:
  JSONConverter() {};
  ~JSONConverter() {};

public:
  JSONConverter(const JSONConverter &obj) = delete;

  void operator=(const JSONConverter &) = delete;

  static JSONConverter *getInstance();

  json convertCodeToJSON(vector<BlockItem *> blocks);
};

#endif
