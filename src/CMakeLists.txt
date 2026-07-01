add_library(libsdb libsdb.cpp)
add_library(sdb::libsdb ALIAS libsdb)

set_target_properties(
	libsdb
	PROPERTIES OUTPUT_NAME sdb
)

target_compile_features(libsdb PUBLIC cxx_std_17)

target_include_directories(
	libsdb
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_SOURCE_DIR}/src/include
)
