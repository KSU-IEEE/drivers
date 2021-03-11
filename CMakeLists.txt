cmake_minimum_required(VERSION 3.0.0)
project(drivers)

# if arduino toolchain is pointed to, proceed
if ( "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "" )
    message(WARNING "arduino toolchain, not found. arduino-drivers not compiling")
else()
    # create lists for sources and the like
    set(SRCS 
    )
    if ( NOT ("${SRCS}" STREQUAL "") )
    set(LIBS)
    message(STATUS "${PROJECT_NAME} library compiling: ${SRCS}")
    add_library(drivers ${SRCS})
    target_link_libraries(drivers 
        PUBLIC
        ${LIBS})

    #############
    ## Install ##
    #############
    install(TARGETS drivers
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}
    )

    ## Mark cpp header files for installation
    install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${PROJECT_BINARY_DIR}
    FILES_MATCHING PATTERN "*.h"
    )

    # link to main arduino and enable it to be exported
    target_link_arduino_libraries(drivers PRIVATE core)
    target_enable_arduino_upload(drivers)
endif()
endif()