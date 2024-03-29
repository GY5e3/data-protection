#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

const std::string keyFile = "key.txt"; 

void encryptDecryptFile(const std::string&, const std::string&, const std::string&, bool);

int main(int argc, char const *argv[])
{
    std::string inputFile = "task-3.txt", outputFile = "";
    char mode;

    std::cout << "Введите 'e' для шифрования или 'd' для расшифрования: ";
    std::cin >> mode;

    bool encryptMode;
    if (mode == 'e' || mode == 'E')
    {
        encryptMode = true;
        inputFile = "task-3.txt";
        outputFile = "en.txt";
    }

    else if (mode == 'd' || mode == 'D')
    {
        encryptMode = false;
        inputFile = "en.txt";
        outputFile = "de.txt";
    }

    else
    {
        std::cerr << "Incorrect choice." << std::endl;
        return 1;
    }
    encryptDecryptFile(inputFile, outputFile, keyFile, encryptMode);

    return 0;
}

void encryptDecryptFile(const std::string &inputFile,
                        const std::string &outputFile,
                        const std::string &keyFile,
                        bool encryptMode)
{
    // Чтение ключа из файла
    std::ifstream keyStream(keyFile);
    if (!keyStream.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл ключа." << std::endl;
        return;
    }
    std::vector<int> key(5); // Ключ для перестановки
    for (int i = 0; i < 5; ++i)
        keyStream >> key[i];
    keyStream.close();

    std::ifstream inputStream(inputFile, std::ios::binary);
    if (!inputStream.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть входной файл." << std::endl;
        return;
    }
    std::ofstream outputStream(outputFile, std::ios::binary);
    if (!outputStream.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть выходной файл." << std::endl;
        return;
    }

    // Шифрование или расшифрование файла
    std::vector<char> buffer(5); // Буфер для хранения блока данных
    while (!inputStream.eof())
    {
        inputStream.read(buffer.data(), 5);
        int bytesRead = inputStream.gcount();
        if (bytesRead < 5)
        {
            // Дополнение символами 'z', если необходимо
            for (int i = bytesRead; i < 5; ++i)
                buffer[i] = 'z';
        }

        if (encryptMode)
        {
            // Шифрование
            for (int i = 0; i < 5; ++i)
                outputStream << buffer[key[i] - 1];
        }
        else
        {
            // Расшифрование
            std::vector<int> inverseKey(5); // Обратный ключ
            for (int i = 0; i < 5; ++i)
                inverseKey[key[i] - 1] = i + 1;
            for (int i = 0; i < 5; ++i)
                outputStream << buffer[inverseKey[i] - 1];
        }
    }

    inputStream.close();
    outputStream.close();

    std::cout << (encryptMode ? "Шифрование" : "Расшифрование") << " завершено успешно." << std::endl;
}