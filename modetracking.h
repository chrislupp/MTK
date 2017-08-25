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

// system headers
#include <vector>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "mtk_datatypes.h"
#include "modaltools.h"


using namespace std;
using namespace Eigen;


// Mode Tracking
//------------------------------------------------------------------------------
vector<ModeSet> TrackModes(vector<ModeSet> data)
{
    // results array (of ModeSets)
    vector<ModeSet> result;

    // temporary modeset for results
    ModeSet set_temp;

    for (int i = 0; i < data[0].pairs.size(); ++i)
     {
        if (data[0].pairs[i].evalue.imag >= 0)
        {
            set_temp.AddPair(data[0].pairs[i].evalue, data[0].pairs[i].evector);
            result.push_back(set_temp)
        }
     }
        

    for (int i = 0; i < data.size() - 1; ++i)
    {
        // blacklist
        vector<int> exclude;

        for j in range(len(result[i-1].pairs))
        {
            // best MAC for mode j
            best_index = 0;
            mac_best = 0.0;

            double best_val = data[i+1].pairs[0].evalue;
            VectorXd best_vec = data[i+1].pairs[0].evector;


            // previous mode
            VetorXd prev_mode = result[i].pairs[j].evector;

            for k in range(len(data[i+1].pairs))
            {
                if (k in exclude)
                {
                    continue;
                }
                else
                {
                    current_mode = data[i+1].pairs[k].evector;
                    mac_temp = MAC(prev_mode, current_mode);
                }

                if (mac_temp > mac_best)
                {
                    // set new best MAC
                    mac_best = mac_temp;

                    // save previous mode
                    best_index = k;
                    best_val = data[i+1].pairs[k].evalue;
                    best_vec = data[i+1].pairs[k].evector;
                }
            }

            // save the best mode and blacklist mode index
            set_temp.AddPair(best_val, best_vec);
            exclude.push_back(best_index);
        }
        
        result.push_back(set_temp);

        // reset blacklist
        exclude.clear();
    }

    return result;
}