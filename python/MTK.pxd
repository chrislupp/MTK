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

# Eigency
from eigency.core cimport *

from MTK.Core cimport EigenPair as cppEigenPair
from MTK.Core cimport ModeSet as cppModeSet


# EigenPair (wrapper)
cdef class EigenPair:
    cdef cppEigenPair[double] ptr


# ModeSet (wrapper)
cdef class ModeSet:
    cdef cppModeSet[double] ptr