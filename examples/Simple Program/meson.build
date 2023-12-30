project('Game', 'cpp',
    default_options : ['buildtype=release'])

if get_option('use_external_libs') == true
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
    { 'SDL_DIRECTX' : false },
    { 'SDL_RENDER_D3D' : false },
    { 'SDL_OPENGLES' : false },
    { 'SDL_SHARED' : true }, { 'SDL_STATIC' : false })

  if get_option('xorg_support') == false
    sdl2_opt.add_cmake_defines(
      { 'SDL_X11' : false }, 
      { 'SDL_X11_SHARED' : false })
  endif

  if build_machine.system() == 'linux'
    sdl2_opt.add_cmake_defines(
      { 'SDL_WAYLAND' : true },
      { 'SDL_WAYLAND_SHARED' : true },
      { 'SDL_WAYLAND_LIBDECOR' : true},
      { 'SDL_WAYLAND_LIBDECOR_SHARED' : true})
  endif

  sdl2 = cmake.subproject('SDL', options : sdl2_opt)
  sdl2_dep = sdl2.dependency('SDL2')
else
  sdl2_dep = dependency('sdl2',
    #version : '>=2.28.4',
    required : true)
endif

Patata_Engine_dep = subproject('patata-engine').get_variable('Patata_Engine_dep')
# For Debug builds
if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
  add_project_arguments('-DDEBUG=1', language : 'cpp')
endif

# game_name is required to use use_custom_icon and icon_path

executable(meson.project_name(),
  'Main.cpp',
  include_directories : include_directories('subprojects/patata-engine/externals/Glad2/include'),
  dependencies : [Patata_Engine_dep, sdl2_dep],
  build_by_default : true,
  install : true,
  install_dir : join_paths(meson.global_build_root(),'../bin'),
  install_rpath : '.',
  build_rpath : '.')
