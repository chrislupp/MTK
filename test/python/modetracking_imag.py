#===============================================================================
#
# MTK Modetracking (imaginary) tests
#
# Author: Christopher A. Lupp
#
#===============================================================================

import numpy
import h5py

from MTK import ModeSet, TrackModes


def LoadFlutterModes(fname):
    pass



# load modes from HDF5 file
untracked = LoadFlutterModes("bwb_flutter_eigensolution.h5")

# create a seed set
seed = ModeSet()

# track modes
tracked = TrackModes(seed, untracked)