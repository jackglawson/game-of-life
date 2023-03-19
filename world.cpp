#include <iostream>
#include <string>
#include <fstream>
#include "world.h"


World::World(){
    for (int i = 0; i < Params::height; i++){
        for (int j = 0; j < Params::width; j++){
            World::grid[i][j] = rand() % 2;
        }
    }
}

World::World(const std::string& filepath, int epoch) {
    // Will read the first state from filepath
    std::ifstream inFile(filepath);
    if (inFile.is_open()) {
        // this is really dumb
        int x;
        for (int i = 0; i < Params::width * Params::height * epoch; i++){
            inFile >> x;
        }
        for (int i = 0; i < Params::height; i++) {
            for (int j = 0; j < Params::width; j++) {
                inFile >> grid[i][j];
            }
        }
        inFile.close();
    } else {
        std::cout << "Unable to open file for reading." << std::endl;
    }
}


int World::countNeighbours(int i, int j){
    int count = 0;
    for (int neighbour_i = i-1; neighbour_i <= i+1; neighbour_i++) {
        for (int neighbour_j = j-1; neighbour_j <= j+1; neighbour_j++) {
            if ((neighbour_i == 0) && (neighbour_j == 0)){
                continue;
            }
            if ((neighbour_i < 0) || (neighbour_j < 0) || (neighbour_i >= Params::height) || (neighbour_j >= Params::width)){
                continue;
            }
            count += grid[neighbour_i][neighbour_j];
        }
    }
    return count;
}

void World::step(){
    for (int i = 0; i < Params::height; i++){
        for (int j = 0; j < Params::width; j++){
            if (((countNeighbours(i, j) < 2) || (countNeighbours(i, j) > 3)) && (grid[i][j] == 1)){
                grid[i][j] = 0;
            }
            else if ((countNeighbours(i, j) == 3) && (grid[i][j] == 0)){
                grid[i][j] = 1;
            }
        }
    }
}

void World::run(int epochs, const std::string& filepath){
    for (int n = 0; n < epochs; n++){
        write(filepath, n);
        step();
    }
}

void World::write(const std::string& filepath, int epoch) {
    std::ofstream outFile;
    if (epoch == 0){
        outFile = std::ofstream(filepath);
    }
    else{
        outFile = std::ofstream(filepath, std::ios_base::app);
    }
    if (outFile.is_open()) {
        for (int i = 0; i < Params::height; i++) {
            for (int j = 0; j < Params::width; j++) {
                outFile << grid[i][j] << ' ';
            }
        }
        outFile.close();
    }
    else
    {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

void World::print() {
    const char *c;
    for (int i = 0; i < Params::height; i++) {
        for (int j = 0; j < Params::width; j++) {
            if (grid[i][j] == 0) {
                c = ".";
            }
            else{
                c = "#";
            }
            std::cout << c << " ";
        }
        std::cout << "\n";
    }
}

