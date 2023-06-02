#ifndef LIBFUNCTIONS_FEATURES_H
#define LIBFUNCTIONS_FEATURES_H

#include <string>
#include<nlohmann/json.hpp>
#include <fstream>

#include "commands.h"


namespace Features {

    CodeValues getCodeValues(string brandName = "", string coupon = "", string effect = "", string date = "");
    long dateConversion_s(std::string const & date);
    void writeClearFile(nlohmann::json & data, std::fstream & file);
    std::string getBrandName();
    unsigned int createId();

}

#endif // LIBFUNCTIONS_FEATURES_H
