 

# Header-only library
add_library(portscanner INTERFACE)
target_include_directories(portscanner
    INTERFACE   
        ${CMAKE_SOURCE_DIR}/external/json     # NLohmann JSON
)
target_link_libraries(portscanner
    INTERFACE
        OpenMP::OpenMP_CXX
)
add_library(PortScanner::portscanner ALIAS portscanner)

# App binary
add_executable(PortScanner.x main.cpp)
target_compile_options(PortScanner.x PRIVATE
    -O3
)
target_link_libraries(PortScanner.x PRIVATE PortScanner::portscanner)
target_compile_features(PortScanner.x PRIVATE cxx_std_23)




