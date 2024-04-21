#include <iostream>
#include <vector>

struct Polynomial
{
    std::vector<int> coefficients; // Współczynniki wielomianu
};

void printPolynomial(const Polynomial &poly);

// Funkcja zwracająca stopień wielomianu
int degree(const Polynomial &poly)
{
    return poly.coefficients.size() - 1;
}

// Funkcja zwracająca wiodący wyraz wielomianu
int leadingTerm(const Polynomial &poly)
{
    return poly.coefficients.back();
}

// Funkcja odejmująca wielomiany
Polynomial subtract(const Polynomial &poly1, const Polynomial &poly2)
{
    Polynomial result;
    int size1 = poly1.coefficients.size();
    int size2 = poly2.coefficients.size();
    int maxSize = std::max(size1, size2);
    int minSize = std::min(size1, size2);

    result.coefficients.resize(maxSize);

    for (int i = 0; i < maxSize; ++i)
    {
        if (i < minSize)
            result.coefficients[i] = poly1.coefficients[i] - poly2.coefficients[i];
        else if (size1 > size2)
            result.coefficients[i] = poly1.coefficients[i];
        else
            result.coefficients[i] = -poly2.coefficients[i];
    }

    // Usuwanie wiodących zer
    while (!result.coefficients.empty() && result.coefficients.back() == 0)
        result.coefficients.pop_back();

    return result;
}

