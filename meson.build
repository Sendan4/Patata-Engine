project('Patata Engine',
  'cpp', 'c',
  default_options: [
    'buildtype=release',
    'cpp_std=c++20'],
  version : '0')
  
prefix = meson.source_root() + 'bin/'
bindir = meson.source_root() + 'bin/'

# SDL2
if meson.backend() == 'vs2022'
  sdl2_dep = dependency('sdl2',
    version : '>=2.24.1',
    static : false,
    modules : ['SDL2::SDL2', 'SDL2::SDL2main'],
    required : true)

  sdl2_image_dep = dependency('sdl2_image',
    static : false,
    modules : ['SDL2_image::SDL2_image'],
    required : true)
else
  sdl2_dep = dependency('sdl2',
    required : true,
    static : true,
    version : '>=2.24.1',
    modules : ['SDL2::SDL2', 'SDL2::SDL2-static'])

  sdl2_image_dep = dependency('sdl2_image',
    static : true,
    required : true)
endif

Vulkan = dependency('Vulkan',
  static : true,
  required : true)

# GLAD
glad_dep = declare_dependency(
  sources : 'externals/libs/glad/src/glad.c',
  include_directories : 'externals/libs/glad/include/',
  d_import_dirs : 'externals/libs/glad/include/')

# Archivos (Source y Include)
include_main = include_directories('include')

source = files([
  'src/base/Core/main.cpp',
  'src/base/Core/sdl.cpp',
  'src/base/Window/window.cpp',
  'src/base/Events/Main_events.cpp',
  'src/base/Core/API_Graphics_Switch.cpp',
  'src/base/Opengl/Opengl_context.cpp',
  'src/base/Vulkan/Setup_Vulkan.cpp'])

if target_machine.system() == 'windows'
  windows = import('windows')

  Patata_icon = windows.compile_resources('data/patata_icon.rc')

  executable('Patata Engine',
    source,
    Patata_icon,
    include_directories : [include_main],
    dependencies : [sdl2_dep, sdl2_image_dep, Vulkan, glad_dep])
else
  executable('Patata Engine',
    source,
    include_directories : [include_main],
    dependencies : [sdl2_dep, sdl2_image_dep, Vulkan, glad_dep])
endif