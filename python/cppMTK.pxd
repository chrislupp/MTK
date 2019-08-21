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
from libcpp.complex cimport complex

# Eigency
from eigency.core cimport *


# EigenPair (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass EigenPair[Type]:
        EigenPair() except +

        complex[Type] evalue

        PlainObjectBase evector

        void SetEvector(vector[Type] &input)

        complex[Type] operator[](int i)


# ModeSet (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass ModeSet[Type]:
        ModeSet() except +


# Modal Functions (C++)
cdef extern from "modaltools.h":
    cdef PlainObjectBase SetsComputeMAC[T](ModeSet[T] &set1, ModeSet[T] &set2)


# Mode Tracking (C++)
cdef extern from "modetracking.h":
    cdef vector[ModeSet] TrackModes[T](ModeSet[T] &seed, vector[ModeSet[T]] &data)