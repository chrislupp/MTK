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


#-------------------------------------------------------------------------------
# Install setup for the Python Interface
#-------------------------------------------------------------------------------

# configure setup.py
configure_file(setup.py ../setup.py)


set(PYMTK_PATH "${CMAKE_SOURCE_DIR}/python")
set(PYTHON_INTERFACE
    ${PYMTK_PATH}/MTK.pxd
    ${PYMTK_PATH}/MTK.pyx
    ${PYMTK_PATH}/cppMTK.pxd
)

# set the Python interface file install location
set(PYTHON_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/MTK/python )

# install cython files
install(FILES ${PYTHON_INTERFACE} DESTINATION "${PYTHON_INSTALL_DIR}")

# install setup.py
install(FILES "${CMAKE_BINARY_DIR}/setup.py" DESTINATION
    "${CMAKE_INSTALL_PREFIX}/MTK/")