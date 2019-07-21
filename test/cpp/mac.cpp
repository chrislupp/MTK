

// system headers
#include <iostream>

// Eigen headers
#include <Eigen/Eigen>

// MTK headers
#include "modaltools.h"


using namespace std;


int main()
{

    // scalar MAC tests
    VectorXd v1(3), v2(3);

    v1 << 1.0, 0.0, 0.0;
    v2 << 0.0, 1.0, 0.0;

    double mac1 = ComputeMAC<double>(v1, v1);
    double mac2 = ComputeMAC<double>(v1, v2);

    if (mac1 != 1.0)
    {
        cout << "Scalar MAC test failed for double type. (A)" << endl
            << endl;
        return -1;
    }

    if (mac2 != 0.0)
    {
        cout << "Scalar MAC test failed for double type. (B)" << endl
            << endl;
        return -1;
    }


    VectorXcd vc1(3), vc2(3);

    vc1 << 1.0 + 1.0i, 0.0, 0.0;
    vc2 << 0.0, 1.0 + 1.0i, 0.0;

    mac1 = ComputeMAC<double>(vc1, vc1);
    mac2 = ComputeMAC<double>(vc1,vc2);

    if (mac1 != 1.0)
    {
        cout << "Scalar MAC test failed for double type. (C)" << endl
            << endl;
        return -1;
    }

    if (mac2 != 0.0)
    {
        cout << "Scalar MAC test failed for double type. (D)" << endl
            << endl;
        return -1;
    }
    



    // full mode set MAC tests
    VectorXd v3(3);
    v3 << 0.0, 0.0, 1.0;

    ModeSet<double> set1, set2;
    double temp = 0.0;

    set1.AddPair(temp, v1);
    set1.AddPair(temp, v2);
    set1.AddPair(temp, v3);

    set2.AddPair(temp, v2);
    set2.AddPair(temp, v1);
    set2.AddPair(temp, v3);

    MatrixXd mac_set1 = SetsComputeMAC<double>(set1, set1);

    MatrixXd mac_set2 = SetsComputeMAC<double>(set1, set2);

    MatrixXd ref1 = MatrixXd::Identity(3,3);
    MatrixXd ref2(3,3);
    ref2 << 0.0, 1.0, 0.0,
            1.0, 0.0, 0.0,
            0.0, 0.0, 1.0;


    if (mac_set1 != ref1)
    {
        cout << "MAC set test failed. (A)" << endl << endl;
        return -1;
    }

    if (mac_set2 != ref2)
    {
        cout << "MAC set test failed. (B)" << endl << endl;
        return -1;
    }

    return 0;
}