project('Glad2', 'c')

glad2_sources = files(['src/gl.c'])
glad2_include = include_directories('include/')

lib = shared_library(meson.project_name(),
  glad2_sources,
  include_directories : [glad2_include],
  d_import_dirs : [glad2_include])

project_dep = declare_dependency(
  include_directories : [glad2_include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
