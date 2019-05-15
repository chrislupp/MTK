#===============================================================================
#
# MTK Python Interface
#
# Author: Christopher A. Lupp
#
#===============================================================================

# distutils: language = c++

# Cython imports
from libcpp cimport bool
from libcpp.vector cimport vector
from libcpp.string cimport string


# EigenPair (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass cppEigenPair:
        cppEigenPair() except +


# ModeSet (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass cppModeSet:
        cppEigenPair() except +



# EigenPair (wrapper)
cdef class EigenPair:
    cdef cppEigenPair *ptr


# ModeSet (wrapper)
cdef class ModeSet:
    cdef cppModeSet *ptr