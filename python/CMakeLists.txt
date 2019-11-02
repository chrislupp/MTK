#===============================================================================
#
# Modal Tool Kit (MTK)
#
# Author: Christopher A. Lupp
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