project('Game', 'cpp',
    default_options : ['buildtype=release'])

sdl2_dep = dependency('sdl2',
  version : '>=2.24.1',
  required : true)

#Patata_Engine_dep = subproject('Patata-Engine', default_options:['game_name=your game name', 'icon_path=path-to/icon.bmp', 'use_custom_icon=true']).get_variable('Patata_Engine_dep')

# game_name is required to use use_custom_icon and icon_path

executable(meson.project_name(),
  'Main.cpp',
  dependencies : [Patata_Engine_dep, sdl2_dep])
