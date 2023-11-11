#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;

void readAndDisplayTable(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Содержимое таблицы (" << filename << "):\n";
        string line;
        while (getline(file, line)) cout << line << '\n';
        file.close();
    }
    else cerr << "Не удалось открыть файл " << filename << " для чтения\n";
}

void writeRecord(const string& filename, const string& variableName, const string& variableValue) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << variableName << "," << variableValue << "\n";
        cout << "Запись добавлена в таблицу (" << filename << ")\n";
        file.close();
    }
    else cerr << "Не удалось открыть файл " << filename << " для записи\n";
}

void deleteRecord(const string& filename, const string& variableName) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        vector<pair<string, string>> records;
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string name, value;
            getline(iss, name, ',');
            getline(iss, value, ',');
            if (name != variableName) records.emplace_back(name, value);
        }
        inputFile.close();

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& record : records) outputFile << record.first << "," << record.second << "\n";
            cout << "Запись с именем " << variableName << " удалена из таблицы (" << filename << ")\n";
            outputFile.close();
        }
        else cerr << "Не удалось открыть файл " << filename << " для записи\n";
    }
    else cerr << "Не удалось открыть файл " << filename << " для чтения\n";
}

void editRecord(const string& filename, const string& variableName, const string& newVariableValue) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        vector<pair<string, string>> records;
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string name, value;
            getline(iss, name, ',');
            getline(iss, value, ',');
            if (name == variableName) value = newVariableValue;
            records.emplace_back(name, value);
        }
        inputFile.close();

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& record : records) outputFile << record.first << "," << record.second << "\n";
            cout << "Запись с именем " << variableName << " отредактирована в таблице (" << filename << ")\n";
            outputFile.close();
        }
        else cerr << "Не удалось открыть файл " << filename << " для записи\n";
    }
    else cerr << "Не удалось открыть файл " << filename << " для чтения\n";
}

void searchAndDisplay(const string& filename, const string& keyword) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, value;
            getline(iss, name, ',');
            getline(iss, value, ',');
            if (name.find(keyword) != string::npos || value.find(keyword) != string::npos)
                cout << "Найдена запись: " << name << "," << value << '\n';
        }
        file.close();
    }
    else cerr << "Не удалось открыть файл " << filename << " для чтения\n";
}
