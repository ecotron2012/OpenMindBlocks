#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "../../components/programming_blocks/blockitem/blockitem.h"

#include <iostream>
#include <mutex>
#include <qobject.h>
#include <vector>
using namespace std;

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

  QJsonObject convertCodeToJSON(vector<BlockItem *> blocks);
};

#endif
