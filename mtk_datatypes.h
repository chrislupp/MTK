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
// Data Types
//
//==============================================================================

// system headers
#include <vector>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "modaltools.h"


using namespace std;
using namespace Eigen;


class EigenPair
{
public:
    double evalue;
    VectorXd evector;

    EigenPair(){};
    EigenPair(double eval, VectorXd evec)
    {
        evalue = eval;
        evector = evec;
    }

    ~EigenPair(){};
}



class ModeSet
{
public:
    vector<EigenPair> pairs;

    ModeSet(){};
    ~ModeSet(){};

    void AddPair(double eval, VectorXd evec)
    {
        pairs.push_back(EigenPair(eval, evec));
    }
}