cmake_minimum_required (VERSION 3.9.1)
project (LUNA_COMPILER)

#Setting flex and bison
FIND_PACKAGE(BISON REQUIRED)

SET(BisonOutput ${CMAKE_BINARY_DIR}/parser.c)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutput}
            COMMAND ${BISON_EXECUTABLE}
                    --defines=${CMAKE_BINARY_DIR}/tokens.h
                    --output=${BisonOutput}
            ${CMAKE_SOURCE_DIR}/luna.y
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_BINARY_DIR}/scanner.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
                    --outfile=${FlexOutput}
            ${CMAKE_SOURCE_DIR}/luna.l
    )
ENDIF()


add_executable(lunac  ${BisonOutput} ${FlexOutput})
