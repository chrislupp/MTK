#===============================================================================
#
# MTK Python Interface
#
# Author: Christopher A. Lupp
#
#===============================================================================

# distutils: language = c++


cdef class EigenPair:
    """
    EigenPair

    This class contains an eigenvalue/eigenvector pair and is intended for use
    within the Modal Toolkit (MTK). Multiple EigenPair instances can be combined
    together to obtain a ModeSet.

    An EigenPair can be created with or without data on instantiation. If no
    data is assigned upon object instantiation, the eigenvalue/eigenvector can
    be set later using the corresponding public variables.
    """

    def __cinit__(self, eval=None, evec=None):
        self.ptr = new cppEigenPair()



cdef class ModeSet:
    """
    ModeSet

    A ModeSet consists of an array of EigenPairs. An illustrative example to
    describe a ModeSet are the frequency/mode shape combinations of a free
    vibration analysis. Each mode frequency corresponds to a specific mode shape
    (EigenPair), and the collection of all vibration modes may be seen as the
    ModeSet. The ModeSet datatype was specifically created for the use within
    the Modal Toolkit (MTK) and enables the easy manipulation of ModeSets using
    mode tracking, etc.

    A ModeSet can be instantiated with and without data. If the object was
    created without data, set functions can be used to populate the eigenvalues
    and eigenvectors. 
    """

    def __cinit__(self, evals=None, evecs=None):
        self.ptr = new cppModeSet()