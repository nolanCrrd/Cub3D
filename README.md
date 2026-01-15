# Cub3D
Cub3d is a project that ask to reproduce a little game environement using raycasting.
That the same technologie than wolfenstein game that was released in 1992.
|            |           |
|------------|-----------|
<img src=https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEim53w6PKjjNpyC1Pa7g5jErdQDHtFscXt3gKSROiYldA1KPxJfCEUPUyptqjTNrfVkdxQxIqMT3ZGaRyJALi-1ClbBHnRYLjWD1umR9cbm18MCMGc-3JPw47iJby_S1SbSfDYsUhkUHRk/s640/Wolfenstein+3DGE.png alt="covber"/>|<img src=https://m.media-amazon.com/images/M/MV5BNDU2NDQ2NGQtOGQ4My00ZTBkLWFhYWEtMGY2MzlmMmQxNjMxXkEyXkFqcGc@._V1_.jpg alt="wolfenstein exemple"/>|

# Raycasting

## Concept
Le raycasting est une méthode de rendu 3D pour des envirnement très simple. L'objectif est d'envoyer des rayons partant du joueur
afin de calculer la distance avec le premier mur rencontré par chaqu'un se ses rayons.

### Découpage par étapes
| Etape | Example |
|-|-|
|1. Send 1 ray from the player <br/> 2. Calculate the first border of the grid that the ray will encounter on X and Y <br/> 3. Calculate the delta distance between 2 X border and 2 Y border |<img src=https://lodev.org/cgtutor/images/raycastdelta.gif alt="lode Vandevenne example" width=100px/>|
|5. Make the ray go forward until it it a border that is a part of a wall case <br/> 6. Calculate the perpendicular distance with the camera plane (to avoid fisheye effect) | <img src=https://lodev.org/cgtutor/images/raycastperpwalldist2.png alt="Lode Vandevenne example" width=200px/>
|7. Draw a vertical line with the distance factor <br/> 8. (If textured) For each pixel of the line get the correct pixel in the texture||

Reapeat this process for each X pixels of the screen !

## Optimisation
That cost a lot of time to be done because it's on the CPU. Now imagine to make floor and ceiling texture (like in doom) we have to calcul this not for all X but for all X and Y pixel the total require a lot of ressources.

To optimise it there is multiple solution:
1. Make the raycaster work in a smaller screen and scretch it to an upper resolution
   - Simple
   - Important overall quality loss
2. Make 1 ray for multiple pixels instead of all pixels
   - Little bit more complicated
   - Overall quality correct with good tweaks
3. Multi threading, cut the screen in multipe sector and each thread do one sector
   - Complicated
   - Overall quality not impacted

### Our choice
We choose to do the seconde one, but with some tweaks, we can change the amount of pixel each ray do in runtime to adapt,
And when the player not move we do 1 ray for 1 pixels to get the best quality instantly, that make a good balance.

But this methode had some limits that are not intuitives:
- After 1 ray for 4 pixels the gain is ridiculous
- It's not magic we only gain arround 15ms per frame

# Usage
I will describe only the bonus usage because why use the ugly version ahaha. The bonus version need a config file that contain same
things as this example (except for the textures paths):

```bash
EA       texture_path # you can space option with it's value with space if you want
# You can space data with empty lines if you want
WE   texture_path
NOtexture_path
SO texture_path
C texture_path
F texture_path
# You can place all things above in the order you want

# Map
11111111
10000001
1000N001 # N/S/E/W for the player position and default direction
10D00001 # For doors positions
11111111
```

To execute you best map use this commands:
```bash
make bonus
./cube3D_bonus path_to_config_file
```

# Some exemple of our game
|1 for 1|1 for 4|1 for 10|
|-------|-------|--------|
|<img alt="image" src="https://github.com/user-attachments/assets/7992c41c-f0dc-4c56-8f5e-dccd2d1f2202" /> | <img alt="image" src="https://github.com/user-attachments/assets/da763bcd-39e7-4a4b-8f54-5d6dc5b3dacf" /> | <img alt="image" src="https://github.com/user-attachments/assets/b2ad1898-2b02-47db-9674-fc24c9d41a81" />|
|<img alt="image" src="https://github.com/user-attachments/assets/081f04df-82a8-41d6-b88a-cc904c8e9b2f" /> | <img alt="image" src="https://github.com/user-attachments/assets/ca57c84b-ea59-4181-936d-f92f474fd6e9" /> | <img alt="image" src="https://github.com/user-attachments/assets/f016c34c-6b18-476d-9f9d-d077d38d80c6" />|

As you can se the "1 for 4" isn´t that bad so when we move we don't see a lot of difference, you can also see that only far texture that are really impacted so it doesn't matter with a such render technology (we're not making a AAA).

# Tanks to
- My mate for this project ![Etienne Hodé](https://github.com/etienne-hd)
- Lode Vandevenne and all the contributor of this ![tutorial](https://lodev.org/cgtutor/raycasting.html)
