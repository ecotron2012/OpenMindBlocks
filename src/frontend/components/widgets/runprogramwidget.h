#pragma once
#include "components/programming_blocks/blockitem/blockitem.h"
#include <QPushButton>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <vector>

class RunProgramWidget : public QPushButton {
  Q_OBJECT
public:
  explicit RunProgramWidget(QWidget *parent = nullptr);
  void runProgram();
signals:
  void execute();
};
