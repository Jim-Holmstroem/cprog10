#include "helper.h"

Vector<std::string>& Helper::split(std::string str, std::string delim, Vector<std::string>& results){
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos ){
        if(cutAt > 0){
            results.push_back(str.substr(0,cutAt));
        }
    str = str.substr(cutAt+1);
    }
    if(str.length() > 0){ //slatten
        results.push_back(str);
    }
    return results;
}

//TODO: fixa med referenspekare och new och liknande för att det ska funka "på riktigt"

Vector<std::string>& Helper::split(std::string str, std::string delim){
    Vector<std::string>* results = new Vector<std::string>();
    return Helper::split(str,delim,*results);
}


