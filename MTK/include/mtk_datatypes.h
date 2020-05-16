/*
    Modal Tool Kit (MTK)

    Copyright 2017-2020 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once


// system headers
#include <vector>
#include <cmath>
#include <algorithm>

// Eigen headers
#include <Eigen/Eigen>


using std::complex;
using std::vector;
using std::pow;
using std::find;
using std::sort;
using std::reverse;

using Eigen::Matrix;
using Eigen::VectorXd;
using Eigen::MatrixXd;
using Eigen::VectorXcd;
using Eigen::MatrixXcd;
using Eigen::Dynamic;



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

    void SetEigenPair(const EigenPair<Type> &pair)
    {
        evalue = pair.evalue;
        evector = pair.evector;
    }

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

    /*!
		\brief Sets the eigenvector of the eigenpair

		\returns Eigenvector
	*/
	void SetEvector(vector<complex<Type>> &input)
	{
        evector = tVector::Zero(input.size());

        for (size_t i=0; i < input.size(); i++)
            evector(i) = input[i];
	}

	//! \brief Eigenvalue
    complex<Type> evalue;

	//! \brief Eigenvector
    tVector evector;

private:
	
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
	ModeSet(tVector evals, tMatrix evecs)
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
	void AddPair(EigenPair<Type> &input)
	{
		pairs_.push_back(input);
	};

    /*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	void AddPair(EigenPair<Type> *input)
	{
		pairs_.push_back(*input);
	};

    /*!
		\brief Constructor from data

		\param eval Eigenvalue
		\param evec Eigenvector
	*/
	void SetPair(int i, EigenPair<Type> &input)
	{
		pairs_[i] = input;
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
			output.col(i) = pairs_[i].evector;

		return output;
	};


	/*!
		\brief Sorts modeset eigenpairs according to a defined function

		This function sorts the eigenpairs according to a predefined function.

		\param sort_func lambda function used to sort the eigenpairs
	*/
	void Sort(std::function<bool (EigenPair<Type>, EigenPair<Type>)> sort_func)
	{
		// sort the eigenpairs within the mode set
		std::sort(pairs_.begin(), pairs_.end(), sort_func);
	}


	/*!
		\brief Deletes all modes that do not fulfill the filter function

		\param filter lambda function that defines the filter

		\remarks The truth value of the filter function denotes if the filter
		has been satisfied. This means that a false value results in an
		exclusion of the mode.
	*/
	void Filter(std::function<bool (EigenPair<Type>)> filter)
	{
		// list of modes to be deleted
		vector<size_t> list;
		
		// find the indices of all modes that violate the filter
		for (size_t i = 0; i < pairs_.size(); i++)
			if (!filter(pairs_[i]))
				list.push_back(i);
		

		// delete the modes in list
		DeleteModes(list);
	}


	/*!
		\brief Deletes a single eigenpair from the mode set

		\param index index of the eigenpair to be discarded 
	*/
	void DeleteMode(size_t index)
	{
		pairs_.erase(pairs_.begin() + index);
	}


	/*!
		\brief Deletes a list of eigenpairs from the mode set

		The individual eigenpairs are deleted in reverse order of the given
		indices to avoid deleting the wrong mode.

		\param indices vector of indices of the eigenparis to be discarded 
	*/
	void DeleteModes(vector<size_t> indices)
	{
		// set the indices in descending order
		sort(indices.begin(), indices.end());
		reverse(indices.begin(), indices.end());

		// delete all eigenpairs from index (in descending order)
		for (size_t const &index: indices)
			DeleteMode(index);
	}

    /*!
		\brief Deletes a list of eigenpairs from the mode set

		The individual eigenpairs are deleted in reverse order of the given
		indices to avoid deleting the wrong mode.

		\param indices vector of indices of the eigenparis to be discarded 
	*/
	void ClearModes()
	{
		pairs_.clear();
	}

    /*
        \brief Removes all modes with imaginary part smaller than zero
    */
    void RemoveConjugates()
    {
        // create a list to contain indices of the modes that should be deleted
        vector<size_t> list;

        for (size_t i = 0; i < pairs_.size(); i++)
        {
            // mark a mode for deletion if its imaginary part is smaller than
            // zero
            if (pairs_[i].evalue.imag() < Type(0.0))
                list.push_back(i);
            else
                continue;
        }

        // delete all modes in the list
        DeleteModes(list);
    }

    /*!
        \brief Removes duplicate modes

        This function removes repeated modes from the set. Two modes are
        determined to be repeated if the imaginary part of their eigenvalues
        falls within a defined tolerance tolerance. The tolerance prescribes the
        number of repeated significant digits.

        \remark This operation is inherently expensive, as the method loops
        through all modes to check if there are duplicates.
    */
    void RemoveRepeatedModes(int tol)
    {
        // create a list to contain indices of the modes that should be deleted
        vector<size_t> list;

        for (size_t i = 0; i < pairs_.size(); i++)
        {
            for (size_t j = 0; j < pairs_.size(); j++)
            {
                // do not compare the mode to itself
                if (i==j)
                    continue;

                // check if the number of significant digits has been fulfilled
                bool repeated = abs(pairs_[i].evalue.imag() -
                    pairs_[i].evalue.imag()) < pow(0.1, tol)
                    * max(abs(pairs_[i].evalue.imag()),
                    * abs(pairs_[i].evalue.imag()));

                // Add the j-th mode to the deletion list, if the list does not
                // already contain it and it has been determined a duplicate
                if (repeated && find(list.begin(), list.end(), j) != list.end())
                    list.push_back(j);
            }
        }

        // delete modes in the list
        DeleteModes(list);
    }


	/*!
        \brief Removes all except for the first N eigenpairs

        \remarks The modes removed are the first N modes according to the
        storage vector. This means that if the modes are not ordered in
        ascending order the modes removed will be essentially random and not
        "everything after the first N in magnitude."
	*/
	void KeepNModes(int n)
	{
		pairs_ = vector<EigenPair<Type>>(pairs_.begin(), pairs_.begin() + n);
	}

    //! \brief Modes (collection of eigenpairs)
    vector<EigenPair<Type>> pairs_;
private:
	
};