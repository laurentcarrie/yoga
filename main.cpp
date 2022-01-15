
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <filesystem>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "model.h"
#include "play.h"

std::vector<std::pair<yoga::Position, int>> data
        {
                {yoga::Position::debout_flexion_avant, 30},
    {yoga::Position::cobra, 30},
                {yoga::Position::debout_flexion_avant, 60},
                {yoga::Position::cobra, 60}
        };

int main(int argc, char **argv) {

    std::string cwd = std::filesystem::current_path();
    std::cout << cwd << std::endl;

    for (auto i: data) {
        yoga::Position p = i.first;
        int d = i.second;
        play_position(p, d);
    }

    play_end() ;

}
