# set source files for the library
set(SRC 
    src/datatypes.cpp
    src/modetracking.cpp
    src/modaltools.cpp
    )


# set header files for the library
set(HEADERS
    include/modaltools.h
    include/modetracking.h
    include/mtk_datatypes.h
    )


# create the library
add_library(mtk ${SRC} ${HEADERS})