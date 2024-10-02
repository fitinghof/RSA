#include "../headers/User.hpp"

// void User::add_message(Message message) { this->messages.push(message); }

User::User(std::string username, size_t prime_min_bits, size_t prime_max_bits)
    : Encrypter(prime_min_bits, prime_max_bits), username(username) {}

User::User(std::string username, mpz_class prime_one, mpz_class prime_two,
           mpz_class beta, mpz_class d)
    : Encrypter(prime_one, prime_two, beta, d), username(username) {}

User::User(const std::string& file_path) {
    std::ifstream file(file_path);
    if (file.is_open()) {
        file >> *this;
    } else {
        throw std::runtime_error("unable to open file");
    }
}

User::User(std::string username, mpz_class prime_product, mpz_class exponent)
    : username(username) {
    Encrypter();
    this->set_public_key(prime_product, exponent);
}

User::~User() {}
bool User::operator==(const User& other) const {
    if (!(this->username == other.username)) std::cout << 1;
    if (!(this->get_prime_one() == other.get_prime_one())) std::cout << 2;
    if (!(this->get_prime_two() == other.get_prime_two())) std::cout << 3;
    if (!(this->get_public_key().prime_product ==
          other.get_public_key().prime_product))
        std::cout << 4;
    if (!(this->get_public_key().exponent == other.get_public_key().exponent))
        std::cout << 5;
    if (!(this->get_beta() == other.get_beta())) std::cout << 6;
    if (!(this->get_d() == other.get_d())) std::cout << 7;
    std::cout << "\n";

    return this->username == other.username &&
           this->get_prime_one() == other.get_prime_one() &&
           this->get_prime_two() == other.get_prime_two() &&
           this->get_public_key().prime_product ==
               other.get_public_key().prime_product &&
           this->get_public_key().exponent == other.get_public_key().exponent &&
           this->get_beta() == other.get_beta() &&
           this->get_d() == other.get_d();
}

// void User::send_message(User& user, const std::string& message, bool encrypt)
// {
//     if (encrypt) {
//         user.add_message(
//             Message(this->username, user.username, "RSA",
//                     Encrypter::encrypt(message, user.get_public_key())));
//     } else {
//         user.add_message(
//             Message(this->username, user.username, "None", message));
//     }
// }

// std::string User::read_message() {
//     Message current_message = this->messages.front();
//     messages.pop();
//     if (current_message.get_encryption() != "None") {
//         // Implement Encrypter factory
//         return Encrypter::decrypt(current_message.get_message());
//     }
//     return current_message.get_message();
// }

// std::string User::read_message_undecrypted() {
//     return this->messages.front().get_message();
// }

std::ostream& operator<<(std::ostream& o, User& user) {
    o << user.username << "\n"
      << user.get_prime_one() << "\n"
      << user.get_prime_two() << "\n"
      << user.get_beta() << "\n"
      << user.get_d() << "\n"
      << user.get_public_key().exponent;
    return o;
}

std::istream& operator>>(std::istream& i, User& user) {
    i >> user.username;
    mpz_class prime_one, prime_two, beta, d, exponent;
    i >> prime_one >> prime_two >> beta >> d >> exponent;
    user.set_prime_one(prime_one);
    user.set_prime_two(prime_two);
    user.set_beta(beta);
    user.set_d(d);
    user.set_public_key(prime_one*prime_two, exponent);
    return i;
}

void User::write_public_info(std::string filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("Failed to open file");
    file << this->get_username() << "\n"
         << this->get_public_key().prime_product << "\n"
         << this->get_public_key().exponent;
}
User User::read_public_info(std::string filepath) {
    std::string username;
    mpz_class prime_product, exponent;
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("Couldn't open file");
    file >> username >> prime_product >> exponent;
    return User(username, prime_product, exponent);
}
