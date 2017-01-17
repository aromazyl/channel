function(memorylib)
  add_definitions('-std=c++11')
  ADD_LIBRARY( memory STATIC
    /Users/aromazyl/code/channel/memory/blob.cc
    /Users/aromazyl/code/channel/memory/memory_pool.cc
    )
endfunction()
