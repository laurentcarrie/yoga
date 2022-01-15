#include <string>

#include "model.h"
#define stringify( name ) # name


namespace yoga {
    const char *PositionNames[] =
            {
                    stringify(debout_flexion_avant),
                    stringify(cobra),
                    stringify(demarrage),
                    stringify(fin),
            };

    std::string getPositionName(yoga::Position position) {
        return std::string(PositionNames[position]) ;
    }

}

