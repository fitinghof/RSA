#include "../headers/Encrypter.hpp"

mpz_class Encrypter::gcd(mpz_class num1, mpz_class num2) {
    if (num1 < num2) std::swap(num1, num2);
    while (num2 != 0) {
        mpz_class modulo_result = num1 % num2;
        num1 = num2;
        num2 = modulo_result;
    }
    return num1;
}

mpz_class Encrypter::find_exponent() {
    gmp_randclass rand_gen(gmp_randinit_default);
    rand_gen.seed(time(nullptr));
    // rand_gen.seed(0);
    while (true) {
        mpz_class exponent = get_random_prime(65000, 100000, rand_gen);
        if (gcd(exponent, this->beta) == 1) return exponent;
    }
}

// Function to generate a random prime number in the range [min, max]
// Returns an mpz_class object
mpz_class Encrypter::get_random_prime(const mpz_class& min,
                                      const mpz_class& max,
                                      gmp_randclass& rand_gen) const {
    while (true) {
        mpz_class candidate = rand_gen.get_z_range(max - min) + min;
        if (mpz_probab_prime_p(candidate.get_mpz_t(), 25) > 0) {
            return candidate;
        }
    }
}

mpz_class Encrypter::mod_inverse(mpz_class e, mpz_class beta) {
    mpz_class m0 = beta, t, q;
    mpz_class x0 = 0, x1 = 1;

    if (beta == 1) return 0;

    while (e > 1) {
        q = e / beta;

        t = beta;
        beta = e % beta;
        e = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

mpz_class Encrypter::power_mod(const mpz_class& base, const mpz_class& exponent,
                               const mpz_class& modulus) const {
    mpz_class result = 1;
    mpz_class base_mod = base % modulus;

    mpz_class exp = exponent;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base_mod) % modulus;
        }
        exp >>= 1;
        base_mod = (base_mod * base_mod) % modulus;
    }

    return result;
}

Encrypter::Encrypter(size_t prime_min_bits, size_t prime_max_bits) {
    if (prime_max_bits < prime_min_bits)
        throw std::runtime_error(
            "prime_min_bits must be less than or equal to prime_max_bits");
    std::cout << "Expected min character limit for encryption: "
              << (prime_min_bits * 2) / 8 << "\n";
    gmp_randclass rand_gen(gmp_randinit_default);
    rand_gen.seed(time(nullptr));
    // rand_gen.seed(0);
    this->prime_one =
        get_random_prime(mpz_class(1) << prime_min_bits,
                         mpz_class(1) << prime_max_bits, rand_gen);
    this->prime_two =
        get_random_prime(mpz_class(1) << prime_min_bits,
                         mpz_class(1) << prime_max_bits, rand_gen);
    this->beta = (this->prime_one - 1) * (this->prime_two - 1);
    this->public_part = {prime_one * prime_two, this->find_exponent()};
    this->d = mod_inverse(this->public_part.exponent, this->beta);
}

Encrypter::Encrypter(mpz_class prime_one, mpz_class prime_two, mpz_class beta,
                     mpz_class d)
    : prime_one(prime_one), prime_two(prime_two), beta(beta), d(d) {
    this->calculate_public_key();
}

mpz_class Encrypter::string_to_bigNum(const std::string& str) const {
    mpz_class retVal = 0;
    for (size_t i = 0; i < str.size(); i++) {
        retVal = (retVal << 8) | mpz_class(static_cast<unsigned int>(str[i]));
    }
    return retVal;
}

std::string Encrypter::bigNum_to_string(const mpz_class& number) const {
    mpz_class num = number;
    std::string retVal;
    while (num > 0) {
        unsigned char byte = num.get_ui() & 0xFF;
        retVal += static_cast<char>(byte);
        num >>= 8;
    }
    std::reverse(retVal.begin(), retVal.end());
    return retVal;
}

std::string Encrypter::encrypt(const std::string& data,
                               public_key public_key) const {
    mpz_class encrypted_message = string_to_bigNum(data);
    if (encrypted_message >= public_key.prime_product)
        throw std::runtime_error(
            "Message to long to encrypt given current primes");
    encrypted_message = power_mod(encrypted_message, public_key.exponent,
                                  public_key.prime_product);
    return encrypted_message.get_str();
}

std::string Encrypter::decrypt(const std::string& data) const {
    mpz_class message(data);
    message = power_mod(message, this->d, this->public_part.prime_product);
    return bigNum_to_string(message);
}

public_key Encrypter::get_public_key() const { return this->public_part; }
mpz_class Encrypter::get_prime_one() const { return this->prime_one; }
mpz_class Encrypter::get_prime_two() const { return this->prime_two; }
mpz_class Encrypter::get_beta() const { return this->beta; }
mpz_class Encrypter::get_d() const { return this->d; }

void Encrypter::set_public_key(mpz_class prime_product, mpz_class exponent) {
    this->public_part = {prime_product, exponent};
}
