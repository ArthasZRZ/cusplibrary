/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file multilevel.h
 *  \brief Multilevel hierarchy
 *
 */

#pragma once

#include <cusp/detail/config.h>
#include <cusp/detail/lu.h>

#include <cusp/array1d.h>
#include <cusp/linear_operator.h>

namespace cusp
{

/*! \addtogroup iterative_solvers Multilevel hiearchy
 *  \ingroup iterative_solvers
 *  \{
 */

/*! \p multilevel : multilevel hierarchy
 *
 *
 *  TODO
 */
template <typename MatrixType, typename SmootherType>
class multilevel : public cusp::linear_operator<typename MatrixType::value_type,
    						typename MatrixType::memory_space>
{
public:

    typedef typename MatrixType::value_type ValueType;
    typedef typename MatrixType::memory_space MemorySpace;

    struct level
    {
        MatrixType R;  // restriction operator
        MatrixType A;  // matrix
        MatrixType P;  // prolongation operator
        cusp::array1d<ValueType,MemorySpace> x;               // per-level solution
        cusp::array1d<ValueType,MemorySpace> b;               // per-level rhs
        cusp::array1d<ValueType,MemorySpace> residual;        // per-level residual

        SmootherType smoother;
    };

    cusp::detail::lu_solver<ValueType, cusp::host_memory> LU;

    std::vector<level> levels;

    template <typename Array1, typename Array2>
    void operator()(const Array1& x, Array2& y);

    template <typename Array1, typename Array2>
    void solve(const Array1& b, Array2& x);

    template <typename Array1, typename Array2, typename Monitor>
    void solve(const Array1& b, Array2& x, Monitor& monitor);

    void print( void );

    double operator_complexity( void );

    double grid_complexity( void );

protected:

    template <typename Array1, typename Array2>
    void _solve(const Array1& b, Array2& x, const size_t i);
};
/*! \}
 */

} // end namespace cusp

#include <cusp/detail/multilevel.inl>

