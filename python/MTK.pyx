"""Modal Tool Kit
"""

# distutils: language = c++


from eigency.core cimport *

from cppMTK cimport EigenPair as cppEigenPair
from cppMTK cimport ModeSet as cppModeSet
from cppMTK cimport SetsComputeMAC as cppSetsComputeMAC, TrackModes as cppTrackModes
cimport cppMTK


from MTK cimport *




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
        self.ptr = new cppEigenPair[double]()


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
        self.ptr = new cppMTK.ModeSet[double]()


    def __setitem__(self, i, input):
        """Index set operator (operator[]).
        """
        pass

    def __getitem__(self, i):
        """Index get operator (operator[]).
        """
        pass