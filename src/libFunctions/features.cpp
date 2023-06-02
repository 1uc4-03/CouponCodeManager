#include <fstream>
using std::fstream;
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>
using std::string;
#include <chrono>
using namespace std::chrono;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <algorithm>
#include <sstream>
using std::stringstream;
#include <exception>

#include "commands.h"
#include "timeparser.h"
#include "features.h"


namespace Features {

    long dateConversion_s(string const & date) {

        int year = std::stoi(date.substr(6, 4));
        int month = std::stoi(date.substr(3, 2));
        int day = std::stoi(date.substr(0, 2));

        if(year < 1900 || month > 12 || day > 31) {
            throw std::invalid_argument("Not a real date.\n");
        }

        system_clock::time_point date_tp = ParseTime::createDateTime(year, month, day, 23, 59, 59);

        return time_point_cast<seconds>(date_tp).time_since_epoch().count();
    }

    CodeValues getCodeValues(string brandName, string coupon, string effect, string date) {

        if (brandName.empty()) {
            brandName = getBrandName();
        }
        if (coupon.empty()) {
            cout << "Enter the coupon code: ";
            std::getline(cin, coupon);
        }
        if (effect.empty()) {
            cout << "Enter the effect of the code: ";
            std::getline(cin, effect);
        }
        if (date.empty()) {
            cout << "Enter the date of expiry (dd/mm/yyyy): ";
            std::getline(cin, date);
        }
        cout << endl;

        try {
            dateConversion_s(date);
        }
        catch (std::invalid_argument const & e) {
            cout << e.what() << endl;
            return getCodeValues(brandName, coupon, effect);
        }

        return { brandName, coupon, effect, date };
    }

    void writeClearFile(json & data, fstream & file) {

        if (file.is_open()) {

            file << data.dump(4) << endl;

            if (file.fail()) { cout << "Writing failed.\n" << endl; }
            else { cout << "Writing succeeded.\n" << endl; }
        }
        else { cout << "Stream is not open.\n" << endl; }
        
        file.flush();
        file.close();
    }

    string getBrandName() {

        cout << "Enter the brand name (no spaces): ";
        string givenBrand;
        std::getline(cin, givenBrand);

        if (givenBrand.find(' ') != string::npos) { return getBrandName(); }

        std::transform(givenBrand.begin(), givenBrand.end(), givenBrand.begin(), ::toupper);

        return givenBrand;
    }

    string createId() {

        static unsigned int id = 1;
        stringstream ss;
        ss << id++;
        return ss.str();
    }

    json readFile(string const & filename, bool must_not_be_empty) {

        fstream infile(filename, fstream::in);
        json data;

        if (infile.peek() != fstream::traits_type::eof()) {
            infile >> data;
        }
        else {
            if (must_not_be_empty) {
                infile.close();
                throw std::invalid_argument("Empty file.");
            }
        }
        infile.close();

        return data;
    }

}
