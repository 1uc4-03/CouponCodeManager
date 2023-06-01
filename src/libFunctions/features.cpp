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

#include "commands.h"
#include "timeparser.h"


namespace Features {

    long dateConversion_s(string const & date) {

        int year = std::stoi(date.substr(6, 4));
        int month = std::stoi(date.substr(3, 2));
        int day = std::stoi(date.substr(0, 2));

        system_clock::time_point date_tp = ParseTime::createDateTime(year, month, day, 23, 59, 59);

        return time_point_cast<seconds>(date_tp).time_since_epoch().count();
    }

    CodeValues getCodeValues() {

        string brandName;
        string coupon;
        string effect;
        string date;

        cout << "Enter the brand's name: ";
        cin >> brandName;
        cout << "Enter the coupon code: ";
        cin >> coupon;
        cout << "Enter the effect of the code: ";
        cin >> effect;
        cout << "Enter the date of expiry (dd/mm/yyyy): ";
        cin >> date;
        cout << endl;

        if (date.length() != 10) {
            cout << "Wrong date length. Try again." << endl;
            return getCodeValues();
        }

        std::transform(brandName.begin(), brandName.end(), brandName.begin(), ::toupper);
        std::transform(coupon.begin(), coupon.end(), coupon.begin(), ::toupper);
        std::transform(effect.begin(), effect.end(), effect.begin(), ::toupper);

        return { brandName, coupon, effect, date };
    }

    void writeClearFile(json & data, fstream & file) {

        if (file.is_open()) {

            file << std::setw(4) << data.dump() << endl;

            if (file.fail()) { cout << "writing fail" << endl; }
            else { cout << "writing success" << endl; }
        }
        else { cout << "stream not open" << endl; }
        
        file.flush();
        file.close();
    }

    string getBrandName() {

        cout << "Enter brand name: ";
        string givenBrand;
        cin >> givenBrand;
        std::transform(givenBrand.begin(), givenBrand.end(), givenBrand.begin(), ::toupper);

        return givenBrand;
    }
    
}
