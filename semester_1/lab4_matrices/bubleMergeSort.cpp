#include<iostream>

void bubleSortArray(int* tmp, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (tmp[j] > tmp[j + 1])
				std::swap(tmp[j], tmp[j + 1]);
}

void bubleSortMatrix(int** a, int n, int m)
{
	for (int i = 0; i < n; i++)
		bubleSortArray(a[i], m);
}

void merge(int* a, int left, int mid, int right, int* tmp)
{
	int i = left;
	int j = mid;
	int k = left;

	while (i < mid && j < right)
	{
		if (a[i] <= a[j])
		{
			tmp[k] = a[i];
			i++;
		}
		else
		{
			tmp[k] = a[j];
			j++;
		}
		k++;
	}
	while (i < mid)
	{
		tmp[k] = a[i];
		i++;
		k++;
	}
	while (j < right)
	{
		tmp[k] = a[j];
		j++;
		k++;
	}

	for (int t = left; t < right; t++)
		a[t] = tmp[t];

}

void mergeSortArray(int* a, int size, int left, int right, int *tmp) 
{
	if (right - left <= 1) return;
	int mid = (left + right) / 2;

	mergeSortArray(a, size, left, mid, tmp);
	mergeSortArray(a, size, mid, right, tmp);

	merge(a, left, mid, right, tmp);
}

void mergeSortMatrix(int** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		int* tmp = new int[m];
		mergeSortArray(a[i], m, 0, m, tmp);
		delete[] tmp;
		
	} 
}

void insertionSortArray(int* a, int size) {
	for (int i = 1; i < size; i++) {
		int key = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

void insertionSortMatrix(int** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		insertionSortArray(a[i], m);
	}
}

void scan_rows_colomuns(int& n, int& m, char &c)
{
	std::cout << "Enter the number of rows and columns: ";
	std::cin >> n >> m;
	if (!std::cin)
	{
		std::cout << "Error";
		exit(1);
	}
	std::cout << "Choose a sort(1 - buble/2 - merge/ 3 - insert): ";
	std::cin >> c;
	if (!std::cin)
	{
		std::cout << "Error";
		exit(1);
	}
}

int** createMatrix(int n, int m)
{
	int** a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[m];
	}
	return a;
}

void scanMatrix(int n, int m, int** a) {
	std::cout << "Enter matrix: \n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			std::cin >> a[i][j];
			if (!std::cin)
			{
				std::cout << "Error";
				exit(1);
			}
		}

}

void printMartix(int n, int m, int** a)
{
	std::cout << "Your matrix: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << a[i][j] << ' ';
		std::cout << '\n';
	}
}

void deleteMatrix(int n, int m, int** a) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
}

int main()
{
	int n, m;
	char c;
	scan_rows_colomuns(n, m, c);
	int** a = createMatrix(n, m);
	scanMatrix(n, m, a);
	if (c == '1')
		bubleSortMatrix(a, n, m);
	else if (c == '2')
		mergeSortMatrix(a, n, m);
	else if (c == '3')
		insertionSortMatrix(a, n, m);
	else {
		std::cout << "Error";
		exit(1);
	}
	printMartix(n, m, a);
	deleteMatrix(n, m, a);
	return 0;
}