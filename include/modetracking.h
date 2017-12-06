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
// Mode Tracking
//
//==============================================================================
#ifndef MTK_MODETRACKING_H

#define MTK_MODETRACKING_H

// system headers
#include <vector>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "mtk_datatypes.h"
#include "modaltools.h"


using namespace std;
using namespace Eigen;


// Mode Tracking (MAC-based)
vector<ModeSet> TrackModes(vector<ModeSet> data);

#endif