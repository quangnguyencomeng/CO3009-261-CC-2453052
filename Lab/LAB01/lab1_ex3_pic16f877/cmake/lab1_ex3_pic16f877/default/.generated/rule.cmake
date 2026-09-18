# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/Acer/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(lab1_ex3_pic16f877_default_default_XC8_assemble_rule target)
    set(options
        "-c"
        "${MP_EXTRA_AS_PRE}"
        "-mcpu=16F877"
        "${DEBUGGER_NAME}"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC16Fxxx_DFP/1.9.176/xc8"
        "-fno-short-double"
        "-fno-short-float"
        "-O0"
        "-maddrqual=ignore"
        "-mwarn=-3"
        "-msummary=-psect,-class,+mem,-hex,-file"
        "-ginhx32"
        "-Wl,--data-init"
        "-mno-keep-startup"
        "-mno-osccal"
        "-mno-resetbits"
        "-mno-save-resetbits"
        "-mno-download"
        "-mno-stackcall"
        "-mno-default-config-bits"
        "-std=c99"
        "-gdwarf-3"
        "-mstack=compiled:auto:auto")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__16F877__"
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
endfunction()
function(lab1_ex3_pic16f877_default_default_XC8_assemblePreprocess_rule target)
    set(options
        "-c"
        "${MP_EXTRA_AS_PRE}"
        "-mcpu=16F877"
        "-x"
        "assembler-with-cpp"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC16Fxxx_DFP/1.9.176/xc8"
        "-fno-short-double"
        "-fno-short-float"
        "-O0"
        "-maddrqual=ignore"
        "-mwarn=-3"
        "-msummary=-psect,-class,+mem,-hex,-file"
        "-ginhx32"
        "-Wl,--data-init"
        "-mno-keep-startup"
        "-mno-osccal"
        "-mno-resetbits"
        "-mno-save-resetbits"
        "-mno-download"
        "-mno-stackcall"
        "-mno-default-config-bits"
        "-std=c99"
        "-gdwarf-3"
        "-mstack=compiled:auto:auto")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__16F877__"
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
endfunction()
function(lab1_ex3_pic16f877_default_default_XC8_compile_rule target)
    set(options
        "-c"
        "${MP_EXTRA_CC_PRE}"
        "-mcpu=16F877"
        "${DEBUGGER_NAME}"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC16Fxxx_DFP/1.9.176/xc8"
        "-fno-short-double"
        "-fno-short-float"
        "-O0"
        "-maddrqual=ignore"
        "-mwarn=-3"
        "-msummary=-psect,-class,+mem,-hex,-file"
        "-ginhx32"
        "-Wl,--data-init"
        "-mno-keep-startup"
        "-mno-osccal"
        "-mno-resetbits"
        "-mno-save-resetbits"
        "-mno-download"
        "-mno-stackcall"
        "-mno-default-config-bits"
        "-std=c99"
        "-gdwarf-3"
        "-mstack=compiled:auto:auto")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__16F877__"
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
endfunction()
function(lab1_ex3_pic16f877_default_link_rule target)
    set(options
        "-Wl,-Map=mem.map"
        "${MP_EXTRA_LD_PRE}"
        "-mcpu=16F877"
        "${DEBUGGER_NAME}"
        "-Wl,--defsym=__MPLAB_BUILD=1"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC16Fxxx_DFP/1.9.176/xc8"
        "-fno-short-double"
        "-fno-short-float"
        "-O0"
        "-maddrqual=ignore"
        "-mwarn=-3"
        "-msummary=-psect,-class,+mem,-hex,-file"
        "-ginhx32"
        "-Wl,--data-init"
        "-mno-keep-startup"
        "-mno-osccal"
        "-mno-resetbits"
        "-mno-save-resetbits"
        "-mno-download"
        "-mno-stackcall"
        "-mno-default-config-bits"
        "-std=c99"
        "-gdwarf-3"
        "-mstack=compiled:auto:auto"
        "-Wl,--memorysummary,memoryfile.xml")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__DEBUG=1"
        PRIVATE "XPRJ_default=default")
endfunction()
function(lab1_ex3_pic16f877_default_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers --source ${lab1_ex3_pic16f877_default_image_name} > ${lab1_ex3_pic16f877_default_image_base_name}.lss
        WORKING_DIRECTORY ${lab1_ex3_pic16f877_default_output_dir})
endfunction()
