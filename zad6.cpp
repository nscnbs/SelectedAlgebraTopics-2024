#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void findMinimalPointsForSecondSet()
{
    int centerX = 10, centerY = 10;
    int radius = 5;
    cout << "Minimalne punkty w zbiorze {n, k) ∈ N^2 : (n - 10)^2 + (k - 10)^2 <= 25}:" << endl;
    for (int i = centerX - radius; i <= centerX + radius; ++i)
    {
        for (int j = centerY - radius; j <= centerY + radius; ++j)
        {
            if ((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY) <= radius * radius)
            {
                cout << "(" << i << ", " << j << ")" << endl;
            }
        }
    }
}

int main()
{
    findMinimalPointsForSecondSet();
    return 0;
}
