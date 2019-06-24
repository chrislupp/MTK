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
# cdef extern from "modaltools.h":
#     cdef double cppComputeMAC(VectorXcd phi1, VectorXcd phi2)

#     cdef MatrixXd cppSetsComputeMAC(ModeSet set1, ModeSet set2)


# # Mode Tracking (C++)
# cdef extern from "modetracking.h":
#     cdef vector[ModeSet] cppTrackModes(ModeSet seed, vector[ModeSet] data)