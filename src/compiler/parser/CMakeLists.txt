cmake_minimum_required (VERSION 3.5)
project (LUNA_COMPILER)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Setting flex and bison
FIND_PACKAGE(BISON REQUIRED)

SET(BisonOutput ${CMAKE_BINARY_DIR}/parser.c)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutput}
            COMMAND ${BISON_EXECUTABLE}
                    --defines=${CMAKE_BINARY_DIR}/tokens.h
                    --output=${BisonOutput}
            ${CMAKE_CURRENT_LIST_DIR}/luna.y
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_BINARY_DIR}/scanner.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
                    --outfile=${FlexOutput}
            ${CMAKE_CURRENT_LIST_DIR}/luna.l
    )
ENDIF()

add_executable(lunac ${BisonOutput} ${FlexOutput})

target_link_libraries(lunac
        liblunac
)

install(TARGETS lunac DESTINATION bin)
