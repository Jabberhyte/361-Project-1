#include <fstream>
#include <string>

int main() {
    std::string userVerify;
    while(true) {
        std::ifstream verify("login.txt");
        std::string line, command, data;
        while (std::getline(verify, line)) {
            if (line.rfind("COMMAND:", 0) == 0) {
                size_t colon1 = line.find(':', 8);
                command = line.substr(8, colon1 - 8);
                data = line.substr(colon1 + 1);
            }
        }
        verify.close();

        std::ofstream out("login.txt");
        if (command == "USERNAME") {
            std::ifstream user("users/" + data + ".txt");
            if (user.is_open()) {
                userVerify = data;
                out << "COMMAND:USERNAME:" << data << "\nRESPONSE:success";
            } else {
                out << "COMMAND:USERNAME:" << data << "\nRESPONSE:failure";
            }
        } else if (command == "PASSWORD") {
            std::ifstream user("users/" + userVerify + ".txt");
            std::string storedPass;
            user >> storedPass;
            if (storedPass == data) {
                out << "COMMAND:PASSWORD:" << data << "\nRESPONSE:success";
            } else {
                out << "COMMAND:PASSWORD:" << data << "\nRESPONSE:failure";
            }
        } else {
            out << "RESPONSE:pending";
        }
        out.close();
    }
}