#include<iostream>
#include<ctime>
#include <random>


bool min_1_ch(double* a, int n)
{
    for (int i = 100501; i < 100501 + n; i++)
        if (a[i] != -1)
            return true;
    return false;
}

double sum(double* a, int n)
{
    double sum_val = 0;
    for (int i = 0; i < n + n; i++)
        sum_val += a[i];
    return sum_val;
}

double max_2(double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}

void max_el_ar(double* a, int n, double* maxxx)
{
    double maxx = *maxxx;
    for (int i = 1; i < n; i++)
        maxx = max_2(maxx, max_2(a[i], a[i - 1]));
    *maxxx = maxx;
}

void ma_in_ar(double* a, int n, int* i)
{
    int im = 100501;
    for (int j = 100502; j < 100501 + n; j++)
        if (a[j] > a[im])
            im = j;
    *i = im;
}

int main()
{
    std::mt19937 gen(time(0));

  
    double* a = new double[2000000]; 
   

    
    for (int i = 0; i < 2000000; i++) {
        a[i] = 0;
    }

    std::cout << "Enter 1 if you want to fill the array manually, and 2 if you want to fill it automatically(1/2): ";
    char c;
    std::cin >> c;
    if (!std::cin || c != '1' && c != '2')
    {
        std::cout << "Error";
        delete[] a;
        exit(1);
    }

    if (c == '1')
    {
        int n;
        std::cout << "Enter a size of array: ";
        std::cin >> n;
        if (!std::cin || n > 100500)
        {
            std::cout << "Error";
            delete[] a;
            exit(1);
        }
        std::cout << "Enter an array: ";
        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
            if (!std::cin)
            {
                std::cout << "Error";
                delete[] a;
                exit(1);
            }
        }
        double maxel = a[0];
        max_el_ar(a, n, &maxel);
        std::cout << "MAX element is " << maxel << '\n';
        std::cout << "SUM elements is " << sum(a, n) << '\n';

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (a[j] == a[i]) {
                    a[i + 100501]++;
                    for (int k = 100501; k < 100501 + i; k++) {
                        if (a[k - 100501] == a[i])
                            a[k] = 0;
                    }
                }
        }

        while (min_1_ch(a, n))
        {
            double max_tmp;
            int im = 0;

            ma_in_ar(a, n, &im);
            max_tmp = a[im];
            for (int i = 0; i < max_tmp; i++)
                std::cout << a[im - 100501] << ' ';
            a[im] = -1;
        }
    }
    else
    {
        std::cout << "Enter a size of array: ";
        int n;
        std::cin >> n;
        if (!std::cin || n > 100500)
        {
            std::cout << "Error";
            delete[] a;
            exit(1);
        }
        std::cout << "Enter the minimum(x) and maximum(y) possible numbers in the array(x/y): ";
        double x, y;
        std::cin >> x >> y;
        if (!std::cin)
        {
            std::cout << "Error ";
            delete[] a;
            exit(1);
        }
        std::uniform_real_distribution<double> dist(x, y);
        for (int i = 0; i < n; i++) {
            a[i] = dist(gen);
        }
        std::cout << "Your array: ";
        for (int i = 0; i < n; i++)
            std::cout << a[i] << ' ';
        std::cout << '\n';
        double max3 = a[0];
        max_el_ar(a, n, &max3);
        std::cout << "MAX element is " << max3 << '\n';
        std::cout << "SUM elements is " << sum(a, n) << '\n';

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (a[j] == a[i]) {
                    a[i + 100501]++;
                    for (int k = 100501; k < 100501 + i; k++) {
                        if (a[k - 100501] == a[i])
                            a[k] = 0;
                    }
                }
        }

        while (min_1_ch(a, n))
        {
            double max_tmp;
            int im = 0;

            ma_in_ar(a, n, &im);
            max_tmp = a[im];
            for (int i = 0; i < max_tmp; i++)
                std::cout << a[im - 100501] << ' ';
            a[im] = -1;
        }
    }

    
    delete[] a;

    return 0;
}