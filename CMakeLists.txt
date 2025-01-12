cmake_minimum_required(VERSION 3.16)

project(SpaceLog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(SpaceLog source/main.cpp
    source/gameobject.cpp source/gameobject.h
    source/mapgenerator.h source/mapgenerator.cpp
    source/assetloader.h source/assetloader.cpp
)

target_link_libraries(SpaceLog PRIVATE SDL3::SDL3 SDL3_image)

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/ressource/)
file(COPY ./ressource DESTINATION ./)

include(GNUInstallDirs)
install(TARGETS SpaceLog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
