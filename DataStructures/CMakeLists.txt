cmake_minimum_required(VERSION 2.8)
project(DataStructure)

set(CMAKE_C_FLAGS "-Wall -g -lm")

include_directories(.)

# Subparts delcaration
add_subdirectory(hello)
add_subdirectory("singly-linked-list")

# Run tests
set(RESULT_FILE test.results)

add_custom_command(
    OUTPUT ${RESULT_FILE}

    COMMAND rm -rf ${RESULT_FILE}

    # TODO make this shorter...
    COMMAND echo "Running hello..." >> ${RESULT_FILE}
    COMMAND hello/hello_test >> ${RESULT_FILE}
    COMMAND echo -e >> ${RESULT_FILE}
    COMMAND echo "hello finished..." >> ${RESULT_FILE}

    COMMAND echo "Running singly linked list..." >> ${RESULT_FILE}
    COMMAND "singly-linked-list/singly-linked-list_test" >> ${RESULT_FILE}
    COMMAND echo -e >> ${RESULT_FILE}
    COMMAND echo "singly linked list finished..." >> ${RESULT_FILE}

    DEPENDS hello/hello_test
    DEPENDS "singly-linked-list/singly-linked-list_test"
)

add_custom_target(
    test ALL
    DEPENDS ${RESULT_FILE}
    DEPENDS hello/hello_test
    DEPENDS "singly-linked-list/singly-linked-list_test"
)
