project('Patata Engine',
  'cpp', 'c',
  default_options: ['buildtype=release', 'cpp_std=c++20'],
  version : '0')

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  version : '>=2.24.1',
  modules : ['SDL2::SDL2'])

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

# GLAD
Glad2 = declare_dependency(
  sources : 'externals/Glad2/src/gl.c',
  include_directories : 'externals/Glad2/include/',
  d_import_dirs : 'externals/Glad2/include/')

# Archivos (Source y Include)
include_main = include_directories('include')

source = files([
  'src/base/Core/main.cpp',
  'src/base/Core/sdl.cpp',
  'src/base/Window/window.cpp',
  'src/base/Window/window_icon.cpp',
  'src/base/Events/Main_events.cpp',
  'src/base/Core/API_Graphics_Switch.cpp',
  'src/base/Opengl/Opengl_context.cpp',
  'src/base/Vulkan/Setup_Vulkan.cpp'])

if target_machine.system() == 'windows'
  windows = import('windows')

  Patata_icon = windows.compile_resources('src/base/Core/patata.rc')

  executable('Patata Engine',
    source,
    Patata_icon,
    include_directories : [include_main],
    dependencies : [sdl2_dep, sdl2_image_dep, Vulkan, Glad2])
else
  executable('Patata Engine',
    source,
    include_directories : [include_main],
    dependencies : [sdl2_dep, sdl2_image_dep, Vulkan, Glad2])
endif
