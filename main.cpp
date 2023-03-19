#include <iostream>
#include <fstream>
#include "display.h"
#include "world.h"

int main() {
    World world = World();

    world.run("test.txt");
    display("test.txt");
    create_gif("test.txt", "test.gif");

    return 0;
}
