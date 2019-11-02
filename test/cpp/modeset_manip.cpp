/*
    Modal Tool Kit (MTK)

    Copyright 2017-2019 Christopher A. Lupp

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

// system headers
#include <iostream>
#include <fstream>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "modaltools.h"

using namespace std;



int main()
{
    // test sort real
    //---------------
    ModeSet<double> test;

    VectorXd vec;

    test.AddPair(9.0, vec);
    test.AddPair(1.0, vec);
    test.AddPair(2.0, vec);
    test.AddPair(4.0, vec);
    test.AddPair(5.0, vec);
    test.AddPair(3.0, vec);
    test.AddPair(6.0, vec);
    test.AddPair(10.0, vec);
    test.AddPair(7.0, vec);
    test.AddPair(8.0, vec);


    // create an anonymous function used during the sorting process
    auto sort_func1 = [](EigenPair<double> x, EigenPair<double> y)
    -> bool
    {
        return x.evalue.real() < y.evalue.real();
    };


    // sort the mode set
    test.Sort(sort_func1);

    // check if the order is correct
    bool sorted = true;

    for (size_t i = 0; i < test.Size(); i++)
    {
        sorted = sorted && (test[i].evalue.real() == double(i+1));
    }
    
    if (!sorted)
    {
        cout << "sort test failed." << endl << endl;
        return -1;
    }


    // test sort imag
    //---------------
    ModeSet<double> testcomplex;

    VectorXcd vec2;

    testcomplex.AddPair(9.0 * 1i, vec2);
    testcomplex.AddPair(1.0 * 1i, vec2);
    testcomplex.AddPair(2.0 * 1i, vec2);
    testcomplex.AddPair(4.0 * 1i, vec2);
    testcomplex.AddPair(5.0 * 1i, vec2);
    testcomplex.AddPair(3.0 * 1i, vec2);
    testcomplex.AddPair(6.0 * 1i, vec2);
    testcomplex.AddPair(10.0 * 1i, vec2);
    testcomplex.AddPair(7.0 * 1i, vec2);
    testcomplex.AddPair(8.0 * 1i, vec2);


    // create an anonymous function used during the sorting process
    auto sort_func2 = [](EigenPair<double> x, EigenPair<double> y)
    -> bool
    {
        return x.evalue.imag() < y.evalue.imag();
    };


    // sort the mode set
    testcomplex.Sort(sort_func2);

    // check if the order is correct
    sorted = true;

    for (size_t i = 0; i < testcomplex.Size(); i++)
    {
        sorted = sorted && (testcomplex[i].evalue.imag() == double(i+1));
    }
    
    if (!sorted)
    {
        cout << "sort test failed." << endl << endl;
        return -1;
    }


    // test keep N modes
    //------------------
    testcomplex.KeepNModes(5);

    if (testcomplex.Size() != 5)
    {
        cout << "testcomplex size: " << testcomplex.Size() << endl;
        cout << "keep n modes test failed." << endl << endl;
        return -1;
    }


    // test mode deletion
    //-------------------
    test.DeleteMode(1);

    if (test[1].evalue.real() != 3.0)
    {
        cout << "delete test failed." << endl << endl;
        return -1;
    }


    // test multiple mode deletion
    //----------------------------
    test.DeleteModes({ 2, 3 });

    if (test[2].evalue.real() != 6.0 && test[3].evalue.real() != 7.0)
    {        
        cout << "multiple delete test failed." << endl << endl;
        return -1;
    }



    // test filter (window function)
    //------------------------------
    ModeSet<double> ftest;

    vector<double> ref = { 2.0, 4.0, 5.0, 3.0 };

    ftest.AddPair(9.0, vec);
    ftest.AddPair(1.0, vec);
    ftest.AddPair(2.0, vec);
    ftest.AddPair(4.0, vec);
    ftest.AddPair(5.0, vec);
    ftest.AddPair(3.0, vec);
    ftest.AddPair(6.0, vec);
    ftest.AddPair(10.0, vec);
    ftest.AddPair(7.0, vec);
    ftest.AddPair(8.0, vec);

    double low = 2.0;
    double up = 5.0;

    // create an anonymous function used during the filtering process
    auto filter_func = [low, up](EigenPair<double> x) -> bool
    {
        return (x.evalue.real() >= low) && (x.evalue.real() <= up);
    };

    // filter the mode set using the defined function
    ftest.Filter(filter_func);

    // check if the order is correct
    bool filtered = true;

    for (size_t i = 0; i < ftest.Size(); i++)
    {
        filtered = filtered && (ftest[i].evalue.real() == ref[i]);
    }
    
    if (!filtered)
    {
        // output the test values
        cout << "ftest:" << endl;

        for (size_t i = 0; i < ftest.Size(); i++)
            cout << ftest[i].evalue.real() << endl;

        cout << "filter test failed." << endl << endl;
        return -1;
    }


    return 0;
}