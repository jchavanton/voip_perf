cmake_minimum_required(VERSION 3.2)
project(voip_perf VERSION 1.0.0 LANGUAGES C)

set(CMAKE_VERBOSE_MAKEFILE ON)

message("CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR} CMAKE_SYSTEM:${CMAKE_SYSTEM}  CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE} OV:${OV}")

set(ROOT_DIR ".")
set(SRC_DIR "${ROOT_DIR}/src")

set(PERF_SRCS
	${SRC_DIR}/voip_perf.c
)

include_directories(${ROOT_DIR}/pjproject/pjmedia/include)
include_directories(${ROOT_DIR}/pjproject/pjsip/include)
include_directories(${ROOT_DIR}/pjproject/pjlib/include)
include_directories(${ROOT_DIR}/pjproject/pjnath/include)
include_directories(${ROOT_DIR}/pjproject/pjlib-util/include)

include_directories(${ROOT_DIR}/include)

set(SOURCE_FILES ${PERF_SRCS})

add_executable(voip_perf ${SOURCE_FILES})

set(CMAKE_LIBRARY_PATH
	"${ROOT_DIR}/pjproject/pjsip/lib"
	"${ROOT_DIR}/pjproject/pjnath/lib"
	"${ROOT_DIR}/pjproject/pjlib/lib"
	"${ROOT_DIR}/pjproject/media/lib"
	"${ROOT_DIR}/pjproject/pjlib-util/lib"
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

execute_process(COMMAND "./pjproject/config.guess" OUTPUT_VARIABLE AC_SYSTEM)
string(STRIP ${AC_SYSTEM} AC_SYSTEM)

target_link_libraries(voip_perf
	pjsua-${AC_SYSTEM}
	pjsip-ua-${AC_SYSTEM}
	pjsip-simple-${AC_SYSTEM}
	pjsip-${AC_SYSTEM}
	pjmedia-codec-${AC_SYSTEM}
	pjmedia-${AC_SYSTEM}
	pjmedia-videodev-${AC_SYSTEM}
	pjmedia-audiodev-${AC_SYSTEM}
	pjmedia-${AC_SYSTEM}
	pjnath-${AC_SYSTEM}
	pjlib-util-${AC_SYSTEM}
	srtp-${AC_SYSTEM}
	resample-${AC_SYSTEM}
	gsmcodec-${AC_SYSTEM}
	speex-${AC_SYSTEM}
	ilbccodec-${AC_SYSTEM}
	g7221codec-${AC_SYSTEM}
	pj-${AC_SYSTEM}
	pthread
	m
	asound
)

find_package(PkgConfig REQUIRED)

pkg_search_module(UUID uuid)
if( UUID_FOUND )
	message("uuid found")
	target_link_libraries(voip_perf uuid)
else()
	message("uuid not found")
endif()

pkg_search_module(OPENSSL openssl)
if( OPENSSL_FOUND )
	message("openssl found")
	target_link_libraries(voip_perf ssl crypto)
else()
	message("openssl not found")
endif()

pkg_search_module(JANSON jansson)
if( JANSON_FOUND )
	message("jansson found")
	target_link_libraries(voip_perf jansson)
else()
	message("janson not found")
endif()

pkg_search_module(OPUS opus)
if( OPUS_FOUND )
	message("opus found")
	target_link_libraries(voip_perf opus)
else()
	message("opus not found")
endif()
