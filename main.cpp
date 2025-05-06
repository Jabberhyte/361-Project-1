#include <iostream>
#include <fstream>
#include <string>

void tutorial() {
    std::cout << "Welcome to the planner! This is a little tutorial to get you started." << std::endl;
    std::cout << "This planner has 4 main functions" << std::endl << std::endl;
    std::cout << "1. Preview Week" << std::endl;
    std::cout << "Here you can get a preview of how busy your week is." << std::endl;
    std::cout << "You will be shown each day of the current week, showing what plans are there and when." << std::endl;
    std::cout << "It will also show you your three largest openings that you have during the week, helpful to find time for something new!" << std::endl << std::endl;

    std::cout << "2. Date Search" << std::endl;
    std::cout << "Here you can look up a specific day at any point int the future and see chat your plans are." << std::endl;
    std::cout << "This will allow you to look at your plans in more detail then the week view, showing any description you may have added!" << std::endl;
    std::cout << "It will also show the amount of time in between your plans so you can easily see when you'll have free time." << std::endl << std::endl;

    std::cout << "3. Create an Event" << std::endl;
    std::cout << "Here is where you put new events in your planner!" << std::endl;
    std::cout << "Along with important things like time and date, you can add a description that can help remind you important things like location!" << std::endl<< std::endl;
    
    std::cout << "4. Export Planner" << std::endl;
    std::cout << "This allows you to export all your plans in a given date range into a portable file that you can share with others." << std::endl;
    std::cout << "This can be helpful to easily compare your plans with someone else!" << std::endl << std::endl;
}

void week() {
    return;
}

void day() {
    return;
}

void createEvent() {
    return;
}

void exportPlans() {
    return;
}



bool createUser() {
    std::string name;
    std::string password;

    std::cout << "Please enter your prefered name: ";
    std::cin >> name;

    std::ofstream user("users/" + name + ".txt");
    
    std::cout << "Please enter your prefered password.  This password cannot be retrieved later if forgotten: ";
    std::cin >> password;
    user << password;

    while(true) {
        std::string choice;
        std::cout << "Would you like to see the tutorial to get you situated? (y/n)" << std::endl;
        std::cin >> choice;

        if (choice == "y") {
            tutorial();
            break;
        } else if (choice == "n") {
            break;
        } else {
            std::cout << "Invalid input, please enter y or n" << std::endl;
        }
    }
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

void directory() {
    int choice;

    std::cout << "Welcome! If you would like to preview your week, enter 1." << std::endl;
    std::cout << "If you would like to look up a specific day, enter 2." << std::endl;
    std::cout << "If you would like to create a new event, enter 3." << std::endl;
    std::cout << "If you would like to export your plans to a file, enter 4." << std::endl;
    std::cout << "If you would like to see the tutorial, enter 5." << std::endl;
    std::cout << "If you would like to quit the program, enter anything else." << std::endl;

    std::cin >> choice;

    if (choice == 1) {
        week();
        directory();
    } else if (choice == 2) {
        day();
        directory();
    } else if (choice == 3) {
        createEvent();
        directory();
    } else if (choice == 4) {
        exportPlans();
        directory();
    } else if (choice == 5) {
        tutorial();
        directory();
    } else {
        return;
    }
}

int main() {
    bool loginAttempt = login(0);
    
    if (loginAttempt){
        directory();
    }
}