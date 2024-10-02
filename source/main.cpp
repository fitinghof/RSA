#include <fstream>
#include <iostream>

#include "../headers/User_interface.hpp"

int main(int argc, char* args[]) {
    User_interface ui;
    while (true) {
        std::cout << "1. Decrypt message\n"
                     "2. Add friend\n"
                     "3. Print your public key\n"
                     "4. Encrypt message\n"
                     "5. Quit\n";

        size_t choice;
        while (true) {
            try {
                std::cin >> choice;
            } catch (...) {
            }
            if (choice > 0 && choice <= 5) break;
        }
        try {
            switch (choice) {
                case 1:
                    ui.decrypt_message();
                    break;
                case 2:
                    ui.add_friend();
                    break;
                case 3:
                    ui.print_public_user_data();
                    break;
                case 4:
                    ui.encrypt_message();
                    break;
                case 5:
                    return 0;
                default:
                    throw std::runtime_error("Something went terribly wrong");
            }
        } catch (...) {
            std::cout << "I have implemented so called lazy error handling, or "
                         "not really errorhandling at all, point is, you "
                         "fucked something and if your lucky nothing got "
                         "fucked up howerver I make no garantees.\n";
        }
    }
}