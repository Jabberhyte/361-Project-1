#include <iostream>
#include <fstream>
#include <string>

bool createUser() {
    std::string name;
    std::string password;

    std::cout << "Please enter your prefered name: ";
    std::cin >> name;

    std::ofstream user("users/" + name + ".txt");
    
    std::cout << "Please enter your prefered password.  This password cannot be retrieved later if forgotten: ";
    std::cin >> password;
    user << password;

    return true;
}

void writeSubmission(const std::string& cmd, const std::string& data) {
    std::ofstream submit("login.txt");
    submit << "COMMAND:" << cmd << ":" << data << "\nRESPONSE:pending";
    submit.close();
}


std::string waitForResponse() {
    std::string line;
    for (int i = 0; i < 100; ++i) {
        std::ifstream verify("login.txt");
        while (std::getline(verify, line)) {
            if (line.rfind("RESPONSE:", 0) == 0) {
                std::string result = line.substr(9);
                if (result != "pending") {
                    return result;
                }
            }
        }
    }
    return "timeout";
}

bool login(int count) {
    std::cout << "Hello!  Please enter 1 if you are a returning user.  If you are a new uaser, please enter 2: ";

    int initial;
    std::cin >> initial;

    if (initial == 2) {
        return createUser();
    } else if (initial == 1) {
        std::string username, password, userVerify;

        std::cout << "Please enter your username: ";
        std::cin >> username;

        
        writeSubmission("USERNAME", username);

        userVerify = waitForResponse();

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

        writeSubmission("PASSWORD", password);

        userVerify = waitForResponse();

        if (userVerify == "failure") {
            std::cout << "Can't find user of that name" << std::endl;
            count += 1;
            if (count < 3) {
                login(count);
            } else {
                return false;
            }
        } else {
            std::cout << "login successful" << std::endl;

            writeSubmission("FINISHED", "finished");

            return true;
        }
    }

    return true;

}

int main() {
    bool loginAttempt = login(0);
}