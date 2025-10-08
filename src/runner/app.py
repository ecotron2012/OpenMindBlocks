import paramiko
from flask import Flask
import os
import subprocess
import paramiko
import atexit
from engine import prims, compile_runtime

app = Flask(__name__)

host = os.getenv("HOST")
user = os.getenv("USER")
pwd = os.getenv("PASS")

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(host, username=user, password=pwd)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/add_instruction")
def add_line():
    #TODO: Load template in file
    # TODO Jump # of lines in template
    # TODO load corresponding insgrucion
    ssh.exec_command("brickrun -r -- pybricks-micropython ./main.py")
    return "<p>Hello, World!</p>"

@app.route("/run_program")
def run_program():
    # TODO:
    return

@app.route("/test")
def test():
    program = prims.prims["start"]() + "\n"
    test_program = {
        "program": [{
            "name": "move_fwd",
            "params": {}
        },
        {
            "name": "move_bwd",
            "params": {}
        },
        {
            "name": "move_bwd",
            "params": {}
        },
        {
            "name": "if_cond",
            "params": {
                    # TODO: cond debe ser un condicional ligado a los sensores de colores
                    "cond": {"name": "color_sensor", "value": prims.colors["red"]},
                    "body": [
                    {
                        "name": "move_fwd",
                        "params": {}
                    },
                    {
                        "name": "move_bwd",
                        "params": {}
                    },
                    ],
            }
            
        },
        {
            "name": "while_cond",
            "params": {
                    "cond": {"name": "n_times", "value": 4},
                    "body": [
                    {
                        "name": "move_fwd",
                        "params": {}
                    },
                    {
                        "name": "move_bwd",
                        "params": {}
                    },
                    {
                        "name": "move_bwd",
                        "params": {}
                    },
                    ],
        }
                    }
        ]}
    result = compile_runtime.compile(test_program.get("program"))
    final_program = program + result
    print(f"Resultado de compilacion: {result}")
    run_program(final_program)
    return "<p>Testing stuff on your EV3....</p>"

def OnExitApp():
    ssh.close()   
    print("cerrando aplicacion...")

def run_program(program):
    sftp = ssh.open_sftp()
    ssh.exec_command("rm ~/tmp")
    try:
        sftp.stat(f"/home/{user}/tmp")
    except FileExistsError:
        print("Creando el directorio tmp...")
        sftp.mkdir(f"/home/{user}/tmp")
    with sftp.file(f"/home/{user}/tmp/program.py", "w") as f:
        f.write(program)
    stdin, stdout, stderr = ssh.exec_command("brickrun -r -- pybricks-micropython ~/tmp/program.py")
    print(stdout.read().decode(), stderr.read().decode())
    sftp.close()

atexit.register(OnExitApp)
