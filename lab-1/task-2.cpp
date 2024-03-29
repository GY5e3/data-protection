#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
//hexdump -C task-2.txt
const std::string filename = "task-2.txt";

int main(int argc, char const *argv[])
{
    // Открываем файл для чтения в бинарном режиме
    std::ifstream file(filename, std::ios::binary);

    // Проверяем, удалось ли открыть файл
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return 1;
    }

    // Создаем массив для подсчета частоты появления каждого байта
    const int arraySize = 256; // количество возможных значений байта (0-255)
    std::vector<int> byteFrequency(arraySize, 0);

    // Считываем байты из файла и увеличиваем соответствующий счетчик
    char byte;
    while (file.get(byte))
    {
        byteFrequency[static_cast<unsigned char>(byte)]++;
    }

    // Закрываем файл
    file.close();

    // Выводим результаты
    std::cout << "Частота появления каждого байта в файле:" << std::endl;
    for (int i = 0; i < arraySize; ++i)
    {
        if (byteFrequency[i] > 0)
        {
            std::cout << "Байт 0x" << std::setw(2) << std::setfill('0') << i
                      << ": " << byteFrequency[i] << " раз" << std::endl;
        }
    }
    return 0;
}
