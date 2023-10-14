fs = import('fs')
if not fs.is_dir(join_paths(meson.build_root(), '../bin/'))
  run_command('mkdir', join_paths(meson.build_root(), '../bin/'), check : true)
endif

run_command('cp', 'patata.yaml', meson.global_build_root(), check : true)
run_command('cp', '-r', 'LICENSES/', meson.global_build_root() + '/../bin/', check : true)

if get_option('game_name') != ''
  run_command('mv', meson.global_build_root() + '/patata.yaml', meson.global_build_root() + '/' + get_option('game_name') + '.yaml', check : true)

  run_command('cp', meson.global_build_root() + '/' + get_option('game_name') + '.yaml', meson.global_build_root() + '/../bin/', check : true)
else
  run_command('cp', meson.global_build_root() + '/patata.yaml', meson.global_build_root() + '/../bin/', check : true)
endif
