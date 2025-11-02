#ifndef LIN_ALG_HPP
#define LIN_ALG_HPP

#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>

namespace Maths
{

class LinAlg
{

public:

    // AX + Y   (A has been flattened to 1D)
    static std::vector<double> axpy(
        const std::vector<double>& A_flat,
        std::size_t rows,
        std::size_t cols,
        const std::vector<double>& x,
        const std::vector<double>& y)
    {

        // Check sizes are correct for AX + Y
        if (A_flat.size() != rows * cols)
        {
            throw std::invalid_argument("A size does not match rows*cols");
        }
        if (x.size() != cols)
        {
            throw std::invalid_argument("x length must equal number of columns of A");
        }
        if (y.size() != rows)
        {
            throw std::invalid_argument("y length must equal number of rows of A");
        }

        // Vector to store results
        std::vector<double> out(rows, 0.0);

        // Do the calculation
        for (std::size_t i = 0; i < rows; ++i) 
        {
            auto acc = 0.0;
            const auto row_off = i * cols;
            for (std::size_t j = 0; j < cols; ++j) 
            {
                acc += A_flat[row_off + j] * x[j];
            }
            out[i] = acc + y[i];
        }
        return out;
    }
};

}

#endif