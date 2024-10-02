#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "User.hpp"

class User_interface {
   private:
    const std::filesystem::path user_file_path = "this_is_you_no_leaking";
    const std::filesystem::path friends_directory = "friends";

    void load_friends();
    void load_user();
    User user;
    std::vector<User> friends;

   public:
    User_interface();
    ~User_interface();

    User& display_friend_choice();

    void print_public_user_data();

    void decrypt_message();

    void encrypt_message();

    void add_friend();

    void clear_terminal();
};



#endif