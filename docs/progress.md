# Project Progress

This markdown will track the development log, checkpoints and tasks for this project.

---
## Checkpoints

🚩 **Checkpoint One (March 11)**
- [X] Game design document

🚩 **Checkpoint Two (March 18)**
- [ ] Placeholder 2D art
- [ ] Handmade map
- [ ] Wall colliders
- [ ] Player entity and movement

🚩 **Checkpoint Three (March 25)**
- [ ] Game loop
- [ ] Energy bar
- [ ] Item tiles
- [ ] Enemies
- [ ] Pathing

🚩 **Checkpoint Four (April 1)**
- [ ] Finalized 2D art
- [ ] Bordered tiles
- [ ] Procedural map generation

🏁 **Checkpoint Five (April 8)**
- [ ] Sound and music
- [ ] UI menus
- [ ] Beginning cut scene
- [ ] Presentation

Checkpoints four and five have features that have a high chance of being out of scope and can be removed if I need more time for the MVP features.

---
### 🚩 Checkpoint One (DONE)

Game design document
- [x] Document
- [x] Engine design PDF

### 🚩 Checkpoint Two (IN PROGRESS)

Placeholder 2D art

Handmade map

Wall colliders

Player entity and movement

### TODO for cleaner code
- *Map iteration is super inefficient*
- Event response system is getting pretty big
  - Utils for player item sprite and wall resetting?
- Remove as many hardcoded values as possible
  - Window dimensions
  - Map draw tile sources
- Remove if check for every map tile for treasure chest
- Rewrite animation system (maybe break it up into separate systems)
- Split up the collision system into collider system (updates collider positions) and collision checker system?
- MainMenuSystem a bit misleading in what it does
- Is UI render system needed, now that I've gotten rid of the camera?
- Hard coded animation system
- Hard coded values in movement system
- Player spritesheet should update based on the item, not done thru collisions
- Render map as a system?
- Move two player view references for Manhattan distance to Render utils?
- Change path illumination system to use delta time instead of sdl ticks
- Combine Velocity and Translation
- Should enemy wander system use collider instead of velocity and translation?
- XML files to avoid hard coded values (e.g. for textures, for spritesheet reference positions) 

### 📝 Development Log

March 17
- 4-5pm (1 hour)
    - Added a Markdown to track my progress
    - Added CMake

March 18
- 1:30-2:00am (30 minutes)
    - Added assignment code to work off of

March 19
- 12-2pm (2 hours)
    - Built handmade map on Tiled 

March 23
- 4-4:45pm (45 minutes)
    - Imported handmade map

March 25
- 1-4:30am (3.5 hours)
    - Stretched map to fit maximized window

March 31
- 12:20-2:50pm (2.5 hours)
  - Cleaned up files and removed unused functionality from the tutorial
- 4:30-6:30pm (2 hours)
  - Cleaned up files and removed unused functionality from the tutorial

April 1
- 12-6am (6 hours)
  - Added a new Vector 2D util function
  - Adjusted movement to be discrete instead of smooth
    - Fixed bug where collision with wall caused the player to get stuck
    - Adjusted animation to follow discrete movement
    - Fixed player stutters when swimming into wall
  - Added treasure collection and exit win condition
  - Added player carrying treasure animation
    - Changed the treasure tile to a wall tile on treasure pickup
- 12-2:30pm (2.5 hours)
  - Added tile space for energy bar
  - Added energy depletion on lose condition
    - Added EnergyDepletionSystem
  - Tracked energy with energy bar component
    - Removed UI tiles based on energy amounts
  - Added energy tile functionality
- 4:30-6pm (1.5 hours)
  - Created player weapon holding animations
  - Added diver weapon pickup

April 6
- 11am-1:30pm (2.5 hours)
  - Added temporary hack for weapon/treasure switching
  - Added enemy entities
- 2-4:30pm (2.5 hours)
  - Split part of EventResponseSystem into TileInteractionSystem
  - Changed player view so that window is transparent where player can't see
- 5-6pm (1 hour)
  - Added alternative map layout

April 7
- 1:30-3:30pm (2 hours)
  - Fixed treasure/weapon swapping glitch
- 4-5:30pm (1.5 hours)
  - Added guide path tracking
  - Changed pathing algorithm from DFS to BFS
  - Added lifetime duration on paths

April 8
- 12:30-
  - Fixed pathing selection
  - Added missing sprites
  - Added enemy wandering
  - Drew and added enemy and player fighting
  - Added window icon
  - Built an executable