#===============================================================================
#
# MTK Python Interface
#
# Author: Christopher A. Lupp
#
#===============================================================================

# distutils: language = c++

from eigency.core cimport *

from cppMTK cimport EigenPair as cppEigenPair
from cppMTK cimport ModeSet as cppModeSet

from MTK cimport *


"""
Modal Tool Kit
"""

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

    def __cinit__(self, eval=None, evec=None):
        self.ptr = new cppEigenPair[double]()



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

    def __cinit__(self, evals=None, evecs=None):
        self.ptr = new cppModeSet[double]()


# cdef ComputeMAC(phi1, phi2):
#     """
#     Computes the Modal Assurance Criterion (MAC) between two vectors.
#     """
#     return 0.0


# cdef SetsComputeMAC(set1, set2):
#     """
#     Computes the Modal Assurance Criterion (MAC) between two s.
#     """
#     return 0.0


# cdef TrackModes(seed, data):
#     """
#     Tracks the modes over a vector of ModeSets from a seed ModeSet.
#     """
#     return 0.0