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
|1. Envoyer 1 rayon partant des coordonnée du joueur <br/> 2. Calculer l'emplacement des premiere ligne de la grille rencontré sur X et Y <br/> 3. Calculer le delta de la distance entre chaqu'une de ces lignes |<img src=https://lodev.org/cgtutor/images/raycastdelta.gif alt="lode Vandevenne example" width=100px/>|
|5. Faire avancer le rayon de ce delta tout droit jusqu'a ce que la bordure fasse partie d'une case mur <br/> 6. Calculer la distance | <img src=https://lodev.org/cgtutor/images/raycastperpwalldist2.png alt="Lode Vandevenne example" width=200px/>
|7. Dessiner une ligne verticale plus ou moins grande en fonction de cette distance <br/> 8. (Si textures) Pour chaque point de cette ligne recuperer le bonne emplacement dans la texture||


## Own optimisation

# Some exemple of our game

# Tanks to
- Lode Vandevenne and all the contributor of this ![tutorial](https://lodev.org/cgtutor/raycasting.html)
