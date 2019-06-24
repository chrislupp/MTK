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
	EigenPair(Type eval, VectorXd evec)
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
	complex<Type> Evector()
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
public:
	//! \brief Default constructor
	ModeSet() {};

	/*!
		\brief Constructor from data

		\param eval Eigenvalues (vector)
		\param evec Eigenvectors (matrix with columns representing the vectors)
	*/
	ModeSet(VectorXd evals, MatrixXd evecs)
	{
		for (int i = 0; i < evals.size(); i++)
		{
			AddPair(evals(i), evecs.col(i));
		}
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalues (vector)
		\param evec Eigenvectors (matrix with columns representing the vectors)
	*/
	ModeSet(VectorXcd evals, MatrixXcd evecs)
	{
		for (int i = 0; i < evals.size(); i++)
		{
			AddPair(evals(i), evecs.col(i));
		}
	};

	//! \brief Destructor
	~ModeSet() {};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	void AddPair(Type eval, VectorXd evec)
	{
		pairs.push_back(EigenPair<Type>(eval, evec));
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    void AddPair(complex<Type> eval, VectorXcd evec)
	{
		pairs.push_back(EigenPair<Type>(eval, evec));
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	void AddPair(EigenPair<Type> input)
	{
		pairs.push_back(input);
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    EigenPair<Type> operator[](int index)
	{
		return pairs[index];
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    int Size()
	{
		return int(pairs.size());
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	VectorXcd OutputEValues()
	{
		VectorXcd output(pairs.size());
		for (int i = 0; i < pairs.size(); i++)
		{
			output(i) = pairs[i].evalue;
		}

		return output;
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	MatrixXcd OutputEVectors()
	{
		MatrixXcd output(pairs[0].evector.rows(),pairs.size());
		for (int i = 0; i < pairs.size(); i++)
		{
			output.col(i) = pairs[i].evector;
		}

		return output;
	};


private:
	//! \brief Modes (collection of eigenpairs)
    vector<EigenPair<Type>> pairs;
};