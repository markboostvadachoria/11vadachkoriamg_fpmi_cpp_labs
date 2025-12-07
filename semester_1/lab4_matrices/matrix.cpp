#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>




size_t input(std::string &in, const std::string& digital_string)
{
    const int max_n = 45, max_string_n = 10;

    if (in.empty())
        throw "Input something";
    if (in[0] == '0' && in.size() > 1)
        throw "Error: input a ineger number(> 0)(< 45)";
    for (size_t i = 0; i < in.size(); i++)
        if (std::find(digital_string.begin(), digital_string.end(), in[i]) == digital_string.end())
            throw "Error: input a ineger number(> 0)(< 45)";
    if (in.size() > max_string_n)
        throw "Enter a smaller number";
    size_t n = std::stoi(in);
    if (n > max_n)
        throw "Enter a smaller number";
    if (n == 0)
        throw "Matrix is empty";
    return n;
}

int** createMatrix(size_t n)
{
    int** matrix = new int*[n];
    for (size_t rows = 0; rows < n; rows++)
        matrix[rows] = new int[n];
    return matrix;
}

void deleteMatrix(size_t n, int** matrix)
{
    for (size_t rows = 0; rows < n; rows++)
        delete[] matrix[rows];
    delete[] matrix;

}

void oneSpiralBranch(int** matrix, size_t n, int& matrix_element, int& diag_i, const int& max_matrix_el, int& diag_sum)
{
    for (size_t col = diag_i; col < n - diag_i && matrix_element <= max_matrix_el; col++)
    {
        matrix[diag_i][col] = matrix_element;
        matrix_element++;
    }
    for (size_t rows = diag_i + 1; rows < n - diag_i && matrix_element <= max_matrix_el; rows++)
    {
        matrix[rows][n - diag_i - 1] = matrix_element;
        matrix_element++;
    }
    for (size_t col = 0; col <= n - 2 * diag_i - 2 && matrix_element <= max_matrix_el; col++)
    {
        matrix[n - diag_i - 1][n - diag_i - 2 - col] = matrix_element;
        matrix_element++;
    }
    for (size_t rows = 0; rows < n - 2 - 2 * diag_i && matrix_element <= max_matrix_el; rows++)
    {
        matrix[n - diag_i  - 2 - rows][diag_i] = matrix_element;
        matrix_element++;
    }
    diag_sum += (matrix[diag_i][n - 1 - diag_i] + matrix[n - 1 - diag_i][diag_i]); 
    diag_i++;
}

void printMatrix(int** matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        {
            for (size_t k = 0; k < n; k++)
                std::cout << std::setw(6) << matrix[i][k];
            std::cout << '\n';
        }       

}

int fillMatrixSpiralAndSecondSideSum(int** matrix, size_t n)
{
    int matrix_element = 1;
    int diag_i = 0, diag_sum = 0;
    const int max_matrix_element = n * n;
    while (matrix_element <= max_matrix_element)
        oneSpiralBranch(matrix, n, matrix_element, diag_i, max_matrix_element, diag_sum);
    return diag_sum;
}

int main()
{
    int** matrix = nullptr;
    size_t n = 0;
    try{
        const std::string digital_string = "1234567890";
        std::string in;
        std::cout << "Enter a matrix side size: ";
        std::getline(std::cin, in);
        n = input(in, digital_string);
        
        matrix = createMatrix(n);
        int diag_sum = fillMatrixSpiralAndSecondSideSum(matrix, n); 
       // oneSpiralBranch(matrix, n, 1, 0);
        printMatrix(matrix, n);
        std::cout << std::endl << "Second size sum = " << diag_sum; 
        deleteMatrix(n, matrix);
        
        
    }catch(const char* error_message)
    {
        if (matrix != nullptr)
            deleteMatrix(n, matrix);
     
        std::cout << error_message;
    }
    


   return 0;
}
