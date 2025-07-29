# Crossing Road Game - Object-Oriented C++ Terminal Arcade

[![Watch the Demo](https://img.youtube.com/vi/PdXGWGMGf4E/maxresdefault.jpg)](https://www.youtube.com/watch?v=PdXGWGMGf4E)

A feature-rich terminal-based arcade game implementing classic "Crossy Road" mechanics with modern OOP design principles. Built from scratch in C++ using Windows APIs.

## I. Key Features
### 1. Gameplay Mechanics
- **Multi-mode objectives**:
    - Level progression (complete all levels)
    - Endless mode (high score challenge - not completed)
- **Dynamic difficulty**: Obstacle speed/density increases with levels
- **Random events**: Obstacles stop randomly with traffic light indicators
- **Skill system**: Special abilities with cooldowns
- **Coin collection**: Risk-reward bonus points system
- **Co-op support**: 2-player local multiplayer

### 2. System Features
- Save/Load system: Persists game state between sessions
- Leaderboard: Tracks top 3 local scores
- Pause functionality: Full game state preservation
- Multiple themes: Jungle, beach, and urban environments
- Procedural elements: Random coin generation

### 3. Technical Implementation
- ***Core Architecture***
<h3 align="center">🧩 Game Architecture Diagram</h3>

<p align="center">
    <img src="https://drive.google.com/uc?export=view&id=1po_ZM37L9k2Uast_JG4mGIi6fCBdKfH-" alt="Game Architecture Diagram" width="600"/>
</p>

- ***Key Systems***
    - **Collision Detection**:
        - Hitbox-based collision system
        - Pixel-perfect overlap detection
        - Different collision types (lethal, blocking, neutral)
    - **Rendering Engine**:
        - Custom text-based sprite system
        - CHAR_INFO texture buffers
        - Dynamic theme switching
        - Special effects pipeline
    - **Object System**:
        - 20+ interconnected classes
        - Entity-component architecture
        - Polymorphic obstacle types:
            - Vehicles (trucks, motorbikes)
            - Animals (lions, rhinos)
            - Environmental (rivers, lily pads)
            - Collectibles (coins)
    - **Save System**:
        - Comprehensive game state serialization
        - Saves include:
            - Player positions/scores
            - Obstacle states
            - Game timers
            - Collected items

- ***UML Diagram***:
<h3 align="center">🧩 Game Architecture Diagram</h3>

<p align="center">
    <img src="https://drive.google.com/uc?export=view&id=13KAYuHn3KDXljekYSCtONESNWjZ38eij" alt="Game Architecture Diagram" width="600"/>
</p>
See more in `presentation.pptx` 

### 4. Technical Stack
- **Core**: C++17 (OOP Design Patterns)
- **APIs**: Windows.h (Console manipulation)
- **Audio**: MCI (Media Control Interface)
- **Concurrency**: std::thread
- **Memory Management**: Custom allocators
 
## II. Getting Started
### 1. Prerequisites
```bash
Windows OS
Visual Studio 2019+ (or compatible C++17 compiler)
```

### 2. Compilation & Execution
``` bash
# Clone repository
git clone https://github.com/pipoiwoczz/Crossing_Game_OOP.git

# Open solution in Visual Studio
Crossing_Game_OOP.sln

# Build and run (Debug/Release)
```

### 3. Controls
- **Player 1**: Arrow keys
- **Player 2**: WASD
- **Menu Navigation**: Enter/Escape keys
- **Skills**: Number keys 1-4

## III. Key Technical Components
### 1. Collision Detection Pseudocode
```cpp
bool isOverlap(Hitbox A, Hitbox B) {
    if (A.bottom < B.top || A.top > B.bottom) 
        return false;
    if (A.right < B.left || A.left > B.right) 
        return false;
    return true;
}
```
### 2. Random Stop System
```cpp
void randomStop() {
    for (Lane& lane : lanes) {
        lane.duration--;
        if (lane.duration <= 0) {
            resumeLane(lane);
            int randVal = rand() % 5000 - 10000;
            if (lane.duration < randVal) {
                setTrafficLight(lane, RED);
                lane.duration = rand() % 5000 + 2500;
            } else {
                setTrafficLight(lane, GREEN);
            }
        } else {
            stopLane(lane);
        }
    }
}
```
### 3. Double Buffering Architecture
```text
+-------------------+     +-------------------+
|  Update Thread    |     |  Rendering Thread |
|-------------------|     |-------------------|
| - Game logic      | ==> | - Buffer prep     |
| - Input handling  |     | - Texture compos  |
| - Physics         |     | - Console output  |
+-------------------+     +-------------------+
            ↓
+-----------------------+
| Shared Game State     |
| (Thread-safe access)  |
+-----------------------+
```

## IV. Documentation
- [Full Technical Report](https://github.com/pipoiwoczz/Crossing_Game_OOP/blob/main/Report.pdf)
- [Project Presentation](https://github.com/pipoiwoczz/Crossing_Game_OOP/blob/main/Presentation.pptx)
- [Game Demo Video](https://www.youtube.com/watch?v=PdXGWGMGf4E)

## V. Contributors
- Lê Ngọc Anh Khoa (22127196)
- Hoàng Tuý Minh (22127264)
- Nguyễn Đức Tín (22127415)
- Võ Thịnh Vượng (22127464)

University of Science - Vietnam National University, Ho Chi Minh City
*Object-Oriented Programming Course Project - December 2023*
