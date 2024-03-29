#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace std;

constexpr const char* INPUT_FILE_NAME = "test_cases.txt";
constexpr const char* OUTPUT_FILE_NAME = "results.txt";

enum class TestResult
{
    SUCCESS,
    ERROR
};

TestResult RunTestCase(const string& input);

int main() 
{
    setlocale(LC_ALL, "Russian");

    ifstream inputFile(INPUT_FILE_NAME);
    if (!inputFile.is_open()) 
    {
        cerr << "�� ������� ������� ���� � ��������� �������." << endl;
        return 1;
    }

    ofstream outputFile(OUTPUT_FILE_NAME);
    if (!outputFile.is_open())
    {
        cerr << "�� ������� ������� ���� ��� ����������� ��������." << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) 
    {
        TestResult result = RunTestCase(line);
        if (result == TestResult::SUCCESS)
        {
            outputFile << "success;" << endl;
        }
        else
        {
            outputFile << "error;" << endl;
        }
    }

    cout << "�������� ���������. ���������� �������� � ���� results.txt." << endl;

    return 0;
}

void ltrim(std::string& s) 
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        })
    );
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) 
{
    if (from.empty())
    {
        return;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

TestResult RunTestCase(const string& input) 
{
    istringstream iss(input);
    string a, b, c;
    string expected_result;
    iss >> a >> b >> c;
    getline(iss, expected_result);
    ltrim(expected_result);

    replaceAll(a, "_", "");
    replaceAll(b, "_", "");
    replaceAll(c, "_", "");

    string command = "triangle.exe " + a + " " + b + " " + c;

    FILE*  pipe = _popen(command.c_str(), "r");

    if (!pipe) 
    {
        cerr << "������ ��� �������� ����������� ��������." << endl;
        return TestResult::ERROR;
    }

    char buffer[128];
    string result;
    while (!feof(pipe)) 
    {
        if (fgets(buffer, 128, pipe) != nullptr)
        {
            result += buffer;
        }
    }
    _pclose(pipe);

    result.pop_back();

    cout << result << " <> " << expected_result << endl;

    if (result != expected_result)
    {
        return TestResult::ERROR;
    }

    return TestResult::SUCCESS;
}

