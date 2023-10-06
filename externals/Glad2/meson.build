project('Glad2', 'c')

glad2_sources = files(['src/gl.c'])
glad2_include = include_directories('include/')

meson.get_compiler('c').check_header('glad/gl.h', include_directories : glad2_include, required : true)
meson.get_compiler('c').check_header('KHR/khrplatform.h', include_directories : glad2_include, required : true)
meson.get_compiler('c').check_header('stdint.h', required : true)
meson.get_compiler('c').check_header('inttypes.h', required : true)

lib = shared_library(meson.project_name(),
  glad2_sources,
  include_directories : [glad2_include],
  d_import_dirs : [glad2_include])

project_dep = declare_dependency(
  include_directories : [glad2_include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
