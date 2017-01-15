file(REMOVE_RECURSE
  "../channel"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/channel.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
