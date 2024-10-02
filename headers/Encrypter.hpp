#ifndef ENCRYPTER_HPP
#define ENCRYPTER_HPP
#include <gmpxx.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <string>

struct public_key {
    mpz_class prime_product;
    mpz_class exponent;
};

class Encrypter {
   private:
    mpz_class prime_one;
    mpz_class prime_two;

    mpz_class beta;
    mpz_class d;

    public_key public_part;

    mpz_class string_to_bigNum(const std::string& str) const;
    std::string bigNum_to_string(const mpz_class& number) const;

    mpz_class gcd(mpz_class num1, mpz_class num2);

    mpz_class find_exponent();

    mpz_class get_random_prime(const mpz_class& min, const mpz_class& max,
                               gmp_randclass& rand_gen) const;

    mpz_class mod_inverse(mpz_class e, mpz_class beta);

    mpz_class power_mod(const mpz_class& base, const mpz_class& exponent,
                        const mpz_class& modulus) const;

   public:
    Encrypter()
        : prime_one(0), prime_two(0), beta(0), d(0), public_part({0, 0}){};
    Encrypter(size_t prime_min_bits, size_t prime_max_bits);
    Encrypter(mpz_class prime_one, mpz_class prime_two, mpz_class beta,
              mpz_class d);

    Encrypter(Encrypter&&) = default;  // Default move constructor
    Encrypter& operator=(Encrypter&&) =
        default;                            // Default move assignment operator
    Encrypter(const Encrypter&) = default;  // Default copy constructor
    Encrypter& operator=(const Encrypter&) =
        default;  // Default copy assignment operator

    std::string encrypt(const std::string& data, public_key public_key) const;
    std::string decrypt(const std::string& data) const;

    public_key get_public_key() const;
    mpz_class get_prime_one() const;
    mpz_class get_prime_two() const;
    mpz_class get_beta() const;
    mpz_class get_d() const;

    void set_prime_one(mpz_class value) { prime_one = value; }
    void set_prime_two(mpz_class value) { prime_two = value; }
    void set_beta(mpz_class value) { beta = value; }
    void set_d(mpz_class value) { d = value; }
    void calculate_public_key() {
        public_part = {prime_one * prime_two, find_exponent()};
    }
    void set_public_key(mpz_class prime_product, mpz_class exponent);
};

#endif