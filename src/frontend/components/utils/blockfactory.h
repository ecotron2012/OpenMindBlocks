#include "components/programming_blocks/blockitem/blockitem.h"
#include "components/programming_blocks/stopprogramblock.h"
#include "components/programming_blocks/movebackwardblock.h"
#include "components/programming_blocks/moveforwardblock.h"
#include "components/programming_blocks/startprogramblock.h"
#include <QString>
using namespace std;
using Factory = function<BlockItem*(const json&)>;
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

extern const unordered_map<string, Factory> BLOCK_FACTORY;
