#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <qgraphicsitem.h>
#include <qitemselectionmodel.h>
#include <qtmetamacros.h>

class WhileBlock : public BlockItem {
  Q_OBJECT
public:
  explicit WhileBlock(QGraphicsItem *parent = nullptr);
  void paint(QPainter *p, const QStyleOptionGraphicsItem *opt,
             QWidget *widget) override;

signals:

private:
  void setupCombo();
  void ensureCombo();
  void layoutOverlay(); // posiciona el combo

  QComboBox *m_combo = nullptr;
  QGraphicsProxyWidget *m_comboProxy = nullptr;

  int m_times = 1;
};
