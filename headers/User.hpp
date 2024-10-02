#ifndef USER_HPP
#define USER_HPP
#include <fstream>
#include <queue>
#include <string>
#include <gmpxx.h>

#include "Encrypter.hpp"

class User : public Encrypter {
   private:
    std::string username;

   public:
    User(std::string username, size_t prime_min_bits, size_t prime_max_bits);
    User(std::string username, mpz_class prime_one, mpz_class prime_two, mpz_class beta, mpz_class d);
    User(const std::string& file_path);
    User(std::string username, mpz_class prime_product, mpz_class exponent);
    User(){};
    ~User();

    User(User&&) = default; // Default move constructor
    User& operator=(User&&) = default; // Default move assignment operator
    User(const User&) = default; // Default copy constructor
    User& operator=(const User&) = default; // Default copy assignment operator
    bool operator==(const User& other) const;

    friend std::ostream& operator<<(std::ostream& o, User& user);
    friend std::istream& operator>>(std::istream& i, User& user);
    std::string get_username() { return this->username; }

    void write_public_info(std::string filepath);
    static User read_public_info(std::string filepath);
};

#endif
