/*
	Modal Tool Kit (MTK)

	Copyright 2017-2023 Christopher A. Lupp

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

// Eigen headers
#include <Eigen/Eigen>

namespace mtk
{
	/*!
		\brief EigenPair
	*/
	template <typename Type>
	class EigenPair
	{
		typedef Eigen::Matrix<std::complex<Type>, Eigen::Dynamic, 1> tVector;

	public:
		//! \brief Default constructor
		EigenPair() = default;

		/*!
			\brief Constructor from data

			\param eval Eigenvalue
			\param evec Eigenvector
		*/
		EigenPair(const Type &eval, const Eigen::VectorXd &evec)
		{
			evalue = std::complex<Type>(eval, 0.0);
			evector = tVector(evec);
		};

		/*!
			\brief Constructor from data

			\param eval Eigenvalue
			\param evec Eigenvector
		*/
		EigenPair(const std::complex<Type> &eval, const tVector &evec)
		{
			evalue = eval;
			evector = evec;
		};

		//! \brief Destructor
		~EigenPair() = default;

		void SetEigenPair(const EigenPair<Type> &pair)
		{
			evalue = pair.evalue;
			evector = pair.evector;
		}

		/*!
			\brief Gets the eigenvalue of the eigenpair

			\returns Eigenvalue (scalar)
		*/
		const std::complex<Type> &Evalue() const
		{
			return evalue;
		}

		/*!
			\brief Gets the eigenvector of the eigenpair

			\returns Eigenvector
		*/
		const Eigen::VectorXcd &Evector() const
		{
			return evector;
		}

		/*!
			\brief Sets the eigenvector of the eigenpair

			\returns Eigenvector
		*/
		void SetEvector(const std::vector<std::complex<Type>> &input)
		{
			evector = tVector::Zero(input.size());

			for (size_t i = 0; i < input.size(); i++)
				evector(i) = input[i];
		}

	private:
		//! \brief Eigenvalue
		std::complex<Type> evalue;

		//! \brief Eigenvector
		tVector evector;
	};
}