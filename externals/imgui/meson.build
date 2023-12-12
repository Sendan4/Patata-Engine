project('imgui', 'cpp',
  version : '1.90',
  meson_version : '>=1.2.0')

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  version : '>=2.24.1',
  modules : ['SDL2::SDL2'])

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

dependencies = [Vulkan, sdl2_dep]

meson.get_compiler('c').check_header('stdio.h', required : true)
meson.get_compiler('c').check_header('stdint.h', required : true)
meson.get_compiler('c').check_header('float.h', required : true)
meson.get_compiler('c').check_header('stdarg.h', required : true)
meson.get_compiler('c').check_header('stddef.h', required : true)
meson.get_compiler('c').check_header('string.h', required : true)
meson.get_compiler('c').check_header('assert.h', required : false)
meson.get_compiler('c').check_header('stdlib.h', required : true)
meson.get_compiler('c').check_header('limits.h', required : true)
meson.get_compiler('c').check_header('math.h', required : true)

if target_machine.system() == 'windows'
  meson.get_compiler('c').check_header('Windows.h', required : true)
endif

Sources = files(
  ['imgui.cpp',
    'imgui_draw.cpp',
    'imgui_demo.cpp',
    'imgui_tables.cpp',
    'imgui_widgets.cpp',
    'backends/imgui_impl_opengl3.cpp'])

Include = include_directories('.')

backends = include_directories('backends/')

if Vulkan.found()
  meson.get_compiler('c').check_header('vulkan/vulkan.h', required : true)
  Sources += files(['backends/imgui_impl_vulkan.cpp'])
endif

if sdl2_dep.found()
  Sources += files(['backends/imgui_impl_sdl2.cpp'])
endif

lib = library(meson.project_name(),
  Sources,
  include_directories : [Include, backends],
  d_import_dirs : [Include, backends],
  dependencies : [dependencies],
  install : true,
  install_dir : join_paths(meson.global_build_root(),'../bin'))

project_dep = declare_dependency(
  include_directories : [Include, backends],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
