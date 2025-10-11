#pragma once

#include "components/programming_blocks/blockitem/blockitem.h"
#include <qgraphicsitem.h>
#include <qtmetamacros.h>
class StartProgramBlock : public BlockItem {
	Q_OBJECT
public:
	explicit StartProgramBlock(QGraphicsItem* parent = nullptr);
protected:
private:
};
