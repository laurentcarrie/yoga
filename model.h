
#ifndef YOGA_MODEL_H
#define YOGA_MODEL_H


namespace yoga {

    enum Position {
        debout_flexion_avant = 0,
        cobra,
        demarrage,
        end
    };

    std::string getPositionName(yoga::Position position) ;

}


#endif
