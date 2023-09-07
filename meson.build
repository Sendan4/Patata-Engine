project('Patata Engine',
  'cpp', 'c',
  version : '0',
  default_options : [
    'buildtype=release'],
  license : ['MIT'])

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

# commit macro
get_commit_hash_long = run_command('git', 'rev-parse', 'HEAD', check: true)
git_commit_long_hash = get_commit_hash_long.stdout().strip()

get_commit_hash_short = run_command('git', 'rev-parse', '--short', 'HEAD', check: true)
git_commit_short_hash = get_commit_hash_short.stdout().strip()

add_project_arguments('-DGIT_HASH_LONG="'+git_commit_long_hash+'"', language : 'cpp')
add_project_arguments('-DGIT_HASH_SHORT="'+git_commit_short_hash+'"', language : 'cpp')

# Build Type macro
if (get_option('buildtype') == 'release')
  add_project_arguments('-DBUILD_TYPE="Release"', language : 'cpp')
elif (get_option('buildtype') == 'debug')
  add_project_arguments(
    '-DBUILD_TYPE="Debug"',
    '-DDEBUG=1',
    language : 'cpp')
elif (get_option('buildtype') == 'debugoptimized')
  add_project_arguments(
    '-DBUILD_TYPE="Debug Optimized"',
    '-DDEBUG=1',
    language : 'cpp')
elif (get_option('buildtype') == 'minsize')
  add_project_arguments('-DBUILD_TYPE="Minimal Size Release"', language : 'cpp')
endif

branchCommand = run_command('git', 'branch', '--show-current', check: true)
branchCOutput = branchCommand.stdout().strip()
message('Branch:', branchCOutput)

# Macros
add_project_arguments(
  '-DPATATAVERSION=0',
  '-DGIT_BRANCH="'+branchCOutput+'"',
  '-DBUILDSYS="Meson"',
  '-DENGINE_NAME="Patata Engine"',
  language : 'cpp') 

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  version : '>=2.24.1',
  modules : ['SDL2::SDL2'])

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

glad2_sources = files([meson.source_root() + '/externals/Glad2/src/gl.c'])
glad2_includes = include_directories('externals/Glad2/include/')

Glad2_lib = shared_library(
  'Glad',
  version : '2.0.4',
  sources : glad2_sources,
  include_directories : glad2_includes)

Glad2 = declare_dependency(
  include_directories : glad2_includes,
  d_import_dirs : glad2_includes,
  link_with : Glad2_lib)

yamlcpp = dependency('yaml-cpp',
  static : false,
  required : true)

features = {
  'Vulkan' : Vulkan.found(),
  'OpenGL' : Glad2.found(),
  'SDL2' : sdl2_dep.found(),
  'Yaml-cpp' : yamlcpp.found()
}

summary({
  'OpenGL': features['OpenGL'],
  'Vulkan': features['Vulkan'],
  'SDL2' : features['SDL2'],
  'Yaml-cpp' : features['Yaml-cpp']},
  bool_yn : true)

subdir('assets')

copy = fs.copyfile(
  patata_icon_file_bmp,
  'patata.bmp')

copy2 = fs.copyfile(
  'patata.yaml',
  'patata.yaml')

include_main = include_directories('include')
subdir('src')

if target_machine.system() == 'windows'
  executable('Patata_Engine',
    source,
    Patata_icon,
    win_subsystem : 'console',
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2, yamlcpp],
    build_by_default : true)
else
  executable('Patata_Engine',
    source,
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2, yamlcpp],
    build_by_default : true)
endif
