#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <random>
#include <vector>

const long PRIME_NUMBER_UPPER_BOUND = 1e8;

const int E = 65537;

int main(int argc, char const *argv[])
{
    std::vector<bool> primeFlag(PRIME_NUMBER_UPPER_BOUND, true);
    std::vector<long> primeNumbers;
    //Используем алгоритм Решето Эратосфена для поиска всех простых чисел в диапазоне [2, 1e8]
    for (auto p = 2; p * p < PRIME_NUMBER_UPPER_BOUND + 1; p++)
    {
        if (primeFlag[p])
        {
            primeNumbers.push_back(p);
            for (auto i = p * p; i < PRIME_NUMBER_UPPER_BOUND + 1; i += p)
                primeFlag[i] = false;
        }
    }
    //Выбираем два простых числа из заданного диапазона
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, primeNumbers.size() - 1);
    long index1 = dis(gen);
    long index2 = dis(gen);
    mpz_t p; mpz_set_ui(p, primeNumbers[index1]);
    mpz_t q; mpz_set_ui(q, primeNumbers[index2]);
 
    mpz_t n;
    mpz_mul(n, p, q);

    char buffer[1000];
    mpz_get_str(buffer, 10, n);
    std::string n_str(buffer);
    std::cout << primeNumbers[index1] << " " << primeNumbers[index2] << std::endl;
    std::cout << "Public key: " << n_str << std::endl;

    //Значение функции Эйлера для выбранных простых чисел
    mpz_t phi_n;
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi_n, p, q);

    mpz_t e; mpz_set_si(e, E);
    mpz_t d;
    //Расширенный Метод Евклида для поиска обратного элемента по модулю phi_n
    mpz_invert(d, e, phi_n);

    mpz_get_str(buffer, 10, d);
    std::string d_str(buffer);
    std::cout << "Private key: " << d_str << std::endl;
   
    return 0;
}
