#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;
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
#include <algorithm>

#include "commands.h"
#include "timeparser.h"


struct CodeValues {
    string brandName;
    string coupon;
    string effect;
    string date;
};

namespace Commands {

    void newCode(){
        
        CodeValues parameters = Features::getCodeValues();
        
        fstream file(fileName);
        json data = json::parse(file);

        json entry = { {"BRAND", parameters.brandName}, {"CODE", parameters.coupon}, {"EXPIRY", parameters.date}, {"EFFECT", parameters.effect} };
        data[data.size()] = entry;

        file.clear();
        file << data;

        file.close();
    }

    void getCode(){

    }

    void viewAll(){

    }

    void deleteExpired(){

        long currentTime_s = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();

        fstream file(fileName);
        json data = json::parse(file);

        for (auto entry : data) {
            if (Features::dateConversion_s(entry.at("EXPIRY")) < currentTime_s) {

                data.erase(entry);
            }
        }
        cout << "deleted." << endl;
    }

    void deleteBrand(){

        string brand;
        cin >> brand;

    }
}

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

        std::transform(brandName.begin(), brandName.end(), brandName.begin(), ::toupper);
        std::transform(coupon.begin(), coupon.end(), coupon.begin(), ::toupper);
        std::transform(effect.begin(), effect.end(), effect.begin(), ::toupper);

        return {brandName, coupon, effect, date};
    }

}
