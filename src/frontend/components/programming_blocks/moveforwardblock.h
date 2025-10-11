#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class MoveForwardBlock : public BlockItem {
	Q_OBJECT
public:
	explicit MoveForwardBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
