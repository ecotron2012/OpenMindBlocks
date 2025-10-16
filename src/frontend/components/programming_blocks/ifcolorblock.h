#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <qgraphicsitem.h>
#include <qitemselectionmodel.h>
#include <qtmetamacros.h>

enum class ComboAnchor { TopLeft, TopRight, BottomLeft, BottomRight, Center };

class IfColorBlock : public BlockItem {
  Q_OBJECT
public:
  explicit IfColorBlock(QGraphicsItem *parent = nullptr);
  void paint(QPainter *p, const QStyleOptionGraphicsItem *opt,
             QWidget *widget) override;

  QColor currentColor() const { return m_color; }

signals:
  void colorChanged(const QColor &);

private:
  void setupCombo();
  void setColorFromName(const QString &);
  void ensureCombo();
  void layoutOverlay(); // posiciona el combo

  QComboBox *m_combo = nullptr;
  QGraphicsProxyWidget *m_comboProxy = nullptr;

  QColor m_color = Qt::red;
};
