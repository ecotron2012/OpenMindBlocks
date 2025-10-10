#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class EndProgramBlock : public BlockItem {
	Q_OBJECT
public:
	explicit EndProgramBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
