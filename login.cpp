#include <fstream>
#include <string>

int main() {
    std::string userVerify;
    while(true) {
        std::ifstream verify;
        verify.open ("login.txt");
        verify >> userVerify;
        verify.close();

        std::ifstream user;
        user.open("users/" + userVerify + ".txt");
        
        std::ofstream submit;
        submit.open ("login.txt");

        if (user.is_open()) {
            submit << "success";
            submit.close();
            break;
        } else {
            submit << "failure";
            submit.close();
        }
    }

    while(true) {
        std::ifstream verify;
        std::string passAttempt;

        verify.open ("login.txt");
        verify >> passAttempt;
        verify.close();

        std::ifstream user;
        user.open("users/" + userVerify + ".txt");

        std::ofstream submit;
        submit.open ("login.txt");

        if (user.is_open()) {
            std::string pass;
            user >> pass;
            if (pass == passAttempt) {
                submit << "success";
                submit.close();
                break;
            }
        } else {
            submit << "failure";
            submit.close();
        }
    }
}