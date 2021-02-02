cmake_minimum_required(VERSION 3.5)
set(SUBPROJECT_NAME Sorter)
# create library
add_library(${PROJECT_NAME}_${SUBPROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Sorter.cpp)


# add include directories
target_include_directories(${PROJECT_NAME}_${SUBPROJECT_NAME}
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
)