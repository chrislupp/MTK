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


# EigenPair (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass EigenPair[T]:
        EigenPair() except +


# ModeSet (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass ModeSet[T]:
        ModeSet() except +


# Modal Functions (C++)
cdef extern from "modaltools.h":
    cdef MatrixXd SetsComputeMAC[T](ModeSet[T] &set1, ModeSet[T] &set2) except +


# Mode Tracking (C++)
cdef extern from "modetracking.h":
    cdef vector[ModeSet] TrackModes[T](ModeSet[T] seed, vector[ModeSet[T]] data) except +