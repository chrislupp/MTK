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
#pragma once


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

	EigenPair(double eval, VectorXd evec);

    EigenPair(complex<double> eval, VectorXcd evec);

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
	// Constructors and Destructor
	ModeSet() {};

	ModeSet(VectorXd evals, MatrixXd evecs);

	ModeSet(VectorXcd evals, MatrixXcd evecs);

	~ModeSet() {};


	// add eigenpair to modeset
	void AddPair(double eval, VectorXd evec);

    void AddPair(complex<double> eval, VectorXcd evec);

	void AddPair(EigenPair input);


	// operators and simple functions
    EigenPair operator[](int index);

    int Size();

	VectorXcd OutputEValues();

	MatrixXcd OutputEVectors();

};