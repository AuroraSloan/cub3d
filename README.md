# cub3d	[![jthompso's 42Project Score](https://badge42.herokuapp.com/api/project/jthompso/cub3d)](https://github.com/AuroraSloan/badge42)
test
![cucco gameplay](https://media.giphy.com/media/O9ufh6QIInY8ttgZaI/giphy.gif)

The goal of this project was to become comfortable with ray-casting by creating a dynamic view inside a maze. The cub3d project is based on the classic Wolfenstein 3D game http://users.atw.hu/wolf3d/.

Currently gameplay is only available on linux operating systems.

----
### Installation
```bash
git clone https://github.com/AuroraSloan/cub3d.git
```
----
## Usage
First, create the executable with make
```bash
make - compiles the cub3d executable
make clean - removes all .o files
make fclean - removes all .o files and the executable
make re - removes all .o files and all executable before recompiling the program
```
In order to run the game window, run the executable with the .cub file.
```bash
./cub3d maps/mabe_library.cub
```

A saved image in the players initial point of view will be saved as a .bmp file with the following command instead of opening the game
```bash
./cub3d maps/mabe_library.cub --save
```
![gameplaybmp](https://picc.io/DUox0O0.png)

### Controls
``W`` ``A`` ``S`` ``D`` will allow you to move around the map.

``←`` ``→`` will allow you to look around the map.

``ESC`` or ``✖`` will allow you to safely exit the game.

## Plot
Evil Ghini have taken over Mabe Village Library!

Please save all the Cucco before it's too late. Don't leave anyone behind!

<sub><sup>#hint: A map will show you the way </sup></sub>
