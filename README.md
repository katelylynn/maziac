# MAZIAC by katelylynn

For updates on my development of this game, see `docs/Progress.md`.

## How to Play

The root folder of this project has an executable version of the game that you can download and play! Alternatively, download it using this link:

[MAZIAC.exe](MAZIAC.exe)

## ECS Design

![ECSDesign.png](docs/ECSDesign.jpg)

### Systems

##### From lecture:
- Animation
- Collision
- KeyboardInput
- Render
##### New / updated:
- **EnemyInteraction** - Handles the interactions between enemies and the player. Output of the fight depends on the amount of energy the player has and whether they have a weapon. Acts like the “EventResponseSystem” from the lecture code but is specialized for enemy/player interactions.
- **EnemyWander** - Handles random movement behavior for each enemy. Prevents the enemy from wandering too far from their initial start point.
- **EnergyDepletion** - Handles energy depletion and calling “game over” when the player has no energy left.
- **Movement** - Handles each characters’ discrete tile movement using Translation, Transform and Velocity. Differs from the lecture code because character movement snaps to each tile, versus being continuous.
- **Observer** - Executes behavior for an entity if a value that entity is watching changes.
- **PathIllumination** - Changes the tiles in the specified path to be "highlighted" until the path's life (time) runs out.
- **TileInteraction** - Handles the interactions (collisions) between the player and each of the tile types. Acts like the “EventResponseSystem” from the lecture code but is specialized for tile/player interactions.
##### Removed:
- **Camera** - Map is stretched to fit the screen view and the player moves around the screen space.
