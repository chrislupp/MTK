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

        void SetEigenPair(const EigenPair[Type] &pair)

        void SetEvector(vector[Type] &input)

        complex[Type] operator[](int i)


# ModeSet (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass ModeSet[Type]:
        ModeSet() except +

        vector[EigenPair[Type]] pairs_

        void AddPair(EigenPair[Type] &input)
        void AddPair(EigenPair[Type] *input)

        int Size()

        void SetPair(int i, EigenPair[Type] &input)


# Modal Functions (C++)
cdef extern from "modaltools.h":
    cdef PlainObjectBase SetsComputeMAC[T](ModeSet[T] &set1, ModeSet[T] &set2)

    Type ComputeMAC[Type](EigenPair[Type] pair1, EigenPair[Type] pair2)


# Mode Tracking (C++)
cdef extern from "modetracking.h":
    cdef vector[ModeSet] TrackModes[T](ModeSet[T] &seed, vector[ModeSet[T]] &data)