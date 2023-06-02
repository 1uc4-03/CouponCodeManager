#include <fstream>
using std::fstream;
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
#include <exception>

#include "commands.h"
#include "timeparser.h"
#include "features.h"


namespace Commands {

    void newCode() {
        
        CodeValues parameters = Features::getCodeValues();
        json data = Features::readFile(fileName);
        
        fstream outfile(fileName.c_str(), fstream::out);

        json entry = { {"BRAND", parameters.brandName}, {"CODE", parameters.coupon}, {"EFFECT", parameters.effect}, {"EXPIRY", parameters.date} };
        data[Features::createId()] = entry;

        Features::writeClearFile(data, outfile);
    }

    void getCode() {

        string givenBrand = Features::getBrandName();

        json data;
        try { data = Features::readFile(fileName, true); }
        catch (std::invalid_argument const & e) {
            cout << e.what() << endl;
            return;
        }

        for (auto & entry : data) {

            if (entry.at("BRAND") == givenBrand) {

                cout << entry.dump(4) << endl;
            }
        }
        cout << endl;
    }

    void viewAll() {

        json data;
        try { data = Features::readFile(fileName, true); }
        catch (std::invalid_argument const & e) {
            cout << e.what() << endl;
            return;
        }

        cout << "All Codes:\n" << endl;

        for (auto & entry : data) {
            cout << entry.dump(4) << endl;
        }
        cout << endl;
    }

    void deleteExpired() {

        long currentTime_s = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();

        json data;
        try { data = Features::readFile(fileName, true); }
        catch (std::invalid_argument const & e) {
            cout << e.what() << endl;
            return;
        }

        for (auto & entry : data.items()) {

            if (Features::dateConversion_s(entry.value().at("EXPIRY")) <= currentTime_s) {

                data.erase(entry.key());
            }
        }

        fstream outfile(fileName.c_str(), fstream::out);

        Features::writeClearFile(data, outfile);
        cout << "Deleted.\n" << endl;
    }

    void deleteBrand() {

        string givenBrand = Features::getBrandName();

        json data;
        try { data = Features::readFile(fileName, true); }
        catch (std::invalid_argument const & e) {
            cout << e.what() << endl;
            return;
        }

        for (auto & entry : data.items()) {
            
            if (entry.value().at("BRAND") == givenBrand) {

                data.erase(entry.key());
            }
        }

        fstream outfile(fileName.c_str(), fstream::out);

        Features::writeClearFile(data, outfile);
        cout << "Deleted.\n" << endl;
    }
}
