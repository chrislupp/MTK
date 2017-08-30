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
#ifndef MTK_MODALTOOLS_H

#define MTK_MODALTOOLS_H


// system headers
#include <complex>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "mtk_datatypes.h"


using namespace std;
using namespace Eigen;


// Modal Assurance Criterion
//------------------------------------------------------------------------------
inline double ComputeMAC(VectorXcd phi1, VectorXcd phi2)
{
	// note: {expression}(0) is used here as a work around to keep datatypes
	// consistent. This works in this scope, because the results of the
	// expressions must be a scalar. Thus, calling the first entry just
	// forces the output as a double.
    double mac = (pow(abs((phi1.adjoint() * phi2)(0)), 2) / 
        (phi1.adjoint() * phi1 * phi2.adjoint() * phi2)(0)).real();

    return mac;
};



// Comparison of two mode sets (using MAC)
//------------------------------------------------------------------------------
inline MatrixXd SetsComputeMAC(ModeSet set1, ModeSet set2)
{
    // preallocate MAC matrix
	MatrixXd mac;
	mac = MatrixXd::Zero(set1.Size(), set2.Size());

    for (int i = 0; i < set1.Size(); ++i)
    {
        for (int j = 0; j < set2.Size(); ++j)
        {
			mac(i, j) = ComputeMAC(set1[i].evector, set2[j].evector);
        }
    }

	return mac;
};


#endif