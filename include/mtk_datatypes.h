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
	typedef Matrix<std::complex<Type>, Dynamic, 1> tVector;

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
		evector = tVector(evec);
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    EigenPair(complex<Type> eval, tVector evec)
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
    tVector evector;
};




/*!
	\brief ModeSet
*/
template<typename Type>
class ModeSet
{
	typedef Matrix<std::complex<Type>, Dynamic, Dynamic> tMatrix;
	typedef Matrix<std::complex<Type>, Dynamic, 1> tVector;

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
	ModeSet(tVector evals, MatrixXcd evecs)
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
		pairs_.push_back(EigenPair<Type>(eval, evec));
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    void AddPair(complex<Type> eval, tVector evec)
	{
		pairs_.push_back(EigenPair<Type>(eval, evec));
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	void AddPair(EigenPair<Type> input)
	{
		pairs_.push_back(input);
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    EigenPair<Type> operator[](int index)
	{
		return pairs_[index];
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
    int Size()
	{
		return int(pairs_.size());
	};


	/*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	tVector OutputEValues()
	{
		tVector output(pairs_.size());
		for (int i = 0; i < pairs_.size(); i++)
		{
			output(i) = pairs_[i].evalue;
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
		MatrixXcd output(pairs_[0].evector.rows(),pairs_.size());
		for (int i = 0; i < pairs_.size(); i++)
		{
			output.col(i) = pairs_[i].evector;
		}

		return output;
	};



	/*!
		\brief Sorts modeset eigenpairs

		This function sorts the eigenpairs by imaginary part in ascending order.
		By default the negative complex conjugate parts (if the mode set is
		complex) is discarded, leaving only the positive imaginary parts.

		\param discard_conjugate flag to discard the complex conjugate part if
		it is negative (default: false).
	*/
	void Sort(bool discard_conjugate=false)
	{
		
		
	}


	/*!
		\brief Deletes a single eigenpair from the mode set

		\param index index of the eigenpair to be discarded 
	*/
	void DeleteMode(int index)
	{
		pairs_.erase(pairs_.begin() + index);
	}


	/*!
		\brief Deletes a list of eigenpairs from the mode set

		The individual eigenpairs are deleted in reverse order of the given
		indices to avoid deleting the wrong 

		\param indices vector of indices of the eigenparis to be discarded 
	*/
	void DeleteModes(vector<int> indices)
	{
		// set the indices in descending order
		std::sort(indices.begin(), indices.end());
		std::reverse(indices.begin(), indices.end());

		// delete all eigenpairs from index (in descending order)
		for (int const &index: indices)
			pairs_.erase(pairs_.begin() + index);
	}


	/*!
		\brief Removes all except for the first N eigenpairs
	*/
	void KeepNModes(int n)
	{
		pairs_ = vector<EigenPair<Type>>(pairs_.begin(), pairs_.begin() + n + 1);
	}


private:
	//! \brief Modes (collection of eigenpairs)
    vector<EigenPair<Type>> pairs_;
};