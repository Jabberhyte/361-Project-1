#include <iostream>
#include <fstream>

bool login(int count) {
    std::cout << "Hello!  Please enter 1 if you are a returning user.  If you are a new uaser, please enter 2: ";

    int initial;
    std::cin >> initial;

    if (initial == 1) {
        std::string username;
        std::string password;

        std::cout << "Please enter your username: ";
        std::cin >> username;

        std::ofstream submit;
        submit.open ("login.txt");
        submit << username;
        submit.close();

        std::ifstream verify;
        std::string userVerify;
        verify.open ("login.txt");
        verify >> userVerify;

        if (userVerify == "failure") {
            std::cout << "Can't find user of that name" << std::endl;
            count += 1;
            if (count < 3) {
                login(count);
            } else {
                return false;
            }
        }

        std::cout << "Please enter your password: ";
        std::cin >> password;


        submit.open ("login.txt");
        submit << password;
        submit.close();

        verify.open ("login.txt");
        verify >> userVerify;

        if (userVerify == "failure") {
            std::cout << "Can't find user of that name" << std::endl;
            count += 1;
            if (count < 3) {
                login(count);
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    return true;

}

int main() {
    bool loginAttempt = login(0);
}