file(REMOVE_RECURSE
  "../channel_test"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/memory.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
