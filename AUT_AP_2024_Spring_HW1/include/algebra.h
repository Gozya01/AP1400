#ifndef AUT_AP_2024_Spring_HW1
#define AUT_AP_2024_Spring_HW1
#include<vector>
#include<optional>
#include<cstdlib>
#include<iostream>
#include<format>
#include<random>
#include <stdexcept>
namespace algebra{
    template<typename T>
    using MATRIX = std::vector<std::vector<T>>;

    enum class MatrixType { Zeros, Ones, Identity, Random };

    template<typename T>
    MATRIX<T> create_matrix(std::size_t rows, 
                            std::size_t columns, 
                            std::optional<MatrixType> type = MatrixType::Zeros,
                            std::optional<T> lowerBound = std::nullopt, 
                            std::optional<T> upperBound = std::nullopt);
    template<typename T>
    void display(const MATRIX<T>& matrix);

    template<typename T>
    MATRIX<T> sum_sub(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB, std::optional<std::string> operation = "sum");

    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrix, const T scalar);

    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB);

    template<typename T>
    MATRIX<T> hadamard_product(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB);

    template<typename T>
    MATRIX<T> transpose(const MATRIX<T>& matrix);

    template<typename T>
    T trace(const MATRIX<T>& matrix);

    template<typename T>
    double determinant(const MATRIX<T>& matrix);

    template<typename T>
    MATRIX<double> inverse(const MATRIX<T>& matrix);


}
#endif //AUT_AP_2024_Spring_HW1
