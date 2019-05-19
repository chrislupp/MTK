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

from cppMTK cimport EigenPair as cppEigenPair
from cppMTK cimport ModeSet as cppModeSet


# EigenPair (wrapper)
cdef class EigenPair:
    cdef cppEigenPair *ptr


# ModeSet (wrapper)
cdef class ModeSet:
    cdef cppModeSet *ptr


# Modal Functions (wrapper)
cdef ComputeMAC(phi1, phi2)
cdef SetsComputeMAC(set1, set2)


# Mode Tracking (wrapper)
cdef TrackModes(seed, data)