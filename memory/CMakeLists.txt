function(memorylib)
  add_definitions('-std=c++11')
  add_definitions('-g')
  ADD_LIBRARY( memory STATIC
    /home/scyl/code/channel/memory/blob.cc
    /home/scyl/code/channel/memory/memory_pool.cc
    )
endfunction()
