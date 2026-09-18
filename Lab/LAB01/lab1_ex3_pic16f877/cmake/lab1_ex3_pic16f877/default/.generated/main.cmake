include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(lab1_ex3_pic16f877_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_assemble)
add_library(lab1_ex3_pic16f877_default_default_XC8_assemble OBJECT ${lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_assemble})
    lab1_ex3_pic16f877_default_default_XC8_assemble_rule(lab1_ex3_pic16f877_default_default_XC8_assemble)
    list(APPEND lab1_ex3_pic16f877_default_library_list "$<TARGET_OBJECTS:lab1_ex3_pic16f877_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(lab1_ex3_pic16f877_default_default_XC8_assemblePreprocess OBJECT ${lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_assemblePreprocess})
    lab1_ex3_pic16f877_default_default_XC8_assemblePreprocess_rule(lab1_ex3_pic16f877_default_default_XC8_assemblePreprocess)
    list(APPEND lab1_ex3_pic16f877_default_library_list "$<TARGET_OBJECTS:lab1_ex3_pic16f877_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_compile)
add_library(lab1_ex3_pic16f877_default_default_XC8_compile OBJECT ${lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_compile})
    lab1_ex3_pic16f877_default_default_XC8_compile_rule(lab1_ex3_pic16f877_default_default_XC8_compile)
    list(APPEND lab1_ex3_pic16f877_default_library_list "$<TARGET_OBJECTS:lab1_ex3_pic16f877_default_default_XC8_compile>")

endif()

# Handle files with suffix elf, for group default-XC8
if(lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_objcopy_lss)
add_library(lab1_ex3_pic16f877_default_default_XC8_objcopy_lss OBJECT ${lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_objcopy_lss})
    lab1_ex3_pic16f877_default_default_XC8_objcopy_lss_rule(lab1_ex3_pic16f877_default_default_XC8_objcopy_lss)
    list(APPEND lab1_ex3_pic16f877_default_library_list "$<TARGET_OBJECTS:lab1_ex3_pic16f877_default_default_XC8_objcopy_lss>")

endif()


# Main target for this project
add_executable(lab1_ex3_pic16f877_default_image_eYpThIL_ ${lab1_ex3_pic16f877_default_library_list})

set_target_properties(lab1_ex3_pic16f877_default_image_eYpThIL_ PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${lab1_ex3_pic16f877_default_output_dir}")
target_link_libraries(lab1_ex3_pic16f877_default_image_eYpThIL_ PRIVATE ${lab1_ex3_pic16f877_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
lab1_ex3_pic16f877_default_link_rule( lab1_ex3_pic16f877_default_image_eYpThIL_)


#Add objcopy steps
lab1_ex3_pic16f877_default_objcopy_lss_rule(lab1_ex3_pic16f877_default_image_eYpThIL_)

