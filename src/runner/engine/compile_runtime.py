import logging
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
Takes the program JSON sent by the frontend and reestructures the conditional blocks to a compatible format.
"""
def structure_sequence(program):
    out = []
    stack = []
    for block in program:
        name = block.get("name")
        params = block.setdefault("params", {})

        cond_name = (params.get("cond", {}) or {}).get("name")
        opens_control = (name == "if_color") or (cond_name in ("color_sensor", "n_times"))

        if opens_control:
            params.setdefault("body", [])

            if stack:
                stack[-1]["params"]["body"].append(block)
            else:
                out.append(block)

            stack.append(block)
            continue
        
        if name == "cond_block_end":
            if stack:
                stack.pop()
            else:
                pass
            continue
        
        if stack:
            stack[-1]["params"]["body"].append(block)
        else:
            out.append(block)

    return out
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
        block_cond = block_params.get("cond" or {})
        logging.info(f"Bloque a compilar : {block}")
        if len(block_params.get("body") or []) >= 1:
            aux_instruction = compile(block_params.get("body"))
            instruction = prims.prims[block_name](block_params.get("cond"), aux_instruction)
        else: instruction = prims.prims[block_name](**block_params)
        code += instruction + "\n"
    return code
