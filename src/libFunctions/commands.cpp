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

#include "commands.h"
#include "timeparser.h"
#include "features.h"


namespace Commands {

    void newCode() {
        
        CodeValues parameters = Features::getCodeValues();

        fstream file(fileName.c_str(), fstream::app);
        
        json entry = { {"BRAND", parameters.brandName}, {"CODE", parameters.coupon}, {"EXPIRY", parameters.date}, {"EFFECT", parameters.effect} };

        Features::writeClearFile(entry, file);
    }

    void getCode() {

        string givenBrand = Features::getBrandName();

        fstream file(fileName.c_str(), fstream::in);
        json data;

        if (file.peek() != fstream::traits_type::eof()) {
            data = json::parse(file);
        }
        else {
            cout << "Empty file." << endl;
            file.close();
            return;
        }
        file.close();

        for (auto & entry : data) {

            if (entry.at("BRAND") == givenBrand) {

                cout << entry.dump(4) << endl;
            }
        }
        cout << endl;
    }

    void viewAll() {
        fstream file(fileName.c_str(), fstream::in);
        json data;

        if (file.peek() != fstream::traits_type::eof()) {
            data = json::parse(file);
        }
        else {
            cout << "Empty file." << endl;
            file.close();
            return;
        }
        file.close();

        cout << "All Codes:" << endl;
        for (auto & entry : data) {

            cout << entry.dump(4) << endl;

        }
        cout << endl;
    }

    void deleteExpired() {

        long currentTime_s = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();

        fstream file(fileName.c_str(), fstream::out);
        json data;

        if (file.peek() != fstream::traits_type::eof()) {
            data = json::parse(file);
        }
        else {
            cout << "Empty file." << endl;
            file.close();
            return;
        }

        for (auto & entry : data) {

            if (Features::dateConversion_s(entry.at("EXPIRY")) < currentTime_s) {

                data.erase(entry);
            }
        }

        Features::writeClearFile(data, file);
        cout << "Deleted.\n" << endl;
    }

    void deleteBrand() {

        string givenBrand = Features::getBrandName();

        fstream file(fileName.c_str(), fstream::out);
        json data;

        if (file.peek() != fstream::traits_type::eof()) {
            data = json::parse(file);
        }
        else {
            cout << "Empty file." << endl;
            file.close();
            return;
        }

        for (auto & entry : data) {
            
            if (entry.at("BRAND") == givenBrand) {

                data.erase(entry);
            }
        }

        Features::writeClearFile(data, file);
        cout << "Deleted.\n" << endl;
    }
}
