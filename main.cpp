#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input.txt"); // имя входного файла с текстовыми вопросами
    std::ofstream outputFile("output.txt"); // имя файла для сохранения вопросов в формате GIFT

    if (!inputFile) {
        std::cout << "ошибка открытия входного файла!" << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cout << "ошибка открытия выходного файла!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue; // пропуск пустых строк
        }

        outputFile << "::" << line << "{" << std::endl; // имя вопроса в формате GIFT

        std::string answer;
        std::getline(inputFile, answer);
        if (!answer.empty()) {
            outputFile << "= " << answer << std::endl; // правильный ответ в формате GIFT
        }

        std::string option;
        while (std::getline(inputFile, option) && !option.empty()) {
            outputFile << "~ " << option << std::endl; // варианты ответов в формате GIFT
        }

        outputFile << "}" << std::endl << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "преобразование завершено. результат сохранен в output.txt" << std::endl;

    return 0;
}