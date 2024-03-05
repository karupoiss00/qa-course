#include <iostream>
#include <string>
#include <optional>
#include <algorithm>

using namespace std;

enum class TriangleType {
    UNKNOWN,
    EQUILATERAL,
    ISOSCELES,
    DEFAULT
};

struct Args
{
    double a;
    double b;
    double c;
};

TriangleType DetermineTriangleType(double a, double b, double c);
optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "Russian");

    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return -1;
    }

    try
    {
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
    }
    catch (exception const& e)
    {
        cout << e.what() << endl;
    }
    
    return 0;
}

string PrepareArgument(char* arg)
{
    string s(arg);
    replace(s.begin(), s.end(), '.', ',');
    return s;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Неверное количество аргументов. Используйте формат: triangle.exe a b c" << endl;
        return nullopt;
    }

    try
    {
        double a = stod(PrepareArgument(argv[1]));
        double b = stod(PrepareArgument(argv[2]));
        double c = stod(PrepareArgument(argv[3]));

        return Args(a, b, c);
    }
    catch (...)
    {
        cout << "Неизвестная ошибка" << endl;
        return std::nullopt;
    }
}

constexpr double EPSILON = 0.0000000001;

inline double compare(double a, double b, double eps = EPSILON)
{
    return fabs(a - b) < EPSILON;
}

TriangleType DetermineTriangleType(double a, double b, double c)
{
    if (a < 0 || b < 0 || c < 0)
    {
        throw std::invalid_argument("Неизвестная ошибка");
    }

    if (compare(a, 0) || compare(b, 0) || compare(c, 0))
    {
        return TriangleType::UNKNOWN;
    }

    if (compare(a, b) && compare(b, c))
    {
        return TriangleType::EQUILATERAL;
    }

    if (compare(a, b) || compare(b, c) || compare(a, c))
    {
        return TriangleType::ISOSCELES;
    }

    return TriangleType::DEFAULT;
}