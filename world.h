#ifndef GAME_OF_LIFE_WORLD_H
#define GAME_OF_LIFE_WORLD_H

#include <string>


namespace Params {
    const int width = 100;
    const int height = 100;
};


class World{

private:
    int countNeighbours(int i, int j);
    void step();
    void write(const std::string& filepath, int epoch);

public:
    int grid[Params::width][Params::height]{};
    World();
    World(const std::string& filepath, int epoch);
    void run(int epochs, const std::string& filepath);
    void print();
};

#endif //GAME_OF_LIFE_WORLD_H
