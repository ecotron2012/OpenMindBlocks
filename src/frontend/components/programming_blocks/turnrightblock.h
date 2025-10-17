#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class TurnRightBlock : public BlockItem {
	Q_OBJECT
public:
	explicit TurnRightBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
