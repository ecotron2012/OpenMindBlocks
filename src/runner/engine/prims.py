from textwrap import dedent, indent

# --------PROGRAMMING BLOCKS---------------------- #

def start_program():
    imports = """#!/usr/bin/env pybricks-micropython
import _thread
from pybricks.tools import wait
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import Motor, ColorSensor
from pybricks.parameters import Port, Color
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile

def play_sound(soundfile):
    ev3.speaker.play_file(soundfile)

ev3 = EV3Brick()
ev3.speaker.play_file(SoundFile.READY)

left_motor = Motor(Port.B)
right_motor = Motor(Port.C)
color_sensor = ColorSensor(Port.S1)
ev3.screen.load_image(ImageFile.THUMBS_UP)

robot = DriveBase(left_motor, right_motor, wheel_diameter=55.5, axle_track=75)
ev3.speaker.play_file(SoundFile.MOTOR_START)
    """
    return imports

def stop_program():
    return """
_thread.start_new_thread(play_sound, (SoundFile.MOTOR_STOP,))
ev3.screen.load_image(ImageFile.SLEEPING)
wait(1000)
"""

def move_fwd():
    inst = """
_thread.start_new_thread(play_sound, (SoundFile.SPEED_UP,))
ev3.screen.load_image(ImageFile.UP)
robot.straight(100)
wait(250)
    """
    return inst

def move_bwd():
    inst = """
_thread.start_new_thread(play_sound, (SoundFile.BACKING_ALERT,))
ev3.screen.load_image(ImageFile.DOWN)
robot.straight(-100)
wait(1000)
    """
    return inst

def turn_left():
    inst = """
_thread.start_new_thread(play_sound, (SoundFile.MOTOR_IDLE,))
ev3.screen.load_image(ImageFile.MIDDLE_LEFT)
robot.turn(-130)
wait(250)
"""
    return inst

def turn_right():
    inst = """
_thread.start_new_thread(play_sound, (SoundFile.MOTOR_IDLE,))
ev3.screen.load_image(ImageFile.MIDDLE_RIGHT)
robot.turn(130)
wait(250)
"""
    return inst

# COND BLOCKS
def if_block(cond, body):
    indented = indent(body, "        ")
    inst = f"""
while True:
    if {cond}:
        {indented}
        break
    """
    return inst

def while_block(cond, step, body):
    indented_body = indent(body, "        ")
    indented_step = indent(step, "    ")
    inst = f"""
i = 0
while {cond}:
    {indented_body}
    {indented_step}
    """
    return inst

def if_cond(cond, body):
    print(f"Condiciones: {cond}, cuerpo: {body}")
    cond_code = conds[cond["name"]](colors[cond[ "value" ]])
    code = if_block(cond_code, body)
    return code

def while_cond(cond, body):
    # Must Be named "n_times"
    print(f"Condiciones: {cond}")
    cond_code, step = conds[cond["name"]](cond["value"])
    code = while_block(cond_code, step, body)
    return code


# --------CONDITIONAL BLOCKS---------------------- #

# Create the conditional sentence required
def color_sensor(color, equal=True):
    cond = f"""(color_sensor.color() == {color}) == {equal}"""
    return cond

def n_times(n):
    cond = f"""i < {n}"""
    step = f"""i += 1"""
    return cond, step

colors = {
    "red": "Color.RED",
    "black": "Color.BLACK",
    "blue": "Color.BLUE",
    "green": "Color.GREEN",
    "yellow": "Color.YELLOW",
    "white": "Color.WHITE",
    "brown": "Color.BROWN",
    "orange": "Color.ORANGE",
    "purple": "Color.PURPLE",
}

conds = {
    "color_sensor":color_sensor,
    "n_times": n_times,
}

prims = {
    "start_program": start_program,
    "stop_program": stop_program,
    "move_fwd": move_fwd,
    "move_bwd": move_bwd,
    "if_cond": if_cond,
    "if_color": if_cond,
    "while_cond": while_cond,
    "turn_left" :turn_left,
    "turn_right": turn_right
}

