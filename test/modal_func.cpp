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

// MTK headers
#include "modaltools.h"

using namespace std;


int main(int arg, char* argv)
{

	cout << "     __  ___          __      __   ______            __   __ __ _ __" << endl;
	cout << "    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_" << endl;
	cout << "   / /|_/ / __ \\/ __  / __ `/ /    / / / __ \\/ __ \\/ /  / ,<  / / __/" << endl;
	cout << "  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /" << endl;
	cout << " /_/  /_/\\____/\\__,_/\\__,_/_/    /_/  \\____/\\____/_/  /_/ |_/_/\\__/" << endl << endl;

	cout << endl << "Running test cases of modal functions." << endl << endl;

    VectorXd v1(3), v2(3);

    v1 << 1.0, 0.0, 0.0;
    v2 << 0.0, 1.0, 0.0;

	cout << "MAC of real vectors:" << endl;
    cout << "v1 with v1: " << ComputeMAC(v1,v1) << endl;
	cout << "v1 with v1: " << ComputeMAC(v1, v2) << endl << endl;


    VectorXcd vc1(3), vc2(3);

    vc1 << 1.0 + 1.0i,0.0, 0.0;
    vc2 << 0.0, 1.0 + 1.0i, 0.0;

	cout << "MAC of complex vectors:" << endl;
    cout << "vc1 with vc1: " << ComputeMAC(vc1,vc1) << endl;
    cout << "vc1 with vc2: " << ComputeMAC(vc1,vc2) << endl << endl;


	VectorXd v3(3);
	v3 << 0.0, 0.0, 1.0;

	ModeSet set1, set2;
	double temp = 0.0;

	set1.AddPair(temp, v1);
	set1.AddPair(temp, v2);
	set1.AddPair(temp, v3);

	set2.AddPair(temp, v2);
	set2.AddPair(temp, v1);
	set2.AddPair(temp, v3);
	

	cout << "MAC real mode sets:" << endl;
	cout << "set1 with set1: " << endl << SetsComputeMAC(set1, set1) << endl << endl;
	cout << "set1 with set2: " << endl << SetsComputeMAC(set1, set2) << endl;

	cout << endl << "Test cases complete." << endl << endl;

    return 0;
}