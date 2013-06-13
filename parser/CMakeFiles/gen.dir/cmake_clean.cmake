FILE(REMOVE_RECURSE
  "parser.tab.h"
  "parser.tab.cc"
  "parser.yy.cc"
  "CMakeFiles/gen"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/gen.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
