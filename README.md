# cub3d	[![jthompso's 42Project Score](https://badge42.herokuapp.com/api/project/jthompso/cub3d)](https://github.com/AuroraSloan/badge42)
![cucco gameplay](https://media1.giphy.com/media/DZXoS76eCc0zkKXImE/giphy.gif)
The goal of this project was to become comfortable with ray-casting by creating a dynamic view inside a maze. The cub3d project is based on the classic Wolfenstein 3D game http://users.atw.hu/wolf3d/.

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
Instead of playing the game, an image (in the players initial point of view) will be saved as a .bmp file with the following command:
```bash
./cub3d --save
```

### Controls
``W`` ``A`` ``S`` ``D`` will allow you to move around the map.

``←`` ``→`` will allow you to look around the map.

``ESC`` or ``✖`` will allow you to safely exit the game.

## Plot
Evil Ghini have taken over Mabe Village!

Please save all the Cucco before it's too late. Don't leave anyone behind!

<sub><sup>#hint: A map will show you the way </sup></sub>
