set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
cmake_minimum_required(VERSION 3.20)

# 工具链设置
# set(TOOLPATH  "D:/App_Windows/MounRiver_Studio/Base_File/MounRiver_Studio/toolchain/RISC-V Embedded GCC/bin/riscv-none-embed-")
set(TOOLPATH "D:/App_Windows/MounRiver_Studio/Base_File/MounRiver_Studio/toolchain/RISC-V Embedded GCC12/bin/riscv-none-elf-")
#RT-Thread
#set(TOOLPATH "D:/RT-ThreadStudio/repo/Extract/ToolChain_Support_Packages/WCH/RISC-V-GCC-WCH/8.2.0/bin/riscv-none-embed-")

if(WIN32)
    MESSAGE(STATUS "Now is windows!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++.exe)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_AR ${TOOLPATH}ar.exe)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy.exe)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump.exe)
    set(SIZE ${TOOLPATH}size.exe)
elseif(UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_AR ${TOOLPATH}ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump)
    set(SIZE ${TOOLPATH}size)
else()
    MESSAGE(STATUS "Unsupported system!")
endif()

# 项目设置
project(CH32V307VCT6_RT_Thread_CMake C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(m)

# 编译参数 一般不用改
add_compile_options(-march=rv32imafc -mabi=ilp32f -mcmodel=medany -msmall-data-limit=8 -mno-save-restore)
add_compile_options(-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant)

message("CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})
message("RT-Thread Version:4.0.4")

# 编译等级
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-O3)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-O2 -g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif()

# 编译信息等级
add_compile_options(-Wall)

# 头文件路径
include_directories(
    App/RTThread_Run/Inc
    App
    CMyLib/Inc
    CMyLib
    MyDrivers/FLASH/Inc
    MyDrivers/FLASH
    MyDrivers/KEY
    MyDrivers/LED
    MyDrivers/USB/Inc
    MyDrivers/USB
    MyDrivers
    Libraries/Hal_Drivers/Inc
    Libraries/Hal_Libraries/BMsis/Inc
    Libraries/Hal_Libraries/CH32V307_Hal/Inc
    rt-thread/components/dfs/filesystems/devfs
    rt-thread/components/dfs/filesystems/elmfat
    rt-thread/components/dfs/include
    rt-thread/components/drivers/include/drivers
    rt-thread/components/drivers/include/ipc
    rt-thread/components/drivers/include
    rt-thread/components/drivers/spi/sfud/inc
    rt-thread/components/drivers/spi
    rt-thread/components/drivers/usb/usbdevice/class
    rt-thread/components/finsh
    rt-thread/components/libc/compilers/common
    rt-thread/components/libc/compilers/newlib
    rt-thread/include/libc
    rt-thread/include
    rt-thread/libcpu/risc-v/common
    rt-thread
    User/Inc
)

# 源码文件
file(GLOB_RECURSE SOURCES
    "App/*.c"
    "CMyLib/Src/*.c"
    "MyDrivers/*.c"
    "Libraries/*.c"
    "Libraries/*.s"
    "rt-thread/*.s"
    "rt-thread/*.c"
    # "User/*.cpp"
    "User/*.c"
)

# 链接参数
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Ld/Link.ld)
add_link_options(
    -march=rv32imafc -mabi=ilp32f
    -nostartfiles
    -Xlinker --gc-sections
    -Wl,--print-memory-usage
    -Wl,-Map,${PROJECT_NAME}.map
    --specs=nano.specs
    --specs=nosys.specs)
add_link_options(-T ${LINKER_SCRIPT})

# 编译可执行文件
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

# 链接静态库
# target_link_libraries(${PROJECT_NAME}.elf printfloat)

# 输出hex和bin
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(LST_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lst)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMAND ${CMAKE_OBJDUMP} --all-headers --demangle --disassemble $<TARGET_FILE:${PROJECT_NAME}.elf> > ${LST_FILE}
    COMMAND ${SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}.elf>
)
