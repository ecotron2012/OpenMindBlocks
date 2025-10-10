#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class StopProgramBlock : public BlockItem {
	Q_OBJECT
public:
	explicit StopProgramBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
