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
    Encrypter(size_t prime_min_bits = 40, size_t prime_max_bits = 50);

    // std::string encrypt(const std::string& data, public_key public_key)
    // const; std::string decrypt(const std::string& data, public_key
    // public_key) const;

    std::string encrypt(const std::string& data, public_key public_key) const;
    std::string decrypt(const std::string& data) const;

    public_key get_public_key() const;
};

#endif