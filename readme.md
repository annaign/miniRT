# miniRT

My first RayTracer with miniLibX.
The program is generate images using the Raytracing protocol. Those computer generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

## Requirements

[OS Ubumtu](https://ubuntu.com/)

* [minilibx-linux](https://github.com/42Paris/minilibx-linux)
* ```sudo apt-get install libx11-dev```
* ```sudo apt-get install libxext-dev```
* ```sudo apt-get install libbsd-dev```

## Build and run the project

Clone or download the repository:

```git clone repository_name```

Build the project:

```make```

Run the programm (with one or two arguments):

```./miniRT "file.rt" --[option]```


Argument | Description
-------- | -----------
file.rt  | a scene description file with the .rt extension
--save   | save rendered scene in a .bmp file

## Instructions

### Close programm

Press `ESC` or click red cross on the window’s frame

### Change camera

If there is more than one camera you can to switch between them by pressing the keyboard keys:
* **`r`** - next (right) camera
* **`l`** - previous (left) camera

### (BONUS) Keyboard interactivity (translation/rotation) with camera

Translation:

* **`arrow left`** - increase point.x by 1
* **`arrow right`** - reduce point.x by 1
* **`arrow top`** - increase point.y by 1
* **`arrow bottom`** - reduce point.y by 1
* **`i`** - increase point.z by 1
* **`o`** - reduce point.z by 1

Rotation:

* **`a`** - move direction: (0,y/2)
* **`s`** - move direction: (x/2,y)
* **`d`** - move direction: (x,y/2)
* **`w`** - move direction: (x/2,0)
* **`mouse`** + **`left button`** click inside the window - move direction: (x,y)