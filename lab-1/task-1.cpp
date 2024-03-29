#include <iostream>
#include <fstream>

const std::string filename = "task-1.odt";

int main(int argc, char const *argv[])
{
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()){
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    std::cout << "Длина файла " << filename << " в байтах: " << fileSize << " байт." << std::endl;
    
    file.close();

    return 0;
}
