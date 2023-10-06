project('Imgui', 'cpp')

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
  ['imgui/imgui.cpp',
    'imgui/imgui_draw.cpp',
    'imgui/imgui_demo.cpp',
    'imgui/imgui_tables.cpp',
    'imgui/imgui_widgets.cpp',
    'imgui/backends/imgui_impl_opengl3.cpp'])

Include = include_directories('imgui/')

meson.get_compiler('cpp').check_header('imgui.h',
  include_directories : Include,
  required : true)

meson.get_compiler('cpp').check_header('backends/imgui_impl_opengl3.h',
  include_directories : Include,
  required : true)

if Vulkan.found()
  meson.get_compiler('c').check_header('vulkan/vulkan.h', required : true)
  meson.get_compiler('cpp').check_header('backends/imgui_impl_vulkan.h',
    include_directories : Include,
    required : true)
  Sources += files(['imgui/backends/imgui_impl_vulkan.cpp'])
endif

if sdl2_dep.found()
  meson.get_compiler('cpp').check_header('backends/imgui_impl_sdl2.h',
    include_directories : Include,
    required : true)
  Sources += files(['imgui/backends/imgui_impl_sdl2.cpp'])
endif

lib = library(meson.project_name(),
  Sources,
  include_directories : [Include],
  d_import_dirs : [Include],
  dependencies : [dependencies])

project_dep = declare_dependency(
  include_directories : [Include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
