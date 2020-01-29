"""
    Modal Tool Kit (MTK)

    Copyright 2017-2020 Christopher A. Lupp

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
from eigency.core cimport *

from MTK.Core cimport EigenPair as cppEigenPair,\
    ModeSet as cppModeSet,\
    ModeTracker as cppModeTracker
from MTK.Core cimport SetsComputeMAC as cppSetsComputeMAC, \
    ComputeMAC as cppComputeMAC, \
    TrackModes as cppTrackModes

cimport MTK.Core



cdef class EigenPair:
    """
    EigenPair datatype

    This class contains an eigenvalue/eigenvector pair and is intended for use
    within the Modal Tool Kit (MTK). Multiple EigenPair instances can be
    combined together to obtain a ModeSet.

    An EigenPair can be created with or without data on instantiation. If no
    data is assigned upon object instantiation, the eigenvalue/eigenvector can
    be set later using the corresponding public variables.
    """

    def __cinit__(self):
        self.ptr = cppEigenPair[double]()


    def __init__(self, eval=None, evec=None):
        if eval:
            self["value"] = eval

        if evec:
            self.ptr.SetEvector(evec)


    def __setitem__(self, item, input):
        """
        Index set operator (operator[]).
        """
        if (item == "value"):
            self.value = input
        elif(item == "vector"):
            self.vector = input
        else:
            raise ValueError("Wrong key during EigenPair assignment")

    def __getitem__(self, item):
        """
        Index get operator (operator[]).
        """
        if (item == "value"):
            return self.value
        elif(item == "vector"):
            return self.vector
        else:
            raise ValueError("Wrong key during EigenPair return")

    @property
    def value(self):
        return self.ptr.evalue

    @value.setter
    def value(self, input):
        self.ptr.evalue = input
    

    @property
    def vector(self):
        return ndarray(self.ptr.evector).flatten()

    @vector.setter
    def vector(self, input):
        self.ptr.SetEvector(input)



cdef class ModeSet:
    """
    ModeSet datatype

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

    def __cinit__(self):
        self.ptr = cppModeSet[double]()


    def __init__(self, evals=None, evecs=None):
        # assign the eigenpairs from data
        if evals and evecs:
            pass


    def __setitem__(self, i, EigenPair input):
        """
        Index set operator (operator[]).
        """
        if i > self.ptr.pairs_.size() or self.ptr.pairs_.size() == 0:
            raise ValueError("Vector of EigenPairs is smaller than index.")
        else:
            self.ptr.SetPair(i, input.ptr)


    def __getitem__(self, i):
        """
        Index get operator (operator[]).
        """
        if i > self.ptr.pairs_.size() or self.ptr.pairs_.size() == 0:
            raise ValueError("Vector of EigenPairs is smaller than index.")
        else:
            out = EigenPair()
            out.ptr.SetEigenPair(self.ptr.pairs_[i])
            return out


    @property
    def values(self):
        return ndarray(self.ptr.OutputEValues()).flatten()


    @property
    def vectors(self):
        return ndarray(self.ptr.OutputEVectors())


    def AddPair(self, EigenPair pair):
        """
        Adds an EigenPair to the ModeSet.
        """
        self.ptr.AddPair(pair.ptr)

    def Size(self):
        """
        Adds an EigenPair to the ModeSet.
        """
        return self.ptr.Size()



cdef class ModeTracker():
    """
    Mode tracking class.
    """

    def __cinit__(self):
        """
        """
        self.ptr = cppModeTracker[double]()


    def __init__(self):
        """
        """
        pass

    
    @property
    def seed(self):
        cdef ModeSet seed = ModeSet()
        seed.ptr = self.ptr.GetSeed()
        return seed

    @seed.setter
    def seed(self, seed_):
        self.SetSeed(seed_.ptr)


    @property
    def data(self):
        # temporary variables
        # n = len(data)
        # cdef vector[cppModeSet[double]] sequence
        # sequence.resize(n)
        # cdef ModeSet temp

        # # create a vector of ModeSets (C++)
        # for i in range(n):
        #     temp = data[i]
        #     sequence[i] = temp.ptr
        pass

    @data.setter
    def data(self, data_):
        # temporary variables
        n = len(data_)
        cdef vector[cppModeSet[double]] sequence
        sequence.resize(n)
        cdef ModeSet temp

        # allocate the C++ vector
        for i in range(n):
            temp = data_[i]
            sequence[i] = temp.ptr
        
        # set the data variable
        self.ptr.SetData(sequence)


    @property
    def tracked_data(self):
        # temporary variables
        # n = len(data)
        # cdef vector[cppModeSet[double]] sequence
        # sequence.resize(n)
        # cdef ModeSet temp

        # # create a vector of ModeSets (C++)
        # for i in range(n):
        #     temp = data[i]
        #     sequence[i] = temp.ptr
        pass


    def Track(self):
        """Tracks the modes.
        """
        self.ptr.Track()



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
    n = len(data)
    cdef vector[cppModeSet[double]] sequence
    sequence.resize(n)
    cdef ModeSet temp


    # create a vector of ModeSets (C++)
    for i in range(n):
        temp = data[i]
        sequence[i] = temp.ptr

    # run the mode tracking
    tracked = cppTrackModes(seed.ptr, sequence)

    # convert the result to ModeSet types
    for i in range(n):
        temp = ModeSet()
        temp.ptr = tracked[i]
        out.append(temp)

    return out