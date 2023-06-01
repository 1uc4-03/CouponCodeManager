#ifndef LIBFUNCTIONS_FEATURES_H
#define LIBFUNCTIONS_FEATURES_H

#include <string>
#include<nlohmann/json.hpp>
#include <fstream>

#include "commands.h"


namespace Features {

    CodeValues getCodeValues();
    long dateConversion_s(std::string const & date);
    void writeClearFile(nlohmann::json const & data, std::fstream & file);
    std::string getBrandName();

}

#endif // LIBFUNCTIONS_FEATURES_H