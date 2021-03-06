#ifndef YOGA_PLAY_H
#define YOGA_PLAY_H

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

namespace  yoga {

    void set_sound_dir(std::string);

    std::string exec(const char *cmd);

    std::filesystem::path wave_path_of_duration(int duration);

    void play_duration(int duration);

    void play_wav_position(yoga::Position position);

    void play_position(yoga::Position position, int index, int toal, int duration);

    void play_end();

    void play_total_duration(int duration);
}

#endif