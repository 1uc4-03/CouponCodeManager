#include <fstream>
using std::fstream;
using std::ifstream;
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <chrono>
using namespace std::chrono;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "commands.h"
#include "timeparser.h"
#include "features.h"


namespace Commands {

    void newCode() {
        
        CodeValues parameters = Features::getCodeValues();
        
        fstream file(fileName);
        json data = json::parse(file);

        json entry = { {"BRAND", parameters.brandName}, {"CODE", parameters.coupon}, {"EXPIRY", parameters.date}, {"EFFECT", parameters.effect} };
        data.push_back(entry);

        Features::writeClearFile(data, file);
    }

    void getCode() {

        string givenBrand = Features::getBrandName();

        ifstream file(fileName);
        json data = json::parse(file);
        file.close();

        for (auto entry : data) {

            if (entry.at("BRAND") == givenBrand) {

                cout << entry.dump() << endl;
            }
        }
        cout << endl;
    }

    void viewAll() {
        ifstream file(fileName);
        json data = json::parse(file);
        file.close();

        for (auto entry : data) {
            cout << entry.dump() << endl;
        }
        cout << endl;
    }

    void deleteExpired() {

        long currentTime_s = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();

        fstream file(fileName);
        json data = json::parse(file);

        for (auto entry : data) {

            if (Features::dateConversion_s(entry.at("EXPIRY")) < currentTime_s) {

                data.erase(entry);
            }
        }

        Features::writeClearFile(data, file);
        cout << "deleted." << endl;
    }

    void deleteBrand() {

        string givenBrand = Features::getBrandName();

        fstream file(fileName);
        json data = json::parse(file);

        for (auto entry : data) {
            
            if (entry.at("BRAND") == givenBrand) {

                data.erase(entry);
            }
        }

        Features::writeClearFile(data, file);
        cout << "deleted." << endl;
    }
}
