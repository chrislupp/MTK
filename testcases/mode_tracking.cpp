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
#include <chrono>

// Eigen headers
#include <Eigen/Eigen>

// HDF5 headers
#include "hdf5.h"
#include "eigen3-hdf5.hpp"

// MTK headers
#include "modetracking.h"


using namespace std;


int main(int argc, char **argv)
{
	cout << "     __  ___          __      __   ______            __   __ __ _ __" << endl;
	cout << "    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_" << endl;
	cout << "   / /|_/ / __ \\/ __  / __ `/ /    / / / __ \\/ __ \\/ /  / ,<  / / __/" << endl;
	cout << "  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /" << endl;
	cout << " /_/  /_/\\____/\\__,_/\\__,_/_/    /_/  \\____/\\____/_/  /_/ |_/_/\\__/" << endl << endl;

	string data_dir;

	if (argc > 1)
	{
		data_dir = string(argv[1]);
	}
	else
	{
		data_dir = ".";
	}

	cout << endl << "Running mode tracking benchmarks." << endl << endl;


	//--------------------------------------------------------------------------
	// Tracking of Real Modes
	//--------------------------------------------------------------------------
	H5::H5File results("modetracking_results.h5", H5F_ACC_TRUNC);

	VectorXd eval;
	MatrixXd evec;

	vector<ModeSet> real_sets;


	// read in real eigenvalues and eigenvectors (deformed modal simulation sweep, Al ruler)
	for (int i = 0; i < 11; i++)
	{
		string fname1 = data_dir + "/modal_results_" + to_string(i) + ".h5";
		H5::H5File data1(fname1, H5F_ACC_RDONLY);
		EigenHDF5::load(data1, "/nast_modalsolver/mode_freq", eval);
		EigenHDF5::load(data1, "/nast_modalsolver/modeshape_eps", evec);

		real_sets.push_back(ModeSet(eval, evec));
	}
	

	// run modetracking and time it
	cout << "Tracking of real modes:" << endl;
	auto t1 = std::chrono::high_resolution_clock::now();
	vector<ModeSet> real_sorted = TrackModes(real_sets);
	auto t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> time = t2 - t1;

	cout << "completed in " << time.count() << " ms." << endl << endl;

	results.createGroup("/real_modes");

	for (int i = 0; i < real_sorted.size(); i++)
	{
		results.createGroup("/real_modes/step_" + to_string(i));
		EigenHDF5::save(results, "/real_modes/step_" + to_string(i) + "/eval_real", real_sorted[i].OutputEValues().real());
		EigenHDF5::save(results, "/real_modes/step_" + to_string(i) + "/evec_real", real_sorted[i].OutputEVectors().real());
	}


	//--------------------------------------------------------------------------
	// Tracking of Complex Modes
	//--------------------------------------------------------------------------
	string fname2 = data_dir + "/bwb_flutter_eigensolution.h5";
	H5::H5File data2(fname2, H5F_ACC_RDONLY);

	VectorXd eval_real, eval_imag;
	MatrixXd evec_real, evec_imag;

	vector<ModeSet> imag_sets;


	// read in complex eigenvalues and eigenvectors (flutter results, BWB)
	for (int i = 0; i < 20; i++)//change 20 to length of search
	{
		EigenHDF5::load(data2, "/nast_flutsolver/search_" + to_string(i) + "/evalues_real", eval_real);
		EigenHDF5::load(data2, "/nast_flutsolver/search_" + to_string(i) + "/evalues_imag", eval_imag);
		EigenHDF5::load(data2, "/nast_flutsolver/search_" + to_string(i) + "/evectors_real", evec_real);
		EigenHDF5::load(data2, "/nast_flutsolver/search_" + to_string(i) + "/evectors_imag", evec_imag);

		VectorXcd temp_values = eval_real + eval_imag * 1i;
		MatrixXcd temp_vecs = evec_real + evec_imag * 1i;

		imag_sets.push_back(ModeSet(temp_values,temp_vecs));
	}

	// run modetracking and time it
	cout << "Tracking of complex modes:" << endl;
	t1 = std::chrono::high_resolution_clock::now();
	vector<ModeSet> imag_sorted = TrackModes(imag_sets);
	t2 = std::chrono::high_resolution_clock::now();

	time = t2 - t1;

	cout << "completed in " << time.count() << " ms."<< endl;

	results.createGroup("/complex_modes");

	for (int i = 0; i < imag_sorted.size(); i++)
	{
		results.createGroup("/complex_modes/step_" + to_string(i));
		EigenHDF5::save(results, "/complex_modes/step_" + to_string(i) + "/eval_real", imag_sorted[i].OutputEValues().real());
		EigenHDF5::save(results, "/complex_modes/step_" + to_string(i) + "/eval_imag", imag_sorted[i].OutputEValues().imag());
		EigenHDF5::save(results, "/complex_modes/step_" + to_string(i) + "/evec_real", imag_sorted[i].OutputEVectors().real());
		EigenHDF5::save(results, "/complex_modes/step_" + to_string(i) + "/evec_imag", imag_sorted[i].OutputEVectors().imag());
	}
	

	cout << endl << "Test complete." << endl << endl;
	

    return 0;
}