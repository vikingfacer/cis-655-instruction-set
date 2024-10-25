project(emulator VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

set_target_properties(${PROJECT_NAME}
    CXX_STANDARD 20
    LINKER_LANGUAGE CXX
)