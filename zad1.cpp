#include <iostream>
#include <utility>
#include <cmath>

struct Complex
{
    int x, y; // Części rzeczywista (a) i urojona (b)
};

// Funkcja dzieląca liczby zespolone z resztą
std::pair<Complex, Complex> div(const Complex &a, const Complex &b)
{
    int x_part = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
    int y_part = (a.y * b.x - a.x * b.y) / (b.x * b.x + b.y * b.y);

    //    double x1 = std::round(x_part);
    //    double y1 = std::round(y_part);

    Complex q{x_part, y_part};
    Complex r{a.x - q.x * b.x + q.y * b.y, a.y - q.x * b.y - q.y * b.x};

    return std::make_pair(q, r);
}

// Funkcja wyznaczająca NWD dla Z[i]
Complex nwd(const Complex &a, const Complex &b)
{
    Complex r1 = a;
    Complex r2 = b;
    Complex temp;

    while (r2.x != 0 || r2.y != 0)
    {
        temp = r2;
        r2 = div(r1, r2).second;
        r1 = temp;
    }

    return r1;
}

// Funkcja wyznaczająca NWW dla Z[i]
Complex nww(const Complex &a, const Complex &b)
{
    int u = a.x * b.x - a.y * b.y;
    int v = a.x * b.y + a.y * b.x;

    Complex c{u, v};
    auto divResult = div(c, nwd(a, b));

    Complex result{divResult.first.x, divResult.first.y};

    return result;
}

int main()
{
    // Complex x{2, 1};
    // Complex y{4, 2};
    Complex a{3, 4};
    Complex b{1, 3};

    // auto divResult = div(x, y);
    // std::cout << "Dzielenie z reszta: " << x.a << " + " << x.b << "i = (" << divResult.first.a << " + " << divResult.first.b << "i)*(" << y.a << " + " << y.b << "i) + (" << divResult.second.a << " + " << divResult.second.b << "i)" << std::endl;
    std::cout << "Dla liczb " << a.x << " + " << a.y << "i oraz " << b.x << " + " << b.y << "i" << std::endl;
    Complex nwdResult = nwd(a, b);
    std::cout << "Najwiekszy wspolny dzielnik: " << nwdResult.x << " + " << nwdResult.y << "i" << std::endl;

    Complex nwwResult = nww(a, b);
    std::cout << "Najmniejsza wspolna wielokrotnosc: " << nwwResult.x << " + " << nwwResult.y << "i" << std::endl;

    return 0;
}
