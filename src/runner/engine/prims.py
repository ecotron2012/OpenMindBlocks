def start_program():
    imports = """#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import Motor
from pybricks.parameters import Port
from pybricks.robotics import DriveBase

ev3 = EV3Brick()

left_motor = Motor(Port.B)
right_motor = Motor(Port.C)

robot = DriveBase(left_motor, right_motor, wheel_diameter=55.5, axle_track=75)
    """
    return imports

def move_fwd():
    inst = """
robot.straight(100)
    """
    return inst

def move_bwd():
    inst = """
robot.straight(-100)
    """
    return inst

prims = {
    "start": start_program,
    "move_fwd": move_fwd,
    "move_bwd": move_bwd
}

