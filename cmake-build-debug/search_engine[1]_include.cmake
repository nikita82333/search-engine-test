if(EXISTS "C:/Users/kunv/CLionProjects/search_engine/cmake-build-debug/search_engine[1]_tests.cmake")
  include("C:/Users/kunv/CLionProjects/search_engine/cmake-build-debug/search_engine[1]_tests.cmake")
else()
  add_test(search_engine_NOT_BUILT search_engine_NOT_BUILT)
endif()
