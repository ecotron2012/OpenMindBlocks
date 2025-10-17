#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class CondBlockEndBlock : public BlockItem {
	Q_OBJECT
public:
	explicit CondBlockEndBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
