cmake_minimum_required(VERSION 3.0)

project(cairobasic VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DDEBUG)


set(SRC
    main.cpp
)

set(HDR
    cr_surfaces.h
    structs.h
)

set(ALL_SRC ${SRC} ${HDR})

list(SORT ALL_SRC)


if(WIN32)
    set(ARCH "mingw64")
elseif(APPLE)
    set(ARCH "mac64")
else()
    set(ARCH "lin64")
endif()

set(LIBACFUTILS "${CMAKE_SOURCE_DIR}/libacfutils")
find_library(LIBACFUTILS_LIBS acfutils "${LIBACFUTILS}/${ARCH}/lib")
find_library(LIBCAIRO_LIBS cairo "${LIBACFUTILS}/${ARCH}/lib")
find_library(LIBFREETYPE_LIBS freetype "${LIBACFUTILS}/${ARCH}/lib")

include_directories(cairobasic PUBLIC
    "XPLSDK303/CHeaders/XPLM"
    "XPLSDK303/CHeaders/Widgets"
    "XPLSDK303/CHeaders/Wrappers"
    "libacfutils/include"
    "libacfutils/lin64/include"
)

add_executable(cairobasic
                ${ALL_SRC})
                
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror -pedantic --std=c11 \
    -Wno-unused-local-typedefs -Wno-missing-field-initializers ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wformat-truncation=0 -Wformat-overflow=0" )

add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1)
if(WIN32)
	add_definitions(-DAPL=0 -DIBM=1 -DLIN=0)
elseif(APPLE)
	add_definitions(-DAPL=1 -DIBM=0 -DLIN=0)
else()
	add_definitions(-DAPL=0 -DIBM=0 -DLIN=1)
endif()


target_link_libraries(cairobasic PUBLIC
    ${LIBACFUTILS_LIBS}
	${LIBCAIRO_LIBS}
	${LIBFREETYPE_LIBS}
)

set_target_properties(cairobasic PROPERTIES
EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out" )