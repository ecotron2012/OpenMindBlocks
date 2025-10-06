import paramiko
from flask import Flask
import os
import subprocess
import paramiko
import atexit
from engine import prims

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
    sftp = ssh.open_sftp()
    ssh.exec_command("rm ~/tmp")
    program = prims.prims["start"]() + "\n" + prims.prims["move_fwd"]()
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
    return "<p>Testing stuff on your EV3....</p>"

def OnExitApp():
    ssh.close()   
    print("cerrando aplicacion...")

atexit.register(OnExitApp)
