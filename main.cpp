#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream inputFile("input.txt"); // имя входного файла с текстовыми вопросами
    std::ofstream outputFile("output.txt"); // имя файла для сохранения вопросов в формате GIFT

    if (!inputFile) {
        std::cout << "Ошибка открытия входного файла!" << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cout << "Ошибка открытия выходного файла!" << std::endl;
        return 1;
    }

    std::string line;
    int questionNumber = 1;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue; // пропуск пустых строк
        }

        // извлечение вопроса
        std::string question;
        if (line.find(". ") != std::string::npos) {
            question = line.substr(line.find(". ") + 2);
        }

        // извлечение вариантов ответов
        std::vector<std::string> answers;
        while (std::getline(inputFile, line) && !line.empty()) {
            std::string answer;
            char prefix = line[0];
            if (prefix == '+' || prefix == '-') {
                answer = line.substr(1);
                answers.push_back(answer);
            }
        }

        // запись вопроса и ответов в формате GIFT
        if (!question.empty() && !answers.empty()) {
            outputFile << questionNumber << ". " << question << " {" << std::endl;
            for (const auto& answer : answers) {
                if (answer[0] == '+') {
                    outputFile << "=" << answer.substr(1) << std::endl;
                } else {
                    outputFile << "~" << answer.substr(1) << std::endl;
                }
            }
            outputFile << "}" << std::endl << std::endl;

            questionNumber++;
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "преобразование завершено. результат сохранен в output.txt" << std::endl;

    return 0;
}
