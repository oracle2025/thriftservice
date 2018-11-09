cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/gen-cpp/MultiplicationService.cpp   
	COMMAND ${PROJECT_BINARY_DIR}/bin/thrift --gen cpp ${PROJECT_SOURCE_DIR}/src/multiplication.thrift
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR})


add_executable(main src/main.cpp
	${PROJECT_BINARY_DIR}/gen-cpp/MultiplicationService.cpp   
	${PROJECT_BINARY_DIR}/gen-cpp/multiplication_constants.cpp
	${PROJECT_BINARY_DIR}/gen-cpp/multiplication_types.h
	${PROJECT_BINARY_DIR}/gen-cpp/MultiplicationService.h
	${PROJECT_BINARY_DIR}/gen-cpp/multiplication_constants.h
	#${PROJECT_BINARY_DIR}/gen-cpp/MultiplicationService_server.skeleton.cpp
	${PROJECT_BINARY_DIR}/gen-cpp/multiplication_types.cpp
	)
target_include_directories(main PRIVATE
	${PROJECT_BINARY_DIR}/include
	${PROJECT_BINARY_DIR}/gen-cpp)
target_link_libraries(main ${PROJECT_BINARY_DIR}/lib/libthrift.a)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/thrift)
execute_process(COMMAND ${CMAKE_COMMAND}
	-G ${CMAKE_GENERATOR}
	-DCMAKE_CXX_STANDARD=14
	-DWITH_JAVA=OFF
	-DWITH_PYTHON=OFF
	-DWITH_HASKELL=OFF
	-DWITH_SHARED_LIB=OFF
	-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}
	-DWITH_BOOST_STATIC=ON
	-DWITH_STDTHREADS=ON
	-DWITH_QT4=OFF
	-DWITH_QT5=OFF
	-DWITH_LIBEVENT=OFF
	-DWITH_ZLIB=OFF
	-DBUILD_TESTING=OFF
	-DBUILD_EXAMPLES=OFF
	-DBUILD_TUTORIALS=OFF
	-DWITH_C_GLIB=OFF
	${PROJECT_SOURCE_DIR}/thrift
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/thrift)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/thrift)
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/thrift)

