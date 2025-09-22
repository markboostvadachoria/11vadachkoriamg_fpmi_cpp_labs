#include<iostream>
#include<cmath>

bool pt(double n)
{
	
	if (n - trunc(n) == 0)
		return 1;
	return 0;
}

int main()
{
	using std::cout;
	using std::cin;
	
	int n;
	cin >> n;
	if (!cin || n < 0)
		exit(1);


	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			if (pt(sqrt(i * i - j * j))) {
				cout << j << ' ' << sqrt(i * i - j * j) << ' ' << i << '\n';
				break;
			}
	
	return 0;

}