#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <future>

#include "windows.h"

#include "logduration.h"

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size(); // количество строк
    int m = matrix[0].size(); // количество столбцов

    // Создание транспонированной матрицы
    vector<vector<int>> transposed_matrix(m, vector<int>(n));

    // Транспонирование матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposed_matrix[j][i] = matrix[i][j];
        }
    }

    return transposed_matrix;
}

int countUsuallyMult(const vector<int>& string, const vector<vector<int>>& matr, int row) {
    //матрица не кэшируется из-за чего скорость чуть ниже
    int sum = 0;
    for (size_t i = 0; i < string.size(); ++i){
        sum += string[i] * matr[i][row];
    }
    return sum;
}

int countOptMult(const vector<int>& string, const vector<int> row) {
    //пользуемя кэшем
    int sum = 0;
    for (size_t i = 0; i < string.size(); ++i) {
        sum += string[i] * row[i];
    }
    return sum;
}

void countParMult(const vector<vector<int>>& matr1, const vector<vector<int>>& matr2,
    vector<vector<int>>& matrix, int start, int finish) {
    for (size_t i = start; i < finish; i++)
    {
        for (size_t j = 0; j < matr1[i].size(); j++)
        {
            matrix[i][j] += countUsuallyMult(matr1[i], matr2, j);
        }
    }
}

vector<vector<int>> sequentialMultWithoutOpt(const vector<vector<int>>& matr1, const vector<vector<int>>& matr2)
{
    LOG_DURATION("sequential without optimizations");
    vector<vector<int>> matrix(matr1.size(), vector<int>(matr2.size()));
    for (size_t i = 0; i < matr1.size(); i++)
    {
        for (size_t j = 0; j < matr1[i].size(); j++)
        {
            matrix[i][j] += countUsuallyMult(matr1[i], matr2, j);
        }
    }
    return matrix;
}

vector<vector<int>> sequentialMultWithOpt(const vector<vector<int>>& matr1, const vector<vector<int>>& matr2)
{
    LOG_DURATION("sequential with optimizations");
    auto n_matr2 = transposeMatrix(matr2);
    vector<vector<int>> matrix(matr1.size(), vector<int>(n_matr2.size()));
    for (size_t i = 0; i < matr1.size(); i++)
    {
        for (size_t j = 0; j < matr1[i].size(); j++)
        {
            matrix[i][j] += countOptMult(matr1[i], n_matr2[j]);
        }
    }
    return matrix;
}

vector<vector<int>> parMult(const vector<vector<int>>& matr1, const vector<vector<int>>& matr2) {
    LOG_DURATION("par mult");
    vector<vector<int>> matrix(matr1.size(), vector<int>(matr2.size()));
    auto part_1 = async(countParMult, ref(matr1), ref(matr2), ref(matrix), 0, matr1.size() / 2);
    auto part_2 = async(countParMult, ref(matr1), ref(matr2), ref(matrix), matr1.size() / 2, matr1.size());
    return matrix;
}

vector<vector<int>> createMatrix(int num_matr)
{
    int count_string, count_columns;
    cout << "Введите количество столбцов, а затем количество строк " << num_matr << " матрицы\n";
    cin >> count_columns >> count_string;
    vector<vector<int>> matrix(count_string, vector<int>(count_columns));
    for (size_t i = 0; i < count_string; ++i)
    {
        for (size_t j = 0; j < count_columns; ++j)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, 10);
            matrix[i][j] = distrib(gen);
        }
    }
    return matrix;
}

void testAlgorithms()
{
    vector<vector<int>> matr1 = createMatrix(1);
    vector<vector<int>> matr2 = createMatrix(2);

    assert(matr1[0].size() == matr2.size());

    //sequential without opt
    sequentialMultWithoutOpt(matr1, matr2);

    //sequential with opt
    sequentialMultWithOpt(matr1, matr2);

    // par mult
    parMult(matr1, matr2);
}

int main()
{
    testAlgorithms();
}
