"""
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
"""

# distutils: language = c++


from matplotlib.pyplot import *

from eigency.core cimport *

from MTK.Core cimport EigenPair as cppEigenPair
from MTK.Core cimport ModeSet as cppModeSet
from MTK.Core cimport SetsComputeMAC as cppSetsComputeMAC, \
    ComputeMAC as cppComputeMAC, \
    TrackModes as cppTrackModes

cimport MTK.Core


# from MTK.MTK cimport *




cdef class EigenPair:
    """EigenPair datatype

    This class contains an eigenvalue/eigenvector pair and is intended for use
    within the Modal Tool Kit (MTK). Multiple EigenPair instances can be
    combined together to obtain a ModeSet.

    An EigenPair can be created with or without data on instantiation. If no
    data is assigned upon object instantiation, the eigenvalue/eigenvector can
    be set later using the corresponding public variables.
    """

    def __cinit__(self, eval=None, evec=None):
        self.ptr = cppEigenPair[double]()


    def __setitem__(self, item, input):
        """Index set operator (operator[]).
        """
        if (item == "evalue"):
            self.ptr.evalue = input
        elif(item == "evector"):
            self.ptr.SetEvector(input)
        else:
            raise ValueError("Wrong key during EigenPair assignment")

    def __getitem__(self, item):
        """Index get operator (operator[]).
        """
        if (item == "evalue"):
            return self.ptr.evalue
        elif(item == "evector"):
            return ndarray(self.ptr.evector)
        else:
            raise ValueError("Wrong key during EigenPair return")



cdef class ModeSet:
    """ModeSet datatype

    A ModeSet consists of an array of EigenPairs. An illustrative example to
    describe a ModeSet are the frequency/mode shape combinations of a free
    vibration analysis. Each mode frequency corresponds to a specific mode shape
    (EigenPair), and the collection of all vibration modes may be seen as the
    ModeSet. The ModeSet datatype was specifically created for the use within
    the Modal Tool Kit (MTK) and enables the easy manipulation of sets of
    modes using mode tracking, etc.

    A ModeSet can be instantiated with or without data. If the object was
    created without data, set functions can be used to populate the eigenvalues
    and eigenvectors. 
    """

    def __cinit__(self, evals=None, evecs=None):
        self.ptr = cppModeSet[double]()


    def __setitem__(self, i, EigenPair input):
        """Index set operator (operator[]).
        """
        if i > self.ptr.pairs_.size() or self.ptr.pairs_.size() == 0:
            raise ValueError("Vector of EigenPairs is smaller than index.")
        else:
            self.ptr.SetPair(i, input.ptr)


    def __getitem__(self, i):
        """Index get operator (operator[]).
        """
        if i > self.ptr.pairs_.size() or self.ptr.pairs_.size() == 0:
            raise ValueError("Vector of EigenPairs is smaller than index.")
        else:
            out = EigenPair()
            out.ptr.SetEigenPair(self.ptr.pairs_[i])
            return out


    def AddPair(self, EigenPair pair):
        """Adds an EigenPair to the ModeSet.
        """
        self.ptr.AddPair(pair.ptr)

    def Size(self):
        """Adds an EigenPair to the ModeSet.
        """
        return self.ptr.Size()


def MAC(EigenPair pair1, EigenPair pair2):
    """Computes the modal assurance criterion between two eigen pairs.
    """
    return cppComputeMAC[double](pair1.ptr, pair2.ptr)


def SetMAC(ModeSet set1, ModeSet set2):
    """Computes the modal assurance criterion between two mode sets.
    """
    return ndarray(cppSetsComputeMAC(set1.ptr, set2.ptr))


def TrackModes(ModeSet seed, data):
    """Tracks the modes between an array of ModeSets.
    
    Returns:
        out: progression of mode-tracked modes
    """

    # array of tracked modes
    out = []

    # temporary variables
    temp = np.array(data, dtype=ModeSet)
    n = len(data)
    cdef vector[cppModeSet[double]] sequence
    sequence.resize(n)
    cdef ModeSet temp2 = ModeSet()


    # create a vector of ModeSets (C++)
    for i in range(n):
        temp2 = temp[i]
        sequence[i] = temp2.ptr

    # run the mode tracking
    tracked = cppTrackModes(seed.ptr, sequence)

    # convert the result to ModeSet types
    for i in range(n):
        temp2.ptr = tracked[i]
        out.append(temp2)

    return out


def PlotReal(var, data):
    """Plots the real mode progression over a variable.
    """
    N_sets = len(data)
    N_modes = data[0].Size()
    real = np.zeros([N_sets, N_modes])

    for i in range(N_sets):
        for j in range(N_modes):
            real[i,j] = data[i][j]["evalue"].real

    # plot the data
    plot(var, real)



def PlotImag(var, data):
    """Plots the imaginary mode progression over a variable.
    """

    N_sets = len(data)
    N_modes = data[0].Size()
    imag = np.zeros([N_sets, N_modes])

    for i in range(N_sets):
        for j in range(N_modes):
            imag[i,j] = data[i][j]["evalue"].imag

    # plot the data
    plot(var, imag)



def PlotRootLocus(data):
    """Plots the root locus of the given data.
    """
    N_sets = len(data)
    N_modes = data[0].Size()
    real = np.zeros([N_sets, N_modes])
    imag = np.zeros([N_sets, N_modes])

    for i in range(N_sets):
        for j in range(N_modes):
            real[i,j] = data[i][j]["evalue"].real
            imag[i,j] = data[i][j]["evalue"].imag

    # plot the data
    plot(real, imag)