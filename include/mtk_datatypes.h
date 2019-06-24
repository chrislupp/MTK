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



/*!
	\brief EigenPair
*/
template<typename Type>
class EigenPair
{
public:
	//! \brief Default constructor
    EigenPair(){};

	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	EigenPair(Type eval, VectorXd evec);
	{
		evalue = complex<Type>(eval,0.0);
		evector = VectorXcd(evec);
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    EigenPair(complex<Type> eval, VectorXcd evec)
	{
		evalue = eval;
		evector = evec;
	};


	//! \brief Destructor
    ~EigenPair(){};


	/*!
		\brief Gets the eigenvalue of the eigenpair

		\returns Eigenvalue (scalar)
	*/
	complex<Type> Evalue()
	{
		return evalue;
	}


	/*!
		\brief Gets the eigenvector of the eigenpair

		\returns Eigenvector
	*/
	complex<Type> Evalue()
	{
		return evalue;
	}

private:
	//! \brief Eigenvalue
    complex<Type> evalue;

	//! \brief Eigenvector
    VectorXcd evector;
};




/*!
	\brief ModeSet
*/
template<typename Type>
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