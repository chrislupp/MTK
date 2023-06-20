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
#include <Eigen/Eigen>
#include <gtest/gtest.h>

#include <eigen_pair.h>

// Test the constructor.
TEST(EigenPairTests, Constructor)
{
    Eigen::VectorXd vec(2);
    vec << 0.0, 1.0;
    mtk::EigenPair<double> eigen_pair1 = mtk::EigenPair(1.0, vec);

    // check that all values were assigned correctly
    EXPECT_TRUE(eigen_pair1.Evalue().real() == 1.0);
    EXPECT_TRUE(eigen_pair1.Evector().real().isApprox(vec));

    Eigen::VectorXcd vec_cplx(2);
    vec_cplx << std::complex<double>(1.0, 1.0), std::complex<double>(1.0, 1.0);
    mtk::EigenPair<double> eigen_pair2 = mtk::EigenPair(std::complex(1.0, 1.0), vec_cplx);

    // check that all values were assigned correctly
    EXPECT_TRUE(eigen_pair2.Evalue().real() == 1.0);
    EXPECT_TRUE(eigen_pair2.Evalue().imag() == 1.0);
    EXPECT_TRUE(eigen_pair2.Evector().isApprox(vec_cplx));
}