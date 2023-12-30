# assets
if get_option('enable_icon')
  add_project_arguments('-DUSE_ICON=1', language : 'cpp')

  fs = import('fs')
  if not fs.is_dir(join_paths(meson.global_build_root(), '../bin/'))
    run_command('mkdir', join_paths(meson.global_build_root(), '../bin'), check : true)
  endif

  if get_option('use_custom_icon')
    if get_option('icon_path') != ''
      run_command('cp', get_option('icon_path'), meson.global_build_root(), check : true)

      if get_option('game_name') != ''
        run_command('mv', meson.global_build_root() + '/icon.bmp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', check : true)

        run_command('cp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', meson.global_build_root() + '/../bin', check : true)
      endif
    endif
  else
    if get_option('buildtype') == 'release' or get_option('buildtype') == 'minsize'
      run_command('cp', 'icon/patata-release.bmp', join_paths(meson.global_build_root()), check : true)
    else
      run_command('cp', 'icon/patata-debug.bmp', join_paths(meson.global_build_root()), check : true)
    endif

    if get_option('game_name') != ''
      if get_option('buildtype') == 'release' or get_option('buildtype') == 'minsize'
        run_command('mv', meson.global_build_root() + '/patata-release.bmp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', check : true)
      else
        run_command('mv', meson.global_build_root() + '/patata-debug.bmp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', check : true)
      endif

      run_command('cp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', meson.global_build_root() + '/../bin', check : true)
    else
      if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
        run_command('cp', meson.global_build_root() + '/patata-debug.bmp', meson.global_build_root() + '/../bin', check : true)
      else
        run_command('cp', meson.global_build_root() + '/patata-release.bmp', meson.global_build_root() + '/../bin', check : true)
      endif
    endif
  endif
endif
