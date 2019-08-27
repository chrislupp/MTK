"""Modal Tool Kit
"""

# distutils: language = c++


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

def MAC(EigenPair pair1, EigenPair pair2):
    """Computes the modal assurance criterion between two eigen pairs.
    """
    return cppComputeMAC[double](pair1.ptr, pair2.ptr)


def SetMAC(ModeSet set1, ModeSet set2):
    """Computes the modal assurance criterion between two mode sets.
    """
    return ndarray(cppSetsComputeMAC(set1.ptr, set2.ptr))