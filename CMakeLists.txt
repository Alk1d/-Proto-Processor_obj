cmake_minimum_required(VERSION 3.14)

project(Proto_processor_OBJ LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_subdirectory(Exchange)

# add_library(${PROJECT_NAME} SHARED
#   $<TARGET_OBJECTS:Exchange>
# )

add_executable(${PROJECT_NAME}
  $<TARGET_OBJECTS:Exchange>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
)

add_custom_target(ProjectRelatedFiles SOURCES
    .astylerc
    .gitignore
    README.md
)
