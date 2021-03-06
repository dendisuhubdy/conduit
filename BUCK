def merge_dicts(x, y):
  z = x.copy()
  z.update(y)
  return z

headers = subdir_glob([
  ('include/conduit', '*.hpp'), 
  ('include/conduit', 'allocators/default.hpp'), 
])

mega_header = '\n'.join([
  '#ifndef CONDUIT_HPP',
  '#define CONDUIT_HPP',
  '',
] + [
  '#include <conduit/' + i + '> ' for i, _ in headers.items()
] + [
  '',
  '#endif',
  '',
])

genrule(
  name = 'mega-header', 
  out = 'conduit.hpp', 
  cmd = 'echo "' + mega_header + '" > $OUT', 
)

cxx_library(
  name = 'conduit',
  header_namespace =  'conduit',
  exported_headers = merge_dicts(subdir_glob([
    ('include/conduit', '**/*.hpp'), 
  ]), {
    'conduit.hpp': ':mega-header', 
  }), 
  licenses = [
    'LICENSE', 
  ], 
  visibility = [
    'PUBLIC', 
  ],
)

cxx_genrule(
  name = 'conduit-unity',
  srcs = glob(['include/**/*.hpp']),
  out = 'conduit-unity.hpp',
  cmd = '&&'.join([
    'cp -r $SRCDIR/. $TMP',
    'cd $TMP',
    'find -name \'*.hpp\' -exec sed -i \'/#include\s*<\s*conduit/! s/#include/##include/g\' {} +',
    '$(cxx) -E -P -Iinclude $(cppflags) -xc++ $(location :mega-header) > $OUT',
    'sed -i \'s/##include/#include/g\' $OUT',
  ])
)

genrule(
  name = 'bundle', 
  out = 'bundle.zip', 
  srcs = glob([
    'include/conduit/**/*.hpp', 
  ]), 
  cmd = ' && '.join([
    'cp -r $SRCDIR/. $TMP', 
    'cp $(location :mega-header) $TMP/include/conduit/conduit.hpp', 
    'cd $TMP', 
    'zip -r $OUT .', 
  ]), 
)
