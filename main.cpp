#include "main.h"

int main() {

    setlocale(LC_ALL, "Russian");

    // ���������� ���� �� JavaScript �� �����
    ifstream inputFile("input.js");
    if (!inputFile.is_open()) {
        cerr << "�� ������� ������� ���� � ����� JavaScript\n";
        return 1;
    }

    string inputCode((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // ���������� ��������� ��� ������ ���� ���������� const � �� ��������
    regex constRegex(R"(\bconst\s+(\w+)\s*=\s*([^;]+);)");

    smatch matches;
    vector<pair<string, string>> variables;

    // ����� ���� ���������� const � �� ��������
    auto codeBegin = inputCode.cbegin();
    auto codeEnd = inputCode.cend();
    while (regex_search(codeBegin, codeEnd, matches, constRegex)) {
        variables.emplace_back(matches[1].str(), matches[2].str());
        codeBegin = matches.suffix().first;
    }

    // ������ � CSV-����
    ofstream outputFile("output.csv");
    if (outputFile.is_open()) {
        // ��������� CSV-�����
        outputFile << "VariableName,VariableValue\n";

        // ������ ���������� � CSV-����
        for (const auto& variable : variables) {
            outputFile << variable.first << "," << variable.second << "\n";
        }

        outputFile.close();
        cout << "���������� const � �� �������� ���� �������� � �������� � output.csv\n";
    }
    else {
        cerr << "�� ������� ������� ���� ��� ������\n";
    }


    const std::string filename = "output.csv";

    // ���������� ������� � �������
    writeRecord(filename, "x", "hello world!");
    writeRecord(filename, "y", "buy world!");

    // ����� ����������� ������� � ��������
    readAndDisplayTable(filename);

    // �������� ������
    deleteRecord(filename, "halfRadius");

    // �������������� ������
    editRecord(filename, "circumference", "Oh God! Who Im? Im student from SevSu");

    // ����� ����������� ������� � ��������
    readAndDisplayTable(filename);

    // ����� ������ �� ��������� �����
    searchAndDisplay(filename, "PI");

    return 0;
  
}

