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

// Test the data assignment and retrieval.
TEST(EigenPairTests, Data)
{
    mtk::ModeSet<double> set = ModeSet();

    // # assign two different eigenpairs
    // a = EigenPair(1.0, [0.0, 1.0])
    // set.AddPair(a)
    // a.value = 2.0
    // a.vector = [1.0, 0.0]
    // set.AddPair(a)

    // # check the values and vectors
    // self.assertTrue((set.values == [1.0, 2.0]).all())
    // self.assertTrue((set.vectors == [[0.0, 1.0], [1.0, 0.0]]).all())
}