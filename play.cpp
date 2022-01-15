
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



std::string exec(const char* cmd) {
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
std::filesystem::path wave_path_of_position(yoga::Position position) {
    std::string name = yoga::getPositionName(position) ;
    std::ostringstream oss ;
    oss << "../sounds/" << name << ".wav"  ;
    std::filesystem::path path(oss.str()) ;
    if (!std::filesystem::exists(path)) {
        std::cerr << "path not found : " << path << std::endl ;
        throw std::domain_error("no such path") ;
    }
    return path ;
}

std::filesystem::path wave_path_of_duration(int duration) {
    std::ostringstream oss ;
    oss << "../sounds/sleep_" << duration << ".wav"  ;
    std::filesystem::path path(oss.str()) ;
    if (!std::filesystem::exists(path)) {
        std::cerr << "path not found : " << path << std::endl ;
        throw std::domain_error("no such path") ;
    }
    return path ;
}

void play_duration(int duration) {
    std::ostringstream  oss ;
    oss << "play " << wave_path_of_duration(duration) ;
    exec(oss.str().c_str()) ;
}

void play_wav_position(yoga::Position position) {
    std::ostringstream  oss ;
    oss << "play " << wave_path_of_position(position) ;
    exec(oss.str().c_str()) ;

}

void play_position(yoga::Position position,int duration) {
    play_wav_position(position) ;
    // le temps de se positionner
    sleep(10) ;

    play_wav_position(yoga::Position::demarrage) ;
    play_wav_position(position) ;
    while (duration>0) {
        play_duration(duration) ;
        sleep(10) ;
        duration-=10 ;
    }
}

void play_end() {
    play_wav_position(yoga::Position::end) ;
}
