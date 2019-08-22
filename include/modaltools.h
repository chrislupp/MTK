//==============================================================================
//
//     __  ___          __      __   ______            __   __ __ _ __
//    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_
//   / /|_/ / __ \/ __  / __ `/ /    / / / __ \/ __ \/ /  / ,<  / / __/
//  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /
// /_/  /_/\____/\__,_/\__,_/_/    /_/  \____/\____/_/  /_/ |_/_/\__/
//
//
// University of Michigan
// Active Aeroelasticity and Structures Research Lab
//
// Author: Christopher A. Lupp
//
// Modal Tools
//
//==============================================================================
#pragma once


// system headers
#include <complex>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "mtk_datatypes.h"


using namespace std;
using namespace Eigen;


/*!
    \brief Computes the Modal Assurance Criterion between two vectors
*/
template<typename Type>
Type ComputeMAC(Matrix<std::complex<Type>, Eigen::Dynamic, 1> phi1,
    Matrix<std::complex<Type>, Eigen::Dynamic, 1> phi2)
{
    // note: {expression}(0) is used here as a work around to keep datatypes
    // consistent. This works in this scope, because the results of the
    // expressions must be a scalar. Thus, calling the first entry just
    // forces the output as a double.
    Type mac = (pow(abs((phi1.adjoint() * phi2)(0)), 2) /
        (phi1.adjoint() * phi1 * phi2.adjoint() * phi2)(0)).real();

    return mac;
};


/*!
    \brief Computes the Modal Assurance Criterion between two eigen pairs
*/
template<typename Type>
Type ComputeMAC(EigenPair<Type> pair1, EigenPair<Type> pair2)
{
    return ComputeMAC(pair1.evector, pair2.evector);
};


/*!
    \brief Comparison of two mode sets (using MAC)
*/
template<typename Type>
Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> SetsComputeMAC(ModeSet<Type> set1,
    ModeSet<Type> set2)
{
    typedef Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> tMatrix;

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