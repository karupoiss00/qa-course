#include <iostream>
#include <string>
#include <optional>

using namespace std;

enum class TriangleType {
    UNKNOWN,
    EQUILATERAL,
    ISOSCELES,
    DEFAULT
};

struct Args
{
    int a;
    int b;
    int c;
};

TriangleType DetermineTriangleType(int a, int b, int c);
optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "Russian");

    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return -1;
    }

    TriangleType type = DetermineTriangleType(args->a, args->b, args->c);

    switch (type) 
    {
        case TriangleType::UNKNOWN:
            cout << "Не треугольник" << endl;
            break;
        case TriangleType::EQUILATERAL:
            cout << "Равносторонний" << endl;
            break;
        case TriangleType::ISOSCELES:
            cout << "Равнобедренный" << endl;
            break;
        case TriangleType::DEFAULT:
            cout << "Обычный" << endl;
            break;
    }

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Неверное количество аргументов. Используйте формат: triangle.exe a b c" << endl;
        return nullopt;
    }

    int a = stoi(argv[1]);
    int b = stoi(argv[2]);
    int c = stoi(argv[3]);

    return Args(a, b, c);
}

TriangleType DetermineTriangleType(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return TriangleType::UNKNOWN;
    }

    if (a == b && b == c)
    {
        return TriangleType::EQUILATERAL;
    }

    if (a == b || b == c || a == c)
    {
        return TriangleType::ISOSCELES;
    }

    return TriangleType::DEFAULT;
}