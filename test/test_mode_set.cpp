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
#include <gtest/gtest.h>

#include <mode_set.h>

// Test the constructors.
TEST(ModeSetTests, Constructor)
{
    mtk::ModeSet<double> set1 = mtk::ModeSet<double>();

    // reference values
    Eigen::VectorXd vals(2);
    vals << 1.0, 2.0;

    Eigen::MatrixXd vecs(2, 2);
    vecs << 0.0, 1.0, 1.0, 0.0;

    // assign two different eigenpairs and add them to the mode set
    Eigen::VectorXd vec(2);
    vec << 0.0, 1.0;
    mtk::EigenPair<double> pair = mtk::EigenPair(1.0, vec);
    set1.AddPair(pair);

    vec(0) = 1.0;
    vec(1) = 0.0;
    pair.Set(mtk::EigenPair(2.0, vec));
    set1.AddPair(pair);

    // check the values and vectors
    EXPECT_TRUE(set1.OutputEValues().isApprox(vals));
    EXPECT_TRUE(set1.OutputEVectors().isApprox(vecs));

    // test other constructor
    mtk::ModeSet<double> set2(vals, vecs);

    // check the values and vectors
    EXPECT_TRUE(set2.OutputEValues().isApprox(vals));
    EXPECT_TRUE(set2.OutputEVectors().isApprox(vecs));
}

// Test the data assignment.
TEST(ModeSetTests, Data)
{
}