#ifndef USER_HPP
#define USER_HPP
#include <fstream>
#include <queue>
#include <string>

#include "Encrypter.hpp"
#include "Message.hpp"

class User : public Encrypter {
   private:
    std::string username;
    std::queue<Message> messages;

    void add_message(Message message);

   public:
    User(std::string username, size_t prime_min_bits = 40,
         size_t prime_max_bits = 50);
    ~User();

    void send_message(User& user, const std::string& message,
                      bool encrypt = false);
    std::string read_message();
    std::string read_message_undecrypted();
};

#endif
