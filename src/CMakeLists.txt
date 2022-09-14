set(histogram_files
    hdr_encoding.c
    hdr_thread.c
    hdr_writer_reader_phaser.c
    hdr_histogram.c
    hdr_interval_recorder.c
    hdr_time.c)

set(HEADER
    hdr_atomic.h
    hdr_endian.h
    hdr_tests.h
    hdr_time.h
    hdr_encoding.h
    hdr_histogram.h
    hdr_interval_recorder.h
    hdr_thread.h
    hdr_writer_reader_phaser.h)

if (ENABLE_LOG_FEATURE)
   list(APPEND histogram_files hdr_histogram_log.c)
   list(APPEND HEADER hdr_histogram_log.h)
endif(ENABLE_LOG_FEATURE)

option(HDR_HISTOGRAM_BUILD_STATIC "Build static library" ON)
option(HDR_HISTOGRAM_BUILD_SHARED "Build shared library" ON)

if(HDR_HISTOGRAM_BUILD_SHARED)
  add_library(hdr_histogram SHARED ${histogram_files} ${HEADER})
  if(WIN32)
    set_target_properties(hdr_histogram PROPERTIES VERSION ${HDR_VERSION})
  else()
    target_link_libraries(hdr_histogram m)
    set_target_properties(hdr_histogram PROPERTIES VERSION ${HDR_VERSION} SOVERSION ${HDR_SOVERSION})
  endif()
  if (ENABLE_LOG_FEATURE)
     target_link_libraries(hdr_histogram ${ZLIB_LIBRARIES})
     target_include_directories(hdr_histogram SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${ZLIB_INCLUDE_DIRS})
  endif (ENABLE_LOG_FEATURE)
  install(TARGETS hdr_histogram DESTINATION lib${LIB_SUFFIX})
endif(HDR_HISTOGRAM_BUILD_SHARED)

if(HDR_HISTOGRAM_BUILD_STATIC)
  add_library(hdr_histogram_static STATIC ${histogram_files} ${HEADER})
  if(NOT WIN32)
    target_link_libraries(hdr_histogram_static m)
  endif()
  if (ENABLE_LOG_FEATURE)
     target_link_libraries(hdr_histogram_static ${ZLIB_LIBRARIES})
     target_include_directories(hdr_histogram_static SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${ZLIB_INCLUDE_DIRS})
  endif(ENABLE_LOG_FEATURE)
  install(TARGETS hdr_histogram_static DESTINATION lib${LIB_SUFFIX})
endif(HDR_HISTOGRAM_BUILD_STATIC)

install(FILES hdr_histogram.h hdr_time.h hdr_writer_reader_phaser.h hdr_interval_recorder.h hdr_thread.h DESTINATION include/hdr)
if (ENABLE_LOG_FEATURE)
    install(FILES hdr_histogram_log.h DESTINATION include/hdr)
endif (ENABLE_LOG_FEATURE)
