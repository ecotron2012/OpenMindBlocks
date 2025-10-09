#include "jsonconverter.h"
#include "../../components/programming_blocks/blockitem.h"

#include <vector>
using namespace std;

#include <nlohmann/json.hpp> // incluir el header principal
using json = nlohmann::json; // alias de conveniencia

JSONConverter::JSONConverter(){

}

json JSONConverter::convertCodeToJSON(vector<BlockItem*> blocks){
	json file = json({}); 
	file["program"] = json::array();
	for (BlockItem* block : blocks){
		json block_element;
		block_element["name"] = block->getName();
		file["program"].push_back({});	
	}
	return file;
}
