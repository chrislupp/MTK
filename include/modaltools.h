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
double ComputeMAC(VectorXcd phi1, VectorXcd phi2);

// Comparison of two mode sets (using MAC)
MatrixXd SetsComputeMAC(ModeSet set1, ModeSet set2);


#endif