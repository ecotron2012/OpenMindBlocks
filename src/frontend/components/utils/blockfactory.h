#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/programming_blocks/stopprogramblock.h"
#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/moveforwardblock.h"
#include "components/programming_blocks/startprogramblock.h"
#include "components/programming_blocks/turnleftblock.h"
#include "components/programming_blocks/turnrightblock.h"
#include <QString>
#include <QJsonObject>
using namespace std;
using Factory = function<BlockItem*(const QJsonObject&)>;
class BlockFactory{
public:
	virtual BlockItem* createBlock() = 0;
	virtual ~BlockFactory(){};

};

class StartProgramBlockFactory: public BlockFactory{
public:
	StartProgramBlock* createBlock() override{
		return new StartProgramBlock();
	}
};

class StopProgramBlockFactory: public BlockFactory{
public:
	StopProgramBlock* createBlock() override{
		return new StopProgramBlock();
	}
};

class MoveForwardBlockFactory: public BlockFactory{
public:
	MoveForwardBlock* createBlock() override{
		return new MoveForwardBlock();
	}
};

class MoveBackwardBlockFactory: public BlockFactory{
public:
	MoveBackwardBlock* createBlock() override{
		return new MoveBackwardBlock();
	}
};

class TurnLeftBlockFactory: public BlockFactory{
public:
	TurnLeftBlock* createBlock() override{
		return new TurnLeftBlock();
	}
};

class TurnRightBlockFactory: public BlockFactory{
public:
	TurnRightBlock* createBlock() override{
		return new TurnRightBlock();
	}
};

extern const unordered_map<string, Factory> BLOCK_FACTORY;
