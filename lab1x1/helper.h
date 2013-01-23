#ifndef HELPER_H
    #define HELPER_H
    #include "vector.h"

namespace Helper{


    Vector<std::string>& split(std::string str, std::string delim, Vector<std::string>& results);
    Vector<std::string>& split(std::string str, std::string delim);
}


#endif
