#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>

class Message {
   private:
    std::string from;
    std::string to;
    std::string encryption;
    std::string message;

   public:
    Message(std::string from, std::string to, std::string encryption,
            std::string message)
        : from(from), to(to), encryption(encryption), message(message){};
    ~Message() { return; };

    Message(Message&&) = default; // Default move constructor
    Message& operator=(Message&&) = default; // Default move assignment operator
    Message(const Message&) = default; // Default copy constructor
    Message& operator=(const Message&) = default; // Default copy assignment operator

    std::string get_from() const { return from; }
    std::string get_to() const { return to; }
    std::string get_encryption() const { return encryption; }
    std::string get_message() const { return message; }
};

#endif