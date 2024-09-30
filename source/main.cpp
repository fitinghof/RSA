#include <fstream>
#include <iostream>

#include "../headers/User.hpp"
#include "../headers/poem.hpp"

int main(int argc, char* args[]) {
    static const size_t lower_prime_size = 5000;
    User user1("Simon", lower_prime_size, lower_prime_size + 100);
    User user2("Pelle", lower_prime_size, lower_prime_size + 100);

    user1.send_message(
        user2,
        "Hello, this is my diary, it is very long thanks to my very great and "
        "very duper long primes. Thanks for coming to my ted talk.\n",
        true);

    user1.send_message(user2, poem, true);

    std::cout << "encrypted message:\n"
              << user2.read_message_undecrypted() << "\n\n";
    std::cout << "exponent:\n" << user2.get_public_key().exponent << "\n\n";
    std::cout << "prime product:\n"
              << user2.get_public_key().prime_product << "\n\n";

    std::cout << user2.read_message() << "\n";
    std::cout << user2.read_message() << "\n";
    std::cout << poem.size() << "\n";
}