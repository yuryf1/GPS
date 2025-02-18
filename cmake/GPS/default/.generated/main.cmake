include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")
set(GPS_default_library_list )
# Handle files with suffix s 
if(GPS_default_FILE_GROUP_assemble)
    add_library(GPS_default_assemble OBJECT ${GPS_default_FILE_GROUP_assemble})
    GPS_default_assemble_rule(GPS_default_assemble)
    list(APPEND GPS_default_library_list "$<TARGET_OBJECTS:GPS_default_assemble>")
endif()

# Handle files with suffix S 
if(GPS_default_FILE_GROUP_assemblePreproc)
    add_library(GPS_default_assemblePreproc OBJECT ${GPS_default_FILE_GROUP_assemblePreproc})
    GPS_default_assemblePreproc_rule(GPS_default_assemblePreproc)
    list(APPEND GPS_default_library_list "$<TARGET_OBJECTS:GPS_default_assemblePreproc>")
endif()

# Handle files with suffix c 
if(GPS_default_FILE_GROUP_compile)
    add_library(GPS_default_compile OBJECT ${GPS_default_FILE_GROUP_compile})
    GPS_default_compile_rule(GPS_default_compile)
    list(APPEND GPS_default_library_list "$<TARGET_OBJECTS:GPS_default_compile>")
endif()

if (BUILD_LIBRARY)
        message(STATUS "Building LIBRARY")
        add_library(${GPS_default_image_name} ${GPS_default_library_list})
        foreach(lib ${GPS_default_FILE_GROUP_link})
        target_link_libraries(${GPS_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR} /${lib})
        endforeach()
        add_custom_command(
            TARGET ${GPS_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GPS_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy lib${GPS_default_image_name}.a ${GPS_default_output_dir}/${GPS_default_original_image_name})
else()
    message(STATUS "Building STANDARD")
    add_executable(${GPS_default_image_name} ${GPS_default_library_list})
    foreach(lib ${GPS_default_FILE_GROUP_link})
    target_link_libraries(${GPS_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${lib})
endforeach()
    GPS_default_link_rule(${GPS_default_image_name})
        add_custom_target(
        GPS_default_Bin2Hex
        ALL
        ${MP_BIN2HEX} ${GPS_default_image_name}
    )
    add_dependencies(GPS_default_Bin2Hex ${GPS_default_image_name})

add_custom_command(
    TARGET ${GPS_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GPS_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${GPS_default_image_name} ${GPS_default_output_dir}/${GPS_default_original_image_name})
endif()
