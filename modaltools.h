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

// system headers


// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "mtk_datatypes.h"


using namespace std;
using namespace Eigen;


// Modal Assurance Criterion
//------------------------------------------------------------------------------
double ComputeMAC(VectorXcd phi1, VectorXcd phi2)
{
    double mac = pow(abs(phi1.adjoint() * phi2), 2) / 
        (phi1.adjoint() * phi1 * phi2.adjoint() * phi2);

    return mac;
}



// Comparison of two mode sets (using MAC) 
//------------------------------------------------------------------------------
MatrixXd SetsComputeMAC(ModeSet set1, ModeSet set2)
{
    // preallocate MAC matrix
    MatrixXd mac(set1.pairs.size(), set2.pairs.size());

    for (int i; i < set1.pairs.size(); ++i)
    {
        for (int j; j < set2.pairs.size(); ++j)
        {
            mac(i,j) = ComputeMAC(modeset1.pairs[i],modeset2.pairs[j]);
        }
    }// need to overload [] or something to avoid ".pairs"
}
