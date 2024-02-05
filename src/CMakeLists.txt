# src/CMakeLists.txt

# Add the 'src' directory
add_library(ConsoleDrawingAppLib
    drawing.cpp
)

# Add the 'include' directory to the include directories
target_include_directories(ConsoleDrawingAppLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Create the main executable
add_executable(ConsoleDrawingApp
    main.cpp
)

# Link the main executable with the library
target_link_libraries(ConsoleDrawingApp
    PRIVATE ConsoleDrawingAppLib
)
