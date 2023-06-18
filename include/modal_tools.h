/*
    Modal Tool Kit (MTK)

    Copyright 2017-2023 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#pragma once

// system headers
#include <complex>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "eigen_pair.h"
#include "mode_set.h"

/*!
    \brief Computes the Modal Assurance Criterion between two vectors
*/
template <typename Type>
Type ComputeMAC(Eigen::Matrix<std::complex<Type>, Eigen::Dynamic, 1> phi1,
                Eigen::Matrix<std::complex<Type>, Eigen::Dynamic, 1> phi2)
{
    // note: {expression}(0) is used here as a work around to keep datatypes
    // consistent. This works in this scope, because the results of the
    // expressions must be a scalar. Thus, calling the first entry just
    // forces the output as a double.
    Type mac = (std::pow(std::abs((phi1.adjoint() * phi2)(0)), 2) /
                (phi1.adjoint() * phi1 * phi2.adjoint() * phi2)(0))
                   .real();

    return mac;
};

/*!
    \brief Computes the Modal Assurance Criterion between two eigen pairs
*/
template <typename Type>
Type ComputeMAC(EigenPair<Type> pair1, EigenPair<Type> pair2)
{
    return ComputeMAC(pair1.evector, pair2.evector);
};

/*!
    \brief Comparison of two mode sets (using MAC)
*/
template <typename Type>
Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> ComputeMAC(ModeSet<Type> set1,
                                                               ModeSet<Type> set2)
{
    typedef Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> tMatrix;

    // preallocate MAC matrix
    tMatrix mac;
    mac = tMatrix::Zero(set1.Size(), set2.Size());

    for (int i = 0; i < set1.Size(); ++i)
    {
        for (int j = 0; j < set2.Size(); ++j)
        {
            mac(i, j) = ComputeMAC(set1[i].evector, set2[j].evector);
        }
    }

    return mac;
};