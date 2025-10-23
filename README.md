# OpenMindBlocks: Open Mindstorms Programming Blocks

<img width="4380" height="1024" alt="logo" src="https://github.com/user-attachments/assets/1b276d9b-c001-46a7-9561-e790720d38d0" />


Open Programming Blocks for the masses.

## Table of contents

* [Introduction](#introduction)
* [Installation](#installation)
* [Quick start](#quick-start)
* [Usage](#usage)
* [Known issues and limitations](#known-issues-and-limitations)
* [Getting help](#getting-help)
* [Contributing](#contributing)
* [License](#license)
* [Acknowledgments](#acknowledgments)


## Introduction

This project is meant to serve as a simplified interface for programming LEGO© Mindstorms EV3 robots. It uses symbols instead of complex language to convey movement options and actions, which makes suitable for teaching in younger ages. This project was made as part of my thesis project, which is focused on teaching computational thinking skills to children with Down Syndrome.

The program is composed of an interface made with Qt, and a backend made in Flask to communicate with and send the constructed program in the interface to the EV3.

The programming instructions are represented by puzzle pieces, and are vertically connected to each other, making a sequence of instructions or program. This concept is inspired by works such as Scratch Jr. and KIBO programming blocks.

<img width="1220" height="738" alt="image" src="https://github.com/user-attachments/assets/a4f0a341-4b8e-43a3-ad6e-7ba7b323c013" />


## Installation

You can download the executable/installer for your operating system from the [Releases](https://github.com/ecotron2012/OpenMindBlocks/releases) page.

If you wish to run it from the source code, you need the following tools:
- Python 3.9+
  - Main dependencies used:
      - Flask
      - Paramiko
      - pyBricks, for running the programs inside the EV3
- Qt 6.9.2
- A Mindstorms EV3 robot loaded with ev3dev, connected to your computer and network via USB. You can follow [this tutorial](https://www.ev3dev.org/docs/getting-started/) to learn how to install the ev3dev image on your EV3 device, and [this tutorial](https://www.ev3dev.org/docs/tutorials/connecting-to-the-internet-via-usb/) to learn how to connect your device to your network via USB.
  The robot must have:
    - A color sensor connected to the 1 port
    - A left and right motor connected to the B and C ports, respectively.

To load the backend, first create and activate a virtual environment in the src/runner folder:
```bash
python -m venv .venv
source .venv/bin/activate # Linux
.venv/Scripts/Activate.ps1 # Powershell on Windows
```
Then install the required libraries:
```bash
python -m pip install -r requirements.txt
```
Then create a .env file with tne following contents:
```
EV3_USER=robot
EV3_HOST=ev3dev # or ev3dev.local if you're on Linux
EV3_PASS=maker
```
You can change these values to match the information of your EV3 device (if you changed from the default values)

Now, run the flask backend with
```bash
flask --app app.py run --host=0.0.0.0 # add --debug if you're doing development
```

To run the frontend, load the /src/frontend/CMakeLists.txt on Qt Studio, and run it from there.

## Quick start

To create a program, begin by click and dragging the green block (the 'start program') block into the canvas
<img width="1818" height="244" alt="Screenshot 2025-10-22 183633" src="https://github.com/user-attachments/assets/0bb36695-7d34-498e-8587-b988c74cc0b3" />
<img width="1815" height="874" alt="Screenshot 2025-10-22 183728" src="https://github.com/user-attachments/assets/5d5fffd9-7f8b-4233-906b-803d9104d9af" />

To create a simple program that moves the robot forward, drag and drop the 'move forward' piece to the canvas, then the 'end program' piece to finish the program execution.
<img width="1753" height="233" alt="Screenshot 2025-10-22 184156" src="https://github.com/user-attachments/assets/4fb972ac-dc61-4300-a8e4-99a9f7028e22" />
<img width="651" height="328" alt="Screenshot 2025-10-22 184137" src="https://github.com/user-attachments/assets/8b7cd33b-7c6c-43fe-8980-e24635edb3e8" />

To execute the program, click on the play button located on the upper right corner:
<img width="1200" height="422" alt="Screenshot 2025-10-22 184446" src="https://github.com/user-attachments/assets/99cfd9a4-320b-46b0-afd9-2b77a948d73e" />
And you will see your robot moving forward **(Remember to have the robot connected to your device via usb)**

You can experiment different combinations using the other blocks available on the bottom container.

To clear the canvas, click on the red button located on the upper left corner.

## Demo
[demo2.webm](https://github.com/user-attachments/assets/dd38f2dc-4f8a-4512-9ef1-d84efe90101a)


## Usage

### Programming blocks

There are currently 9 programming blocks, each with a different purpose:
- Start program block: this block tells the robot that a new program is about to be loaded. It contains all the necessary imports and objects needed to start the program, so it must always be the first block of your sequence.
<img width="128" height="128" alt="start_program" src="https://github.com/user-attachments/assets/f62f8794-ca52-4383-b11d-2fa06d009af7" />

- Move forward block: Moves the robot forward according to it's orientation.
  
  <img width="128" height="128" alt="move_forward" src="https://github.com/user-attachments/assets/08bf7b1e-c5a9-466f-8395-424278f0b123" />
  
- Move backward block: Makes the robot move backward.
  
  <img width="128" height="128" alt="move_backward" src="https://github.com/user-attachments/assets/a6e2a718-c90e-4bcc-a51e-c43b1bb12b21" />

- Turn left: Rotates the robot 90 degrees in a counter-clockwise motion.
  
  <img width="128" height="128" alt="turn_left" src="https://github.com/user-attachments/assets/bba9ef6e-edb5-49a0-a7e9-76ff18492cd5" />

- Turn right: Rotates the robot 90 degrees in a clockwise motion.
  
  <img width="128" height="128" alt="turn_right" src="https://github.com/user-attachments/assets/853f4472-7fe8-49ad-92ad-0f39a2d53162" />

- If color block: Makes the robot perform a series of actions if the color sensor detects a certain color. Keep in mind that the flow of execution will stop until the sensor reads the specified color when the program reaches this block.
  
  <img width="128" height="128" alt="if_color_sensor" src="https://github.com/user-attachments/assets/96350b5e-05f2-4c9e-acad-bd029a4effd9" />

- Repeat/while block: Makes the robot repeat a serires of actions up to 10 times.
  
  <img width="128" height="128" alt="while_block" src="https://github.com/user-attachments/assets/3da9c240-78d3-46b3-b344-ed3788c8be05" />

- End condition block: Its purpose is to indicate where the instruction sequence of an if or while block ends, preventing execution errors.

  <img width="128" height="128" alt="cond_block_end" src="https://github.com/user-attachments/assets/cb5be40e-8d2f-4418-a21a-2a3c17c0e3c7" />

- End program block: It marks a symbolic representation of the end of the program and thus its insertion is not required.

  <img width="128" height="128" alt="stop_program" src="https://github.com/user-attachments/assets/44f4c526-ce7a-4ede-b9c7-fca9796a0e97" />

## Known issues and limitations

This project was tested with the [COR3 model](https://ev3lessons.com/RobotDesigns/instructions/COR3.pdf) designed by Michael Buss Andersson, built using the LEGO Mindstorms EV3 Education Core Set (45544).

This project also assumes that the color sensor is connected to the port 1 of the EV3, and the left and right motor are connected to the B and C ports, respectively. Plugging them in any other port will make the program stop working.

The backend uses the port 5000 by default, so make sure it is free before launching the program.

## License

This project is distributed under the terms of the GNU General Public License v3.0 (GPL-3.0). This means that anyone is free to use, modify, and distribute the software, provided that all derivative works remain open-source under the same license and proper credit is given to the original authors. For more details, please refer to the [GNU GPL v3.0 license text](https://www.gnu.org/licenses/gpl-3.0.html).


