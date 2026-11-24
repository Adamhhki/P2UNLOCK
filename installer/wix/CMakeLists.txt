if(NOT WIN32)
    return()
endif()

find_program(DOTNET_EXECUTABLE dotnet REQUIRED)

add_custom_target(PSeriesNativeMSI
    COMMAND "${DOTNET_EXECUTABLE}" build
            "${CMAKE_CURRENT_SOURCE_DIR}/PSeriesNative.wixproj"
            "-p:PSeriesServiceExe=$<TARGET_FILE:PSeriesService>"
            "-p:Platform=x64"
            "-p:Configuration=Release"
            "-p:OutputPath=${CMAKE_BINARY_DIR}/installer/wix/"
    DEPENDS PSeriesService
    COMMENT "Building PSeries Native WiX MSI"
)
