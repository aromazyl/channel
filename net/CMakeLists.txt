function(netlib)
  cmake_minimum_required(VERSION 3.7)
  include(../memory/CMakeLists.txt)
  memorylib()
  add_definitions('-std=c++11')
  ADD_LIBRARY( net STATIC
    /Users/aromazyl/code/channel/net/zmq_network.cc
    /Users/aromazyl/code/channel/net/network.cc
    )
  link_libraries(zmq gtest glog gtest memory net)
endfunction()
