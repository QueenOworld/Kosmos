# Kosmos
## What is this?

Kosmos is a project I'm working on that I want to turn into a complete game.
All graphics will be text based, and it will have a frame with 3D rendering.
I'm just starting this and working out how I make this, and have no deadlines set for myself, so it will grow slowly over time.

## Controls
- Move the telescope around with WASD and arrow keys
- Roll the telescope counterclockwise with Q and clockwise with E
- Zoom out with Z and in with X
- Reset zoom with C
- Increase movement distance with + and decrease with -
- Reset movement distance with 0
- Inpect cosmic object with spacebar (unfinished)

This list is subject to change

## Compilation

### Release
```shell
cmake -DCMAKE_BUILD_TYPE=Release -Bbuild/Release
cmake --build build/Release
```
### Debug
```shell
cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild/Debug
cmake --build build/Debug
```

## Todo
- Add a proper gameplay loop
- Add signal scanning and audio playback via procedural sound generation and some prerecorded audio
- Make a main menu
- Add the second half of the UI that sits next to the viewport, with information on inspected objects, an audio graph, and a smaller viewport with a view of the object in more detail
- Properly implement landscape and portrait
- Maybe work on a windows port, currently only testing on linux and window resizing relies on the SIGWINCH signal
- Add progression, a proper goal to reach, and saving
