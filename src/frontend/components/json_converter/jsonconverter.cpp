#include "jsonconverter.h"
#include "../../components/programming_blocks/blockitem/blockitem.h"

#include <qlogging.h>
#include <qobject.h>
#include <qstring.h>
#include <vector>
using namespace std;

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia


JSONConverter* JSONConverter::instancePtr{nullptr};
mutex JSONConverter::mtx;

JSONConverter *JSONConverter::getInstance() {
  lock_guard<mutex> lock(mtx);
  if (instancePtr == nullptr) {
    instancePtr = new JSONConverter();
  }
  return instancePtr;
}

json JSONConverter::convertCodeToJSON(vector<BlockItem *> blocks) {
  json file = json({});
  file["program"] = json::array();
  for (BlockItem *block : blocks) {
    json block_element;
    block_element["name"] = block->getName();
    block_element["params"] = block->getParams();
    file["program"].push_back(block_element);
    // TODO: add support for if and while blocks, generate conditional
    // statements
  }
  qDebug() << QString::fromStdString(file.dump());
  return file;
}
