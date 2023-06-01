#ifndef COUPON_CODE_MANAGER_COMMANDS_H
#define COUPON_CODE_MANAGER_COMMANDS_H

#include <map>
#include <string>


enum class FileHeader;
struct CodeValues;

namespace Commands {

    void newCode();
    void getCode();
    void viewAll();
    void deleteExpired();
    void deleteBrand();

    typedef void (*FnPtr)();

    inline std::map<char, FnPtr> commands = {
        {'n', &newCode},
        {'g', &getCode},
        {'v', &viewAll},
        {'e', &deleteExpired},
        {'b', &deleteBrand}
    };

    inline std::string const displayText = "This is the coupon code manager. Manage your coupon codes by using the following commands:\n'n' stores a new code.\n'g' gets a code by brand name.\n'v' displays all coupon codes.\n'e' deletes all expired coupon codes.\n'b' deletes a code by brand name.\n";

    inline std::string const fileName = "couponcodes.json";
}

namespace Features {

    CodeValues getCodeValues();
    long dateConversion_s(std::string const & date);

}

#endif // COUPON_CODE_MANAGER_COMMANDS_H
