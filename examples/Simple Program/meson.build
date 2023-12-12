project('Game', 'cpp',
    default_options : ['buildtype=release'])

sdl2_dep = dependency('sdl2',
  required : true)

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
