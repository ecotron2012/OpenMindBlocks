#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class TurnLeftBlock : public BlockItem {
	Q_OBJECT
public:
	explicit TurnLeftBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
