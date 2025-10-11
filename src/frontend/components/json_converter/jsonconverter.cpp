#include "jsonconverter.h"
#include "../../components/programming_blocks/blockitem/blockitem.h"

#include <QJsonArray>
#include <QJsonObject>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonparseerror.h>
#include <qlogging.h>
#include <qobject.h>
#include <qstring.h>
#include <vector>

JSONConverter *JSONConverter::instancePtr{nullptr};
mutex JSONConverter::mtx;

JSONConverter *JSONConverter::getInstance() {
  lock_guard<mutex> lock(mtx);
  if (instancePtr == nullptr) {
    instancePtr = new JSONConverter();
  }
  return instancePtr;
}

QJsonObject JSONConverter::convertCodeToJSON(vector<BlockItem *> blocks) {
  QJsonObject file;
  QJsonArray programArray;
  for (BlockItem *block : blocks) {
    QJsonObject block_element;
    block_element["name"] = QString::fromStdString(block->getName());
    QJsonObject paramsObj = block->getParams();

    if (paramsObj.contains("params"))
      block_element["params"] = paramsObj["params"];
    else
      block_element["params"] = QJsonObject{};
    programArray.append(block_element);
    // TODO: add support for if and while blocks, generate conditional
    // statements
  }
  file["program"] = programArray;
  QJsonDocument doc(file);
  qDebug().noquote() << doc.toJson(QJsonDocument::Indented);

  return file;
}
