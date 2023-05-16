project('Patata Engine',
  'cpp', 'c',
  default_options: [
    'buildtype=release'])

#current_date = meson.current_date()
#message('La fecha actual es', current_date)

if meson.get_compiler('cpp').get_id() == 'gcc' or meson.get_compiler('cpp').get_id() == 'clang'
  if (meson.get_compiler('cpp').has_argument('-Wall') and meson.get_compiler('cpp').has_argument('-Wextra'))
    warning_level = 3
  elif meson.get_compiler('cpp').has_argument('-Wall') and not meson.get_compiler('cpp').has_argument('-Wextra')
    warning_level = 3
  endif
endif

if (meson.get_compiler('cpp').has_argument('-std=c++20'))
  cpp_std = 'c++20'
endif

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
    static : false,
    version : '>=2.24.1',
    modules : ['SDL2::SDL2', 'SDL2::SDL2-static'])

  sdl2_image_dep = dependency('sdl2_image',
    static : true,
    required : true)
endif

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

# GLAD
glad = shared_library('glad',
	sources : 'externals/libs/glad/src/glad.c',
	include_directories : 'externals/libs/glad/include/')

glad_dep = declare_dependency(
  include_directories : 'externals/libs/glad/include/',
  link_with : glad)

# Archivos (Source y Include)
include_main = include_directories('include')

source = files([
  'src/base/Core/main.cpp',
  'src/base/Core/sdl.cpp',
  'src/base/Window/window.cpp',
  'src/base/Events/Main_events.cpp',
  'src/base/Core/API_Graphics_Switch.cpp',
  'src/base/Opengl/Opengl_context.cpp',
  'src/base/Vulkan/Setup_Vulkan.cpp',
  'src/base/Vulkan/Vulkan_info.cpp'])

features = {
    'Vulkan' : Vulkan.found(),
    'OpenGL' : glad_dep.found(),
    'SDL2' : sdl2_dep.found(),
    'SDL2-image' : sdl2_image_dep.found()
}

summary({'OpenGL': features['OpenGL'],
         'Vulkan': features['Vulkan'],
          'SDL2' : features['SDL2'],
          'SDL2-Image': features['SDL2-image']},
         bool_yn : true)

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
