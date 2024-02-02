project('example', 'cpp',
    default_options : ['buildtype=release'])

if get_option('use_external_libs') == true and build_machine.system() != 'windows'
  cmake = import('cmake')

  buildtypeforcmake = ''
  if get_option('buildtype') == 'debug'
    buildtypeforcmake = 'Debug'
  elif get_option('buildtype') == 'debugoptimized'
    buildtypeforcmake = 'RelWithDebInfo'
  elif get_option('buildtype') == 'release'
    buildtypeforcmake = 'Release'
  elif get_option('buildtype') == 'minsize'
    buildtypeforcmake = 'MinSizeRel'
  endif

  sdl2_opt = cmake.subproject_options()
  sdl2_opt.add_cmake_defines(
    { 'CMAKE_INSTALL_PREFIX' : join_paths(meson.global_build_root(), '../bin/') },
    { 'CMAKE_INSTALL_LIBDIR' : '.' },
    { 'CMAKE_BUILD_TYPE' : buildtypeforcmake },
    { 'SDL_TEST' : false },
    { 'SDL_OPENGLES' : false },
    { 'SDL_SHARED' : true },
    { 'SDL_STATIC' : false },
    { 'SDL_FILE' : false },
    { 'SDL_LOCALE' : false },
    { 'SDL_POWER' : false },
    { 'SDL_RENDER' : false},
    { 'SDL_SENSOR' : false },
    { 'SDL_TIMERS' : false},
    { 'SDL_ATOMIC' : false })

  if get_option('xorg_support') == false
    sdl2_opt.add_cmake_defines(
      { 'SDL_X11' : false }, 
      { 'SDL_X11_SHARED' : false })
  endif

  sdl2 = cmake.subproject('SDL', options : sdl2_opt)
  sdl2_dep = sdl2.dependency('SDL2')
else
  sdl2_dep = dependency('sdl2',
    required : true)
endif

Patata_Engine_dep = subproject('patata-engine').get_variable('Patata_Engine_dep')
dependencies = [sdl2_dep, Patata_Engine_dep]

if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
  add_project_arguments('-DDEBUG=1', language : 'cpp')
endif

executable(meson.project_name(),
  'Main.cpp',
  dependencies : dependencies,
  build_by_default : true,
  install : true,
  install_dir : join_paths(meson.global_build_root(), '../bin'),
  install_rpath : '.')
