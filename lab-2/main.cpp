#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::string message = "HELLO";
    mpz_t n;
    mpz_init_set_str(n, "364703", 10);

    mpz_t d;
    mpz_init_set_str(d, "342473", 10);

    mpz_t e;
    mpz_init_set_str(e, "65537", 10);

    std::vector<std::string> encrypted;
    for (auto i : message)
    {
        mpz_t ci;
        mpz_init(ci);
        mpz_set_si(ci, i - ' ');
        mpz_powm(ci, ci, e, n);

        char buffer[1000];

        mpz_get_str(buffer, 10, ci);

        std::string ci_str(buffer);

        encrypted.push_back(ci_str);
    }
    for (auto ci : encrypted)
    {
        char buffer[1000];
        mpz_t ti;
        mpz_init(ti);

        mpz_set_str(ti, ci.c_str(), 10);

        mpz_get_str(buffer, 10, ti);

        std::string ci_str(buffer);

        mpz_powm(ti, ti, d, n);

        mpz_get_str(buffer, 10, ti);

        std::string ti_str(buffer);
        std::cout << static_cast<char>(std::stoi(ti_str) + ' ');
        mpz_clear(ti);
    }

    return 0;
}
