project(parser VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    parser.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    LINKER_LANGUAGE CXX
)
