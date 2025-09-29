import os
import subprocess
import paramiko
from dotenv import load_dotenv

load_dotenv()
path = './'

def transfer_to_ev3(ssh, filepath):
    subprocess.run(["scp", "main.py", f"robot@ev3dev:/home/robot/programs" ])

def run_program(ssh, filepath):
    ssh.exec_command("brickrun -r -- pybricks-micropython ./main.py")

def load_program(ssh, path, filename):
    ssh.exec_command("brickrun -r -- pybricks-micropython ./main.py")
    

host = os.getenv("HOST")
user = os.getenv("USER")
pwd = os.getenv("PASS")
print(f"host: {host}, user:{user}, pass:{pwd}")

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(host, username=user, password=pwd)

# transfer_to_ev3(ssh)
run_program(ssh)

ssh.close()

while True:
    pass
