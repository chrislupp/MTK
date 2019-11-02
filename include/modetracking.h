/*
    Modal Tool Kit (MTK)

    Copyright 2017 Christopher A. Lupp

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

// MTK headers
#include "mtk_datatypes.h"
#include "modaltools.h"


using namespace std;
using namespace Eigen;


// Mode Tracking (MAC-based)
template<typename Type>
vector<ModeSet<Type>> TrackModes(ModeSet<Type> seed, vector<ModeSet<Type>> data)
{
    typedef Matrix<std::complex<Type>, Dynamic, 1> tVector;

    // results array (of ModeSets)
    vector<ModeSet<Type>> result;

    // add seed set as initial ModeSet
    result.push_back(seed);
        
    // iterate through every ModeSet
    for (int i = 0; i < data.size() - 1; ++i)
    {
        ModeSet<Type> set_temp;

        vector<int> exclude;
        Type mac_temp;

        // iterate previous mode
        for (int j = 0; j < result[i].Size(); ++j) 
        {
            // best MAC for mode j
            int best_index = 0;
            Type mac_best = 0.0;

            complex<Type> best_val = data[i+1][0].evalue;
            tVector best_vec = data[i+1][0].evector;

            // previous mode
            tVector prev_mode = result[i][j].evector;

            // compare to other modes
            for (int k = 0; k < data[i+1].Size(); ++k)
            {
                if (find(exclude.begin(), exclude.end(), k) != exclude.end())
                {
                    continue;
                }
                else
                {
                    tVector current_mode = data[i+1][k].evector;
                    mac_temp = ComputeMAC(prev_mode, current_mode);
                }

                if (mac_temp > mac_best)
                {
                    // set new best MAC
                    mac_best = mac_temp;

                    // save previous mode
                    best_index = k;
                    best_val = data[i+1][k].evalue;
                    best_vec = data[i+1][k].evector;
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