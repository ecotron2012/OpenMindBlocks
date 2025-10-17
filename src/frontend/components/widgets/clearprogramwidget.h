#pragma once
#include "components/programming_blocks/blockitem/blockitem.h"
#include <QPushButton>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <vector>

class ClearProgramWidget : public QPushButton {
  Q_OBJECT
public:
  explicit ClearProgramWidget(QWidget *parent = nullptr);
  void clearProgram();
signals:
  void clearSignal();
};