// Funkcja mnożąca wielomiany
Polynomial multiply(const Polynomial &poly1, const Polynomial &poly2)
{
    int degree1 = degree(poly1);
    int degree2 = degree(poly2);
    int resultDegree = degree1 + degree2;
    std::vector<int> resultCoefficients(resultDegree + 1, 0);

    for (int i = 0; i <= degree1; ++i)
    {
        for (int j = 0; j <= degree2; ++j)
        {
            resultCoefficients[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
        }
    }

    Polynomial result;
    result.coefficients = resultCoefficients;

    return result;
}

Polynomial add(const Polynomial &poly1, const Polynomial &poly2)
{
    Polynomial result;
    int size1 = poly1.coefficients.size();
    int size2 = poly2.coefficients.size();
    int maxSize = std::max(size1, size2);
    int minSize = std::min(size1, size2);

    result.coefficients.resize(maxSize);

    for (int i = 0; i < maxSize; ++i)
    {
        if (i < minSize)
            result.coefficients[i] = poly1.coefficients[i] + poly2.coefficients[i];
        else if (size1 > size2)
            result.coefficients[i] = poly1.coefficients[i];
        else
            result.coefficients[i] = poly2.coefficients[i];
    }

    // Usuwanie wiodących zer
    while (!result.coefficients.empty() && result.coefficients.back() == 0)
        result.coefficients.pop_back();

    return result;
}

// Funkcja dzieląca wielomiany z resztą
std::pair<Polynomial, Polynomial> div(const Polynomial &f, const Polynomial &g)
{
    Polynomial q;
    Polynomial r;
    Polynomial p = g;
    std::cout << std::endl;
    std::cout << "Test: " << std ::endl;
    std::cout << "deg(f): " << degree(f) << std ::endl;
    std::cout << "deg(g): " << degree(g) << std ::endl;
    printPolynomial(f);
    printPolynomial(g);
    if (degree(f) < degree(g))
    {
        std::cout << "swap f,g = g,f ";
        p = f;
        r = g;
        std::cout << "deg(r) (copy g): " << degree(r) << std ::endl;
        std::cout << "deg(p) (copy f): " << degree(p) << std ::endl;
    }
    else
    {
        r = f;
        std::cout << "deg(r) (copy f): " << degree(r) << std ::endl;
        std::cout << "deg(p) (copy g): " << degree(p) << std ::endl;
    }
    printPolynomial(r);
    printPolynomial(p);

    std::cout << "while div begin: " << std ::endl;

    while (degree(r) >= degree(p))
    {
        int leadingR = leadingTerm(r);
        int leadingG = leadingTerm(p);

        int coefficient = leadingR / leadingG;
        int exp = degree(r) - degree(p);

        // std::cout << "quotient.coefficients: " << exp << std::endl;

        std::vector<int> term(exp + 1, 0);
        term[exp] = coefficient;

        Polynomial quotient;
        quotient.coefficients = term;

        q = add(q, quotient);
        r = subtract(r, multiply(quotient, p));
    }
    std::cout << "end Test, div end " << std ::endl;
    std::cout << std::endl;

    return std::make_pair(q, r);
}
/*
// Funkcja wyznaczająca NWD dla R[x]
Polynomial nwd(const Polynomial &a, const Polynomial &b)
{
    if (b.coefficients == std::vector<int>{0})
    {
        return a;
    }
    else
    {
        auto divResult = div(a, b);
        return nwd(b, divResult.second);
    }
}

*/

Polynomial nwd(const Polynomial &a, const Polynomial &b)
{
    if (b.coefficients == std::vector<int>{0})
    {
        return a;
    }
    else
    {
        auto divResult = div(a, b);
        return nwd(b, divResult.second);
    }
}

// Funkcja wyznaczająca NWW dla R[x]
Polynomial nww(const Polynomial &p, const Polynomial &q)
{
    Polynomial nwdResult = nwd(p, q);
    Polynomial divResult = multiply(p, q);
    return div(divResult, nwdResult).first;
}

// Funkcja drukująca wielomian
void printPolynomial(const Polynomial &poly)
{
    bool firstTerm = true;
    for (int i = poly.coefficients.size() - 1; i >= 0; --i)
    {
        if (poly.coefficients[i] != 0)
        {
            if (!firstTerm)
            {
                std::cout << " + ";
            }
            std::cout << poly.coefficients[i];
            if (i > 0)
            {
                std::cout << "x^" << i;
            }
            firstTerm = false;
        }
    }
    if (firstTerm)
    {
        std::cout << "0";
    }
    std::cout << std::endl;
}

int main()
{
    Polynomial a{{1, 0, 1}}; // 1 + x^2
    Polynomial b{{1, 2, 1}}; // 1 + 2x + x^2
    // Polynomial a{{1, -1, 3, 1}};
    // Polynomial b{{-1, 0, 1}};

    std::cout << "Degree(1 + x^2) = " << degree(a) << std::endl;

    std::cout << "Degree(1 + 2x + x^2) = " << degree(b) << std::endl;

    std::cout << "LT(1 + x^2) = " << leadingTerm(a) << std::endl;

    std::cout << "LT(1 + 2x + x^2) = " << leadingTerm(b) << std::endl;

    Polynomial multiplyResult = multiply(a, b);
    std::cout << "Multiply(1 + x^2, 1 + 2x + x^2) = ";
    printPolynomial(multiplyResult);

    Polynomial subtractResult = subtract(a, b);
    std::cout << "Subtract(1 + x^2, 1 + 2x + x^2) = ";
    printPolynomial(subtractResult);

    Polynomial addResult = add(a, b);
    std::cout << "Add(1 + x^2, 1 + 2x + x^2) = ";
    printPolynomial(addResult);

    auto divResult = div(a, b);

    std::cout << "div(1 + x^2, 1 + 2x + x^2):" << std::endl;
    std::cout << "q: ";
    printPolynomial(divResult.first);
    std::cout << "r: ";
    printPolynomial(divResult.second);

    Polynomial nwdResult = nwd(a, b);
    Polynomial nwwResult = nww(a, b);

    std::cout << "NWD(1 + x^2, 1 + 2x + x^2) = ";
    printPolynomial(nwdResult);

    std::cout << "NWW(1 + x^2, 1 + 2x + x^2) = ";
    printPolynomial(nwwResult);

    return 0;
}
