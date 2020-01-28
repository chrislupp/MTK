"""
    Modal Tool Kit (MTK)

    Copyright 2017-2020 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
"""

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

        void SetEigenPair(const EigenPair[Type] &pair) except +

        void SetEvector(vector[Type] &input) except +

        complex[Type] operator[](int i) except +


# ModeSet (C++)
cdef extern from "mtk_datatypes.h":
    cdef cppclass ModeSet[Type]:
        ModeSet() except +

        vector[EigenPair[Type]] pairs_

        void AddPair(EigenPair[Type] &input) except +
        void AddPair(EigenPair[Type] *input) except +

        PlainObjectBase OutputEValues()

        PlainObjectBase OutputEVectors()

        void SetPair(int i, EigenPair[Type] &input) except +

        int Size() except +


# Modal Functions (C++)
cdef extern from "modaltools.h":
    cdef PlainObjectBase SetsComputeMAC[T](ModeSet[T] &set1,\
        ModeSet[T] &set2)

    Type ComputeMAC[Type](EigenPair[Type] pair1, EigenPair[Type] pair2) except +


# Mode Tracking (C++, object-oriented)
cdef extern from "modetracking.h":
    cdef cppclass ModeTracker[Type]:
        ModeTracker() except +

        void SetSeed(ModeSet[Type] seed) except +

        ModeSet[Type] GetSeed() except +

        void SetData(vector[ModeSet[Type]] seed) except +

        ModeSet[Type] GetData() except +

        ModeSet[Type] GetTrackedData() except +

        void Track() except +


# Mode Tracking (C++)
cdef extern from "modetracking.h":
    cdef vector[ModeSet[T]] TrackModes[T](ModeSet[T] &seed,\
        vector[ModeSet[T]] &data)  except +