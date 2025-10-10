#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class MoveBackwardBlock : public BlockItem {
	Q_OBJECT
public:
	explicit MoveBackwardBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
