from flask import Flask
import os
import paramiko
import atexit

app = Flask(__name__)

host = os.getenv("HOST")
user = os.getenv("USER")
pwd = os.getenv("PASS")

# ssh = paramiko.SSHClient()
# ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
# ssh.connect(host, username=user, password=pwd)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/run_program")
def run_program():
    # TODO:
    return

def OnExitApp():
    # ssh.close()   
    print("cerrando aplicacion...")

atexit.register(OnExitApp)
