#include "../headers/User_interface.hpp"

User_interface::User_interface() {
    load_user();
    load_friends();
}
User_interface::~User_interface() {}

void User_interface::load_friends() {
    namespace fs = std::filesystem;

    if (!std::filesystem::exists(friends_directory) || !std::filesystem::is_directory(friends_directory))
        std::filesystem::create_directory(friends_directory);
    // Iterate over all the files in the directory
    for (const auto& entry : fs::directory_iterator(friends_directory)) {
        // Check if the entry is a regular file (not a directory)
        if (fs::is_regular_file(entry.path())) {
            User new_friend = User::read_public_info(entry.path().string());
            friends.emplace_back(new_friend);
            std::cout << "Loaded friend: " << new_friend.get_username() << std::endl;
        }
    }
}

void User_interface::load_user() {
    std::ifstream file(user_file_path);
    if (!file.is_open()) {
        std::cout << "No user found, creating a new one\nSelect your username: "
                  << std::flush;
        std::string username;
        std::cin >> username;
        this->user = User(username, 5000, 5100);
        std::cout << "User " << user.get_username() << " created\n";
        std::ofstream write(user_file_path);
        write << this->user;
        return;
    }
    file >> this->user;
    std::cout << "Loaded user: " << user.get_username() << "\n";
}

User& User_interface::display_friend_choice() {
    clear_terminal();
    std::cout << "Select a friend:" << std::endl;
    for (size_t i = 0; i < this->friends.size(); i++) {
        std::cout << i + 1 << ". " << friends[i].get_username() << std::endl;
    }
    size_t input;
    while (true) {
        try {
            std::cin >> input;
            if (input > 0 && input <= this->friends.size())
                return this->friends[input - 1];
        } catch (...) {}
    }
    clear_terminal();
}

void User_interface::print_public_user_data() {
    clear_terminal();
    std::cout << "Username: " << user.get_username() << "\n\nExponent:\n"
              << user.get_public_key().exponent << "\n\nPrime product:\n"
              << user.get_public_key().prime_product << "\n\n";
    std::cout << "Type something to return ";
    std::string temp;
    std::cin >> temp;
    clear_terminal();
}

void User_interface::decrypt_message() {
    clear_terminal();
    std::cout << "Paste the message:\n";
    std::string encryption;
    std::cin.clear();
    std::cin.ignore();
    getline(std::cin, encryption);
    std::cout << "Decrypted message:\n\n" << this->user.decrypt(encryption) << "\n" << "Type something to return\n";
    std::cin >> encryption;
    clear_terminal();
    return;
}

void User_interface::add_friend() {
    std::string username;
    mpz_class exponent, prime_product;
    clear_terminal();
    std::cout << "Type the username of the friend:\n";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> username;
    std::cout << "Paste the prime product:\n";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> prime_product;
    std::cout << "Paste the Exponent:\n";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> exponent;

    User new_friend(username, prime_product, exponent);
    friends.push_back(new_friend);
    new_friend.write_public_info(friends_directory / (new_friend.get_username() + "##FILE"));
    clear_terminal();
    std::cout << username << " Successfully added\n";
}

void User_interface::encrypt_message(){
    User toUser = this->display_friend_choice();
    std::string message;
    std::cout << "Write your message:\n";
    std::cin.clear();
    std::cin.ignore();
    getline(std::cin, message);
    std::cout << "\nYour encrypted message:\n" << user.encrypt(message, toUser.get_public_key()) << "\n";
}

void User_interface::clear_terminal() {
#ifdef _WIN32
    // If the system is Windows
    system("cls");
#else
    // If the system is Linux/Unix/macOS
    system("clear");
#endif
}