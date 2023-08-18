# so_sneaky
The so_long project from 42 School.

This is a simple game written in C, using [miniLibX](https://github.com/42Paris/minilibx-linux) and [yLib](https://github.com/IgorkoGR/ylib). It is compatible with 42 School Norm v3*.

In this game you play as a secret agent trying to escape bandit's base. The twist is that you don't have any weapons, while they do, so your goal is to escape without getting noticed. Each level has an exit. The exit is locked, and it unlocks once you collect all the keycards on the level. Levels may also contain locked doors, that can only be unlocked with a certain type (color) of a keycard. Levels are being constantly patroled by the bandit guards. They patrol their area using one of 3 patrol strategies:

1) Random walk - guard walks constantly in a random direction. Walking forwards has more bias than turning left or right. Turning left or right has more bias than turning 180 degrees back.
2) Wall hugging - guard walks along the wall to the left or right, as if they are solving a maze.
3) Lazy turning - guard constantly walks forward, until they hit a wall. Afterwards, guard turns into a preferred direction.

Guards can't see you through the walls or when you're behind. Getting in their line of sight will result in a game over. Your goal is to collect all keycards and reach the exit of the level without getting noticed.

![screenshot of level 3](/images_src/screenshot.png)

*My definition of compatible is that the norminette doesn't complain about the code :).

## Building instructions

*I only tested building and running this game on MacOS, Fedora 38 and Ubuntu 20.04.*

### Building on Linux

Make sure you have installed all the necessary dependencies:

On Debian/Ubuntu:
`sudo apt-get install clang xorg xorg-dev libxext-dev zlib1g-dev libbsd-dev`

On Fedora:
`sudo dnf install clang libXext libXext-devel zlib zlib-devel libbsd libbsd-devel`

Then `cd` into the repository and then `make`.

### Building on MacOS
Ensure that [miniLibX](https://github.com/42Paris/minilibx-linux) is installed in the system.

`cd` into the repository and then `make`.

### Building on Windows 11
Install either Fedora, Debian or Ubuntu under WSL2 and follow the Linux build instructions.

### Building on Windows 10
Install WSL2 and follow Windows 11 build instructions. (Alternatively figure out how to run X11 programs under WSL1)

## Playing the game

You can launch the game from the command line, using:

`./so_long <path to the level.ber file>`

For example:

`./so_long maps/level1.ber`

will launch the first level of the game. You can use the arrow keys to move around and press the Q key to quit the game.

## Game configuration

This game can be configured with `config.txt` file (on MacOS), or `configlx.txt` (on Linux and other platforms). Inside the config file you can change the window size (miniLibX does not allow making windows resizable), and change the default keybinds.

## Level format

Levels are contained in the .ber files. These files are made according to the requirements specified in so_long subject document (available on 42 intranet). If the .ber file does not follow these requirements, the game will fail to launch.

Any .ber file can also have accompanying .ber.ext file, which may contain extra data to allow extra features of this game, such as doors, colored keycards, custom enemy patrol strategies. They can also point to custom asset override files.

## Game assets

All the assets of this game are drawn by myself, using [Aseprite](https://www.aseprite.org/). Project files are contained in `images_src` folder, while `images` contains exported .tga files. The game can only import .tga graphics.

## Asset overloading

`assets.txt` contains a list of all assets the game uses. Each level of the game may provide its own assets file that overrides specified assets for that particular level.
