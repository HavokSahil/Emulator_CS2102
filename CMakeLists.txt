cmake_minimum_required(VERSION 3.10)

project(Emulator VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_BUILD_TYPE Debug)

find_package(Curses REQUIRED)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(
		-std=c89
		-pg
		-w
		#-pedantic
		-W
		-Wall
		-Wpointer-arith
		-Wwrite-strings
		-g
		-O0
	)

endif()

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

add_executable(emulator
	${SRC_DIR}/main.c
	${SRC_DIR}/devices.c
	${SRC_DIR}/datapath.c
	${SRC_DIR}/api.c
	${SRC_DIR}/ui.c
)

target_link_libraries(emulator PRIVATE ${CURSES_LIBRARIES})
target_include_directories(emulator PUBLIC ${INCLUDE_DIR} ${CURSES_INCLUDE_DIR})

enable_testing()

add_executable(test_devices ${TESTS_DIR}/test_devices.c ${SRC_DIR}/devices.c)
add_executable(test_datapath ${TESTS_DIR}/test_datapath.c ${SRC_DIR}/datapath.c ${SRC_DIR}/devices.c)
add_executable(test_api ${TESTS_DIR}/test_api.c ${SRC_DIR}/api.c ${SRC_DIR}/datapath.c ${SRC_DIR}/devices.c)

target_include_directories(test_devices PUBLIC ${INCLUDE_DIR})
target_include_directories(test_datapath PUBLIC ${INCLUDE_DIR})
target_include_directories(test_api PUBLIC ${INCLUDE_DIR})

add_test(NAME DevicesTest COMMAND test_devices)
add_test(NAME DatapathTest COMMAND test_datapath)
add_test(NAME ApiTest COMMAND test_api)


