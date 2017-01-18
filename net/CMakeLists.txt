function(netlib)
  include_directories(../third_party/zmq/include/)
  include(${CMAKE_CURRENT_BINARY_DIR}/../../memory/CMakeLists.txt)
  memorylib()
  add_definitions('-std=c++11')
  ADD_LIBRARY( net STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/../../net/zmq_network.cc
    ${CMAKE_CURRENT_BINARY_DIR}/../../net/network.cc
    )
  link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../third_party/zmq/lib/)
  link_libraries(zmq gtest glog gtest memory net)
endfunction()
