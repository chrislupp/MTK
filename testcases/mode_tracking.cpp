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
// Benchmarks
//
//==============================================================================

// system headers
#include <iostream>

// Eigen headers
#include <Eigen/Eigen>

// HDF5 headers
#include "hdf5.h"
#include "eigen3-hdf5.hpp"

// MTK headers
#include "modetracking.h"


using namespace std;




int main(int argc, char* argv)
{
	string data_dir;

	if (argc > 1)
	{
		data_dir = argv[1];
	}
	else
	{
		data_dir = ".";
	}


	H5::H5File results("bwb_flutter_eigensolution.h5", H5F_ACC_TRUNC);


	cout << endl << "Running test cases of modal functions." << endl << endl;

    return 0;
}