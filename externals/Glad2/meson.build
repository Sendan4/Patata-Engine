project('Glad2', 'c', version : '2.0.4')

glad2_sources = files(['src/gl.c'])
glad2_include = include_directories('include/')

meson.get_compiler('c').check_header('stdint.h', required : true)
meson.get_compiler('c').check_header('inttypes.h', required : true)

librarytype = '' 

if get_option('libs_shared_build') == true
  lib = shared_library(meson.project_name(),
    glad2_sources,
    include_directories : [glad2_include],
    d_import_dirs : [glad2_include],
    install : true,
    soversion : meson.project_version(),
    install_dir : join_paths(meson.build_root(),'../bin'))

  librarytype = 'Shared'
else
  lib = static_library(meson.project_name(),
    glad2_sources,
    include_directories : [glad2_include],
    d_import_dirs : [glad2_include],
    install : true,
    install_dir : join_paths(meson.build_root(),'../bin'))

  librarytype = 'Static'
endif

project_dep = declare_dependency(
  include_directories : [glad2_include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)

Info = {
  'APIs' : 'OpenGL',
  'OpenGL Version' : '4.6',
  'Extensions' : false,
  'Multiple GL contexts' : false,
  'Header Only' : false,
  'Build Type' : get_option('buildtype'),
  'Library Type' : librarytype
}

summary({
  'APIs' : Info['APIs'],
  'OpenGL Version' : Info['OpenGL Version'],
  'Extensions' : Info['Extensions'],
  'Multiple GL contexts' : Info['Multiple GL contexts'],
  'Header Only' : Info['Header Only']},
  bool_yn : true)

summary({
  'Build Type' : Info['Build Type'],
  'Library Type' : Info['Library Type']},
  bool_yn : true,
  section : 'Library')
