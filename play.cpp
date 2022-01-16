
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
#include <algorithm>

#include "model.h"


namespace yoga {
    std::filesystem::path song_dir;

    void set_sound_dir(std::string s) {
        song_dir = s;
    }


    std::string exec(const char *cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

    void play_list(const std::vector<std::string> &sounds) {

        std::for_each(std::begin(sounds), std::end(sounds), [](const std::string &item) {
            std::filesystem::path path(song_dir);
            path /= item;
            path.replace_extension(".wav");
            if (!std::filesystem::exists(path)) {
                std::ostringstream oss;
                oss << "path does not exist : " << path;
                throw std::runtime_error(oss.str());
            }
            std::ostringstream oss;
            oss << "play \"" << std::string(path) << "\"" ;
            std::string ret = exec(oss.str().c_str());
            std::cout << ret << std::endl;
        });


    }


    std::filesystem::path wave_path_of_duration(int duration) {
        std::ostringstream oss;
        oss << "../sounds/sleep_" << duration << ".wav";
        std::filesystem::path path(oss.str());
        if (!std::filesystem::exists(path)) {
            std::cerr << "path not found : " << path << std::endl;
            throw std::domain_error("no such path");
        }
        return path;
    }

    void play_duration(int duration) {
        std::ostringstream oss;
        oss << "play " << wave_path_of_duration(duration);
        exec(oss.str().c_str());
    }

    void play_total_duration(int duration) {
        int minutes = duration / 60;
        int seconds = (duration % 60) / 10 * 10;
        play_list({"le_temps_total_est_de", std::to_string(minutes), "minutes", std::to_string(seconds),
                   "secondes"});
        sleep(3);

    }

    void play_wav_position(yoga::Position position) {
        play_list({yoga::getPositionName(position)});
    }

    void play_position(yoga::Position position, int index, int total, int duration) {
        play_list({std::to_string(index + 1), "sur", std::to_string(total)});
        play_wav_position(position);

        // le temps de se positionner
        sleep(10);

        play_wav_position(yoga::Position::demarrage);
        play_wav_position(position);
        while (duration > 0) {
            play_duration(duration);
            sleep(10);
            duration -= 10;
        }
    }

    void play_end() {
        play_wav_position(yoga::Position::fin);
    }

}