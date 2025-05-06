#include <fstream>
#include <string>

int main() {
    while(true) {
        std::ifstream verify;
        std::string userVerify;
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
        } else {
            submit << "failure";
            submit.close();
        }
    }
}