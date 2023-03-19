#include <iostream>
#include "display.h"
#include "world.h"

int main() {
    World world = World();
    world.run(2000, "test.txt");

    World test = World("test.txt", 11);
    test.print();

    display("test.txt");

    return 0;
}
