function(io)
  add_definitions('-std=c++11')
  add_definitions('-g')
  ADD_LIBRARY(io STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/../../io/fast_io.cc
    )
  link_libraries(gtest glog gtest)
endfunction()
