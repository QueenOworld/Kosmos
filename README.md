# What is this?

Kosmos is a project I'm working on that I want to turn into a complete game.
All graphics will be text based, and it will have a frame with 3D rendering.
I'm just starting this and working out how I make this, and have no deadlines set for myself, so it will grow slowly over time.

# Compilation

-  ## Linux
    I didn't add a make file, so you can run this in the root of the project instead:
    
    ```shell
    g++ -std=c++23 -O3 -g $(find . -type f -iregex ".*\.cpp") -o main
    ```