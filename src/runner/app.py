import threading
import paramiko
from flask import Flask, request, jsonify
import os
import sys
import subprocess
import paramiko
import atexit
from engine import prims, compile_runtime
from pathlib import Path
from werkzeug.serving import make_server

def load_env():
    try:
        from dotenv import load_dotenv
    except ImportError:
        return  # si no está, sigue con ENV del sistema

    candidates = []

    # 1) Si es one-file, datos empaquetados van en _MEIPASS:
    meipass = getattr(sys, "_MEIPASS", None)
    if meipass:
        candidates.append(Path(meipass) / ".env")

    # 2) Carpeta del ejecutable (permite .env editable junto al EXE)
    exe_dir = Path(getattr(sys, "executable", __file__)).parent
    candidates.append(exe_dir / ".env")

    # 3) CWD por si lo lanzan desde terminal
    candidates.append(Path.cwd() / ".env")

    for p in candidates:
        if p.is_file():
            load_dotenv(p)        # carga y no rompe si faltan claves
            break

load_env()
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

@app.route("/execute", methods=['POST'])
def execute():
    if request.method != 'POST':
        return jsonify({"result": "Invalid request type..."}), 400
    else:
        code_sequence = request.get_json().get("program") or {}
        compiled_code = compile_runtime.compile(code_sequence)
        run_program(compiled_code)
        return jsonify({"result": "Compiling and running your code..."}), 200



@app.route("/test")
def test():
    program = prims.prims["start_program"]() + "\n"
    test_program = {
        "program": [{
            "name": "turn_right",
            "params": {}
        },
        # {
        #     "name": "turn_right",
        #     "params": {}
        # },
        {
            "name": "move_fwd",
            "params": {}
        },
        # {
        #     "name": "if_cond",
        #     "params": {
        #             # TODO: cond debe ser un condicional ligado a los sensores de colores
        #             "cond": {"name": "color_sensor", "value": prims.colors["red"]},
        #             "body": [
        #             {
        #                 "name": "move_fwd",
        #                 "params": {}
        #             },
        #             {
        #                 "name": "move_bwd",
        #                 "params": {}
        #             },
        #             ],
        #     }
        #
        # },
        # {
        #     "name": "while_cond",
        #     "params": {
        #             "cond": {"name": "n_times", "value": 4},
        #             "body": [
        #             {
        #                 "name": "move_fwd",
        #                 "params": {}
        #             },
        #             {
        #                 "name": "move_bwd",
        #                 "params": {}
        #             },
        #             {
        #                 "name": "move_bwd",
        #                 "params": {}
        #             },
        #             ],
        # }
                    # }
        ]}
    result = compile_runtime.compile(test_program.get("program"))
    final_program = program + result
    print(f"Resultado de compilacion: {result}")
    run_program(final_program)
    return "<p>Testing stuff on your EV3....</p>"

# TODO: Create endpoint for shutting down server
def shutdown_server():
    func = exit
    if func is None:
        raise RuntimeError('Not running with the Werkzeug Server')
    func()
    
# Terminate the app process
@app.route("/shutdown", methods=['GET'])
def shutdown():
    ssh.close()
    shutdown_server()
    return "<p>Shutting down server...</p>"

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

if __name__ == "__main__":
    # host = os.getenv("BACKEND_HOST", "127.0.0.1")
    # port = int(os.getenv("BACKEND_PORT", "5000"))
    app.run(host="127.0.0.1", port=5000, debug=False, use_reloader=False, threaded=True)
