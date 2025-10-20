#include <iostream>
#include <iomanip>

int main()
{
    int n, cnt = 1;
    std::cin >> n;
    if (!std::cin)
    {
        std::cout << "Error";
        exit(1);
    }
    if (n > 100 || n < 0)
    {
        std::cout << "Error";
        exit(1);
    }
   
    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    int i0 = 0, j0 = 0;
    do
    {
        for (int j = j0; j < n - j0 && cnt != n * n + 1; j++)
        {
            a[i0][j] = cnt;
            cnt++;
        }
        for (int i = i0 + 1; i < n - i0 && cnt != n * n + 1; i++)
        {
            a[i][n - j0 - 1] = cnt;
            cnt++;
        }
        for (int j = n - 2 - j0; j >= j0 && cnt != n * n + 1; j--)
        {
            a[n - i0 - 1][j] = cnt;
            cnt++;
        }
        for (int i = n - i0 - 2; i > i0 && cnt != n * n + 1; i--)
        {
            a[i][j0] = cnt;
            cnt++;
        }
        i0++;
        j0++;
    } while (cnt != n * n + 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << std::setw(4) << a[i][j];
        std::cout << "\n";
    }
    int sum = 0;
    int i = n - 1, j = 0;
    while (i > -1 && j < n)
    {
        sum += a[i][j];
        i--;
        j++;

    }
    std::cout << sum;
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}