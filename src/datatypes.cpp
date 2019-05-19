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
// Data Types
//
//==============================================================================


#include "mtk_datatypes.h"


EigenPair::EigenPair(double eval, VectorXd evec)
{
    evalue = complex<double>(eval,0.0);
    evector = VectorXcd(evec);
};


EigenPair::EigenPair(complex<double> eval, VectorXcd evec)
{
    evalue = eval;
    evector = evec;
};


ModeSet::ModeSet(VectorXd evals, MatrixXd evecs)
{
    for (int i = 0; i < evals.size(); i++)
    {
        AddPair(evals(i), evecs.col(i));
    }
};

ModeSet::ModeSet(VectorXcd evals, MatrixXcd evecs)
{
    for (int i = 0; i < evals.size(); i++)
    {
        AddPair(evals(i), evecs.col(i));
    }
};


// add eigenpair to modeset
void ModeSet::AddPair(double eval, VectorXd evec)
{
    pairs.push_back(EigenPair(eval, evec));
};

void ModeSet::AddPair(complex<double> eval, VectorXcd evec)
{
    pairs.push_back(EigenPair(eval, evec));
};

void ModeSet::AddPair(EigenPair input)
{
    pairs.push_back(input);
};


// operators and simple functions
EigenPair ModeSet::operator[](int index)
{
    return pairs[index];
};

int ModeSet::Size()
{
    return int(pairs.size());
};

VectorXcd ModeSet::OutputEValues()
{
    VectorXcd output(pairs.size());
    for (int i = 0; i < pairs.size(); i++)
    {
        output(i) = pairs[i].evalue;
    }

    return output;
};

MatrixXcd ModeSet::OutputEVectors()
{
    MatrixXcd output(pairs[0].evector.rows(),pairs.size());
    for (int i = 0; i < pairs.size(); i++)
    {
        output.col(i) = pairs[i].evector;
    }

    return output;
};