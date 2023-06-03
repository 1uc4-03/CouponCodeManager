#ifndef COUPON_CODE_MANAGER_COMMANDS_H
#define COUPON_CODE_MANAGER_COMMANDS_H

#include <map>
#include <string>


// custom return object for data input
struct CodeValues {
    std::string brandName;
    std::string coupon;
    std::string effect;
    std::string date;
};

namespace Commands {

    void newCode();
    void getCode();
    void viewAll();
    void deleteExpired();
    void deleteBrand();

    typedef void (*FnPtr)();

    // map of commands and their function pointers
    inline std::map<char, FnPtr> commands = {
        {'n', &newCode},
        {'g', &getCode},
        {'v', &viewAll},
        {'e', &deleteExpired},
        {'b', &deleteBrand}
    };

    inline std::string const displayText = "This is the coupon code manager. Manage your coupon codes by using the following commands:\n'n' stores a new code.\n'g' gets a code by brand name.\n'v' displays all coupon codes.\n'e' deletes all expired coupon codes.\n'b' deletes a code by brand name.\n";

    // name of the file storing the data
    inline std::string const fileName = "couponcodes.json";
}

#endif // COUPON_CODE_MANAGER_COMMANDS_H
