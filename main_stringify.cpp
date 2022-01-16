//
// Created by laurent on 16/01/2022.
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

std::vector<std::string> positions{
        "demarrage",
        "fin",
        "debout_flexion_avant",
        "cobra",
        "arbre_droit",
        "arbre_guche",
        "baton_droit",
        "baton_gauche",
        "chien_tete_en_bas",
        "chien_tete_en_haut",
        "enfant",
        "pigeon",
        "pince",
        "souffle_gorge",
        "triangle_ouverture_droite",
        "triangle_ouverture_gauche",
};


void write_model_h() {
    std::filesystem::path path("../model.h");
    std::ofstream fout(std::string(path).c_str());
    fout << R"HEREDOC(
#ifndef YOGA_MODEL_H
#define YOGA_MODEL_H

// this is generated from main_stringify.cpp
// go there to add new yoga positions

namespace yoga {

    enum Position {
)HEREDOC";

    bool first = true;
    for (auto n: positions) {
        if (first) {
            fout << "       " << n << " = 0";
            first = false;
        } else {
            fout << "," << std::endl << "       " << n;
        }
    }
    fout << R"HEREDOC(
    };
    std::string getPositionName(yoga::Position position) ;
} ;

#endif
)HEREDOC";
}


void write_model_cpp(){
    std::filesystem::path path("../model.cpp");
    std::ofstream fout(std::string(path).c_str());
    fout << R"HEREDOC(
#include <string>
#include "model.h"
#define stringify( name ) # name

namespace yoga {
    const char *PositionNames[] =
                {
)HEREDOC" ;

    for ( auto n : positions ) {
        fout << "           stringify(" << n << ")," << std::endl ;

    }
    fout << R"HEREDOC(
        } ;

        std::string getPositionName(yoga::Position position) {
            return std::string(PositionNames[position]) ;
        }
}
)HEREDOC" ;

                }

int main(int argc, char **argv) {
    std::cout << "hello world" << std::endl;
    write_model_h();
    write_model_cpp() ;

}