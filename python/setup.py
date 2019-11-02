#===============================================================================
#
#     Modal Tool Kit (MTK)
#
#     Copyright 2017 Christopher A. Lupp
#
#     Licensed under the Apache License, Version 2.0 (the "License");
#     you may not use this file except in compliance with the License.
#     You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#     Unless required by applicable law or agreed to in writing, software
#     distributed under the License is distributed on an "AS IS" BASIS,
#     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#     See the License for the specific language governing permissions and
#     limitations under the License.
#
#===============================================================================

import os
from subprocess import check_output
import sys
import eigency
import numpy

from setuptools import setup, find_packages
from setuptools.extension import Extension
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


# Convert from relative to absolute directories
inc_dirs.extend(get_global_dir(rel_inc_dirs))
lib_dirs.extend(get_global_dir(rel_lib_dirs))


exts = [Extension('MTK.MTK', sources=['MTK/MTK.pyx'],
            include_dirs=inc_dirs + eigency.get_includes(),
            libraries=libs,
            library_dirs=lib_dirs,
            runtime_library_dirs=runtime_lib_dirs)
    ]

for e in exts:
    e.cython_directives = {"embedsignature": True,
                           "binding":True}
    
setup(name='pymtk',
    version='${MTK_VERSION_MAJOR}.${MTK_VERSION_MINOR}.${MTK_VERSION_PATCH}',
    description='Modal Tool Kit',
    author='Christopher A. Lupp',
    author_email='clupp@umich.edu',
    include_package_data=True,
    packages = find_packages(),
    package_data = {"MTK": ['*.pxd']},
    ext_modules=cythonize(exts),
    install_requires = ['numpy','h5py','eigency','sphinx']
    )