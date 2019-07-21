#===============================================================================
#
# MTK Modetracking (real) tests
#
# Author: Christopher A. Lupp
#
#===============================================================================

import numpy
import h5py

from MTK import ModeSet, TrackModes


def LoadModes(fname_base, i):
    pass



# load modes from HDF5 file
untracked = LoadModes("modal_results_", 11)

# create a seed set


# track modes
tracked = TrackModes(seed, untracked)