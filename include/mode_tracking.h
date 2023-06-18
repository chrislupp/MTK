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

// MTK headers
#include "eigen_pair.h"
#include "mode_set.h"
#include "modal_tools.h"

/*!
    \brief Mode tracking class
*/
template <typename Type>
class ModeTracker
{
public:
    // convenient type definition
    typedef Eigen::Matrix<std::complex<Type>, Eigen::Dynamic, 1> tVector;

    //! \brief Default constructor
    ModeTracker(){};

    //! \brief Destructor
    ~ModeTracker(){};

    //! \brief Sets the mode sets array to be tracked
    void SetData(vector<ModeSet<Type>> data) { data_ = data; };

    //! \brief Gets the mode sets array to be tracked
    ModeSet<Type> GetData() { return data_; };

    //! \brief Gets the mode sets array to be tracked
    vector<ModeSet<Type>> GetTrackedData() { return tracked_; };

    /*!
        \brief Tracks the modes
    */
    void Track()
    {
        // reset the results vector and preallocate memory
        tracked_.clear();
        tracked_.reserve(data_.size());

        // add seed set as initial ModeSet
        tracked_.push_back(data[0]);

        // iterate through every ModeSet
        for (int i = 0; i < data_.size() - 1; ++i)
        {
            ModeSet<Type> set_temp;

            vector<int> exclude;
            Type mac_temp;

            // iterate previous mode
            for (int j = 0; j < tracked_[i].Size(); ++j)
            {
                // best MAC for mode j
                int best_index = 0;
                Type mac_best = 0.0;

                std::complex<Type> best_val = data_[i + 1][0].evalue;
                tVector best_vec = data_[i + 1][0].evector;

                // previous mode
                tVector prev_mode = tracked_[i][j].evector;

                // compare to other modes
                for (int k = 0; k < data_[i + 1].Size(); ++k)
                {
                    if (find(exclude.begin(), exclude.end(), k) != exclude.end())
                    {
                        continue;
                    }
                    else
                    {
                        tVector current_mode = data_[i + 1][k].evector;
                        mac_temp = ComputeMAC(prev_mode, current_mode);
                    }

                    if (mac_temp > mac_best)
                    {
                        // set new best MAC
                        mac_best = mac_temp;

                        // save previous mode
                        best_index = k;
                        best_val = data_[i + 1][k].evalue;
                        best_vec = data_[i + 1][k].evector;
                    }
                }

                // save the best mode and blacklist mode index
                set_temp.AddPair(best_val, best_vec);
                exclude.push_back(best_index);
            }

            tracked_.push_back(set_temp);

            // reset blacklist
            exclude.clear();
        }
    };

private:
    //! \brief Vector of mode sets to be tracked
    std::vector<ModeSet<Type>> data_;

    //! \brief Vector of mode sets to be tracked
    std::vector<ModeSet<Type>> tracked_;
};