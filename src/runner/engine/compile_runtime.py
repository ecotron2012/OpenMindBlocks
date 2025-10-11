from engine import prims
import numpy as np

"""
parse(program):
Parse a programming block into python code
{
    "program":[
        {"name": "move_fwd",
            params: {}},
        {"name": "if_block",
            "params":{
                "cond": "i => 1",
                "body": [{
        {"name": "move_fwd",
            params: {}},}]

            }
        }

    
    ]
}
...and write it to the EV3 connected via USB
"""
def parse(block):
    block_name = block.get("name")
    block_params = block.get("params") or {}
    instruction = prims.prims[block_name](**block_params)
    return instruction

"""
compile(program):
Recibe una secuencia de bloques de instruccion:
{
    "program":[
        {"name": "move_fwd",
            params: {}},
        {"name": "if_block",
            "params":{
                "cond": "i => 1",
                "body": [{
        {"name": "move_fwd",
            params: {}},}]

            }
        }

    
    ]
}
Y las escribe en el robot conectado por USB.
"""
def compile(program):
    vec_parse = np.vectorize(parse)
    code = ""
    for block in program:
        block_name = block.get("name")
        block_params = block.get("params" or {})
        if len(block_params.get("body") or []) >= 1:
            aux_instruction = compile(block_params.get("body"))
            instruction = prims.prims[block_name](block_params.get("cond"), aux_instruction)
        else: instruction = prims.prims[block_name](**block_params)
        code += instruction + "\n"
    return code
