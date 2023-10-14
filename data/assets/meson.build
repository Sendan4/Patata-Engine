# assets
if get_option('enable_icon')
  add_project_arguments('-DUSE_ICON=1', language : 'cpp')
  message('Icon: Yes')

  fs = import('fs')
  if not fs.is_dir(join_paths(meson.global_build_root(), '../bin/'))
    run_command('mkdir', join_paths(meson.global_build_root(), '../bin/'), check : true)
  endif

  if get_option('use_custom_icon')
    if get_option('icon_path') != ''
      message('Custom Icon: Yes')
      message('Icon Path: ' + get_option('icon_path'))

      run_command('cp', get_option('icon_path'), meson.global_build_root(), check : true)

      if get_option('game_name') != ''
        run_command('mv', meson.global_build_root() + '/icon.bmp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', check : true)

        run_command('cp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', meson.global_build_root() + '/../bin', check : true)
      endif
    endif
  else
    message('Custom Icon: No')

    run_command('cp', 'icon/patata.bmp', join_paths(meson.global_build_root()), check : true)

    if get_option('game_name') != ''
      run_command('mv', meson.global_build_root() + '/patata.bmp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', check : true)

      run_command('cp', meson.global_build_root() + '/' + get_option('game_name') + '.bmp', meson.global_build_root() + '/../bin', check : true)
    else
      run_command('cp', meson.global_build_root() + '/patata.bmp', meson.global_build_root() + '/../bin', check : true)
    endif
  endif
else
  message('Icon: No')
endif
