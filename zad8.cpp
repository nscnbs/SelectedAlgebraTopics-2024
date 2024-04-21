#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// Struktura reprezentująca wielomian
struct Polynomial
{
    vector<int> coefficients;
    Polynomial(const vector<int> &coeffs) : coefficients(coeffs) {}
};

// Funkcja pomocnicza obliczająca resztę z dzielenia wielomianu f przez g
Polynomial polynomial_mod(const Polynomial &f, const Polynomial &g)
{
    vector<int> mod_coeffs(f.coefficients.size(), 0);
    int deg_diff = f.coefficients.size() - g.coefficients.size();
    for (int i = f.coefficients.size() - 1; i >= 0; --i)
    {
        if (i - deg_diff >= 0)
            mod_coeffs[i] = f.coefficients[i] - g.coefficients[i - deg_diff];
        else
            mod_coeffs[i] = f.coefficients[i];
    }
    while (!mod_coeffs.empty() && mod_coeffs.back() == 0)
    {
        mod_coeffs.pop_back();
    }
    return Polynomial(mod_coeffs);
}

// Procedura obliczająca współczynniki A i B oraz nwd(f, g)
tuple<Polynomial, Polynomial, Polynomial> NWD_wielomianow(const Polynomial &f, const Polynomial &g)
{
    if (g.coefficients.empty())
    {
        return make_tuple(f, Polynomial({1}), Polynomial({0}));
    }
    auto result = NWD_wielomianow(g, polynomial_mod(f, g));
    Polynomial d = get<0>(result);
    Polynomial A_ = get<1>(result);
    Polynomial B_ = get<2>(result);
    Polynomial A = B_;
    Polynomial B({0});
    int deg_diff = f.coefficients.size() - g.coefficients.size();
    for (int i = 0; i < A_.coefficients.size(); ++i)
    {
        if (i + deg_diff >= 0)
            B.coefficients.push_back(A_.coefficients[i] - (f.coefficients[i] / g.coefficients[0]) * B_.coefficients[0]);
        else
            B.coefficients.push_back(A_.coefficients[i]);
    }
    return make_tuple(d, A, B);
}

// Funkcja pomocnicza do wyświetlania współczynników wielomianu
void print_polynomial(const Polynomial &p)
{
    for (int i = p.coefficients.size() - 1; i >= 0; --i)
    {
        cout << p.coefficients[i];
        if (i > 0)
            cout << "x^" << i << " + ";
    }
    cout << endl;
}

int main()
{
    vector<int> coefficients_f = {1, 2, 3};
    vector<int> coefficients_g = {1, 1};
    Polynomial f(coefficients_f);
    Polynomial g(coefficients_g);

    auto result = NWD_wielomianow(f, g);
    Polynomial d = get<0>(result);
    Polynomial A = get<1>(result);
    Polynomial B = get<2>(result);

    cout << "NWD(f, g) = ";
    print_polynomial(d);
    cout << "A = ";
    print_polynomial(A);
    cout << "B = ";
    print_polynomial(B);

    return 0;
}
