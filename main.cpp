#include "main.h"

int main() {

    setlocale(LC_ALL, "Russian");

    // Считывание кода на JavaScript из файла
    ifstream inputFile("input.js");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл с кодом JavaScript\n";
        return 1;
    }

    string inputCode((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // Регулярное выражение для поиска имен переменных const и их значений
    regex constRegex(R"(\bconst\s+(\w+)\s*=\s*([^;]+);)");

    smatch matches;
    vector<pair<string, string>> variables;

    // Поиск имен переменных const и их значений
    auto codeBegin = inputCode.cbegin();
    auto codeEnd = inputCode.cend();
    while (regex_search(codeBegin, codeEnd, matches, constRegex)) {
        variables.emplace_back(matches[1].str(), matches[2].str());
        codeBegin = matches.suffix().first;
    }

    // Запись в CSV-файл
    ofstream outputFile("output.csv");
    if (outputFile.is_open()) {
        // Заголовок CSV-файла
        outputFile << "VariableName,VariableValue\n";

        // Запись переменных в CSV-файл
        for (const auto& variable : variables) {
            outputFile << variable.first << "," << variable.second << "\n";
        }

        outputFile.close();
        cout << "Переменные const и их значения были выделены и записаны в output.csv\n";
    }
    else {
        cerr << "Не удалось открыть файл для записи\n";
    }


    const std::string filename = "output.csv";

    // Добавление записей в таблицу
    writeRecord(filename, "x", "hello world!");
    writeRecord(filename, "y", "buy world!");

    // Вывод содержимого таблицы в терминал
    readAndDisplayTable(filename);

    // Удаление записи
    deleteRecord(filename, "halfRadius");

    // Редактирование записи
    editRecord(filename, "circumference", "Oh God! Who Im? Im student from SevSu");

    // Вывод содержимого таблицы в терминал
    readAndDisplayTable(filename);

    // Поиск записи по ключевому слову
    searchAndDisplay(filename, "PI");

    return 0;
  
}

