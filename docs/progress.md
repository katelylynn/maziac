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

### TODO for UML
- Add Translation and Transform to AnimationSystem
- Add Translation component

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
- 12-2pm (2 hours)
  - Added tile space for energy bar