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
#ifndef MTK_DATATYPES_H

#define MTK_DATATYPES_H


// system headers
#include <vector>

// Eigen headers
#include <Eigen/Eigen>


using namespace std;
using namespace Eigen;


// EigenPair
//------------------------------------------------------------------------------
// pair of eigenvalue and eigenvector
//------------------------------------------------------------------------------
class EigenPair
{
public:
    complex<double> evalue;
    VectorXcd evector;

    EigenPair(){};

	EigenPair(double eval, VectorXd evec)
	{
		evalue = eval + 0i;
		evector = evec + VectorXd::Zero(evec.size())*1i;
	};

    EigenPair(complex<double> eval, VectorXcd evec)
    {
        evalue = eval;
        evector = evec;
	};

    ~EigenPair(){};
};


// ModeSet
//------------------------------------------------------------------------------
// set of eigenpairs
//------------------------------------------------------------------------------
class ModeSet
{
private:
    vector<EigenPair> pairs;

public:
    
    ModeSet(){};
    ~ModeSet(){};

	void AddPair(double eval, VectorXd evec)
	{
		pairs.push_back(EigenPair(eval, evec));
	};

    void AddPair(complex<double> eval, VectorXcd evec)
    {
        pairs.push_back(EigenPair(eval, evec));
	};

	void AddPair(EigenPair input)
	{
		pairs.push_back(input);
	};

    EigenPair operator[](int index)
    {
        return pairs[index];
	};

    int Size()
    {
        return int(pairs.size());
	};
};

#endif