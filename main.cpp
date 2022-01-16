
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
#include <functional>
#include <numeric>
#include "model.h"
#include "play.h"

std::vector<std::pair<yoga::Position, int>> data
        {
                {yoga::Position::debout_flexion_avant, 30},
                {yoga::Position::cobra,                30},
                {yoga::Position::enfant,                30},
                {yoga::Position::baton_gauche,                30},
                {yoga::Position::baton_droit,                30},
                {yoga::Position::enfant,                30},
                {yoga::Position::debout_flexion_avant, 60},
                {yoga::Position::cobra,                60},
                {yoga::Position::enfant,                30},
                {yoga::Position::fin,                0},
        };


void show_total_time(const std::vector<std::pair<yoga::Position, int>>& data) {
    auto f = [](int a, std::pair<yoga::Position, int> b) { return a + b.second; };
    int total_seconds = std::accumulate(data.begin(), data.end(), 0, f);

    play_total_duration(total_seconds) ;

}

int main(int argc, char **argv) {

    std::string cwd = std::filesystem::current_path();
    std::cout << cwd << std::endl;

    show_total_time(data) ;




    for (auto i: data) {
        yoga::Position p = i.first;
        int d = i.second;
        play_position(p, d);
    }

    play_end();

}
