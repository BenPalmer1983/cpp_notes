 

# Header-only library
add_library(simplemd INTERFACE)
target_include_directories(simplemd
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib       
        ${CMAKE_SOURCE_DIR}/external/json     # NLohmann JSON
)

add_library(SimpleMD::simplemd ALIAS simplemd)

# App binary
add_executable(SimpleMD.x main.cpp)

# C++ standard 
target_compile_features(SimpleMD.x PRIVATE cxx_std_17)

# SYCL + targets + OpenMP flags (compile + link)
target_compile_options(SimpleMD.x PRIVATE
    -O3
    -fsycl
    -fsycl-targets=nvptx64-nvidia-cuda,spir64_x86_64
    -qopenmp
)

target_link_options(SimpleMD.x PRIVATE
    -O3
    -fsycl
    -fsycl-targets=nvptx64-nvidia-cuda,spir64_x86_64
    -qopenmp
)

target_link_libraries(SimpleMD.x PRIVATE SimpleMD::simplemd)
target_compile_features(SimpleMD.x PRIVATE cxx_std_20)




