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

#include <eigen_pair.h>

// Test the constructor.
TEST(EigenPairTests, Constructor)
{
    mtk::EigenPair<double> eigen_pair1 = mtk::EigenPair(1.0, {0.0, 1.0});

    // check the eigenvalue and eigenvector

    // #check the value and vector
    //             self.assertTrue(a["value"] == 1.0)
    //                 self.assertTrue((a["vector"] == [ 0.0, 1.0 ]).all())
    // a = EigenPair(1.0 + 1.0*1j, [0.0, 1.0 + 1.0 * 1j])

    // check other constructor
    // mtk::EigenPair<double> eigen_pair2 = mtk::EigenPair(1.0, {0.0, 1.0});

    //     # check the value and vector
    //     self.assertTrue(a["value"] == 1.0 + 1*1j)
    //     self.assertTrue((a["vector"] == [0.0, 1.0 + 1.0*1j]).all())
}

// Test the data assignment and retrieval.
TEST(EigenPairTests, Data)
{
    mtk::EigenPair<double> eigen_pair1 = mtk::EigenPair(1.0, {0.0, 1.0});
}
// def test_Properties(self):
//     """
//     Tests the evaluation of the value and vector properties.
//     """
//     a = EigenPair(1.0 + 1.0*1j, [0.0, 1.0 + 1.0 * 1j])

//     # check the value and vector
//     self.assertTrue(a.value == 1.0 + 1*1j)
//     self.assertTrue((a.vector == [0.0, 1.0 + 1.0*1j]).all())