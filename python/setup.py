#===============================================================================
#
#     __  ___          __      __   ______            __   __ __ _ __
#    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_
#   / /|_/ / __ \/ __  / __ `/ /    / / / __ \/ __ \/ /  / ,<  / / __/
#  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /
# /_/  /_/\____/\__,_/\__,_/_/    /_/  \____/\____/_/  /_/ |_/_/\__/
#
# Modal Tool Kit
#
# Author: Christopher A. Lupp
#
# University of Michigan
# Active Aeroelasticity and Structures Research Lab
#
#===============================================================================


#===============================================================================
#
# UM/NAST Python Interface
#
# Setup Script
#
# Author: Christopher A. Lupp
#
# This file was adapted from the setup script for TACS (written by G. Kennedy)
#
#===============================================================================

import os
from subprocess import check_output
import sys
import eigency


# Numpy/mpi4py must be installed prior to installing UM/NAST
import numpy
import mpi4py

# Import distutils
from setuptools import setup
from distutils.core import Extension as Ext
from Cython.Build import cythonize



# Convert from local to absolute directories
#-------------------------------------------
def get_global_dir(files):
    root_dir = os.path.abspath(os.path.dirname(__file__))
    new = []
    for f in files:
        new.append(os.path.join(root_dir, f))
    return new



# get Eigen includes
#-------------------
def get_eigen_dir():
    # get the Eigen directory from the registered environment variable
    eigen_dir = os.environ['EIGEN3_ROOT']

    return eigen_dir


inc_dirs = []
lib_dirs = []
libs = []

# inc_dirs, lib_dirs, libs = get_mpi_flags()


# find the eigen root directory and add it to the include path
inc_dirs.append(get_eigen_dir())


# Add runtime directory
if sys.platform == 'win32':
    runtime_lib_dirs = []
else:
    runtime_lib_dirs = get_global_dir(['lib'])

# Relative paths for the include/library directories
rel_inc_dirs = ['include/']
rel_lib_dirs = ['lib']
libs.extend(['MTK'])




# Convert from relative to absolute directories
inc_dirs.extend(get_global_dir(rel_inc_dirs))
lib_dirs.extend(get_global_dir(rel_lib_dirs))


# Add the numpy/mpi4py directories
# inc_dirs.extend([numpy.get_include(), mpi4py.get_include()])


exts = []
exts.append(Ext('MTK', sources=['python/MTK.pyx'],
                    include_dirs=inc_dirs + eigency.get_includes(),
                    libraries=libs,
                    library_dirs=lib_dirs,
                    runtime_library_dirs=runtime_lib_dirs))

for e in exts:
    e.cython_directives = {"embedsignature": True,
                           "binding":True}
    
setup(name='pymtk',
      version='${MTK_VERSION_MAJOR}.${MTK_VERSION_MINOR}.${MTK_VERSION_PATCH}',
      description='Modal Tool Kit',
      author='Christopher A. Lupp',
      author_email='clupp@umich.edu',
      ext_modules=cythonize(exts, include_path=inc_dirs))
