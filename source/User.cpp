#include "../headers/User.hpp"

void User::add_message(Message message) { this->messages.push(message); }

User::User(std::string username, size_t prime_min_bits, size_t prime_max_bits)
    : Encrypter(prime_min_bits, prime_max_bits), username(username) {}

User::~User() {}

void User::send_message(User& user, const std::string& message, bool encrypt) {
    if (encrypt) {
        user.add_message(
            Message(this->username, user.username, "RSA",
                    Encrypter::encrypt(message, user.get_public_key())));
    } else {
        user.add_message(
            Message(this->username, user.username, "None", message));
    }
}

std::string User::read_message() {
    Message current_message = this->messages.front();
    messages.pop();
    if (current_message.get_encryption() != "None") {
        // Implement Encrypter factory
        return Encrypter::decrypt(current_message.get_message());
    }
    return current_message.get_message();
}

std::string User::read_message_undecrypted() {
    return this->messages.front().get_message();
}