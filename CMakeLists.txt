cmake_minimum_required(VERSION 3.23)
project(Flightsearcher)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
IF (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    include("/Users/luca-miguel/.vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(Flightsearcher MACOSX_BUNDLE main.cpp Flights.cpp Airports.cpp Airlines.cpp ${app_icon_macos})
ENDIF ()

IF(WINDOWS)
    include("H:/Programmieren/vcpkg/scripts/buildsystems/vcpkg.cmake")
    add_executable(Flightsearcher MACOSX_BUNDLE main.cpp Flights.cpp Airports.cpp Airlines.cpp)
ENDIF()

find_package(cpr CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Qt6Widgets CONFIG REQUIRED)
find_package(Qt6Core CONFIG REQUIRED)
find_package(Qt6Gui CONFIG REQUIRED)



target_link_libraries(Flightsearcher cpr::cpr fmt::fmt-header-only nlohmann_json::nlohmann_json Qt6::Widgets Qt6::Core Qt6::Gui)