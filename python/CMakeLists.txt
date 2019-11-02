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


#-------------------------------------------------------------------------------
# Install setup for the Python Interface
#-------------------------------------------------------------------------------

# configure setup.py
configure_file(setup.py ../setup.py)


set(PYMTK_PATH "${CMAKE_SOURCE_DIR}/python")
set(PYTHON_INTERFACE
    ${PYMTK_PATH}/__init__.py
    ${PYMTK_PATH}/MTK.pxd
    ${PYMTK_PATH}/MTK.pyx
    ${PYMTK_PATH}/Core.pxd
    ${PYMTK_PATH}/Core.pyx
)

# set the Python interface file install location
set(PYTHON_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/MTK/MTK )

# install cython files
install(FILES ${PYTHON_INTERFACE} DESTINATION "${PYTHON_INSTALL_DIR}")

# install setup.py
install(FILES "${CMAKE_BINARY_DIR}/setup.py" DESTINATION
    "${CMAKE_INSTALL_PREFIX}/MTK/")


# set python auto install flag
set(PYTHON_AUTO_INSTALL FALSE CACHE BOOL
    "Automatically install python interface when install target is called")

# install python interface (using pip) if python auto install is set
if(PYTHON_AUTO_INSTALL)
    install(CODE "execute_process(COMMAND pip install . 
        WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/MTK/)")
endif(PYTHON_AUTO_INSTALL)