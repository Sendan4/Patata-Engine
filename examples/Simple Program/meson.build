project('Game', 'cpp',
    default_options : ['buildtype=release'])

sdl2_dep = dependency('sdl2',
  version : '>=2.28.4',
  required : true)

#Patata_Engine_dep = subproject('Patata-Engine', default_options:['game_name=your game name', 'icon_path=path-to/icon.bmp', 'use_custom_icon=true']).get_variable('Patata_Engine_dep')

# game_name is required to use use_custom_icon and icon_path

executable(meson.project_name(),
  'Main.cpp',
  dependencies : [Patata_Engine_dep, sdl2_dep],
  build_by_default : true,
  install : true,
  install_dir : join_paths(meson.global_build_root(),'../bin'),
  install_rpath : join_paths(meson.global_build_root(),'../bin'),
  build_rpath : join_paths(meson.global_build_root(),'../bin'))
