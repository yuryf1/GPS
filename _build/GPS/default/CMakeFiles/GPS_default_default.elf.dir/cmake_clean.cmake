file(REMOVE_RECURSE
  "GPS_default_default.elf"
  "GPS_default_default.elf.manifest"
  "GPS_default_default.elf.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/GPS_default_default.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
