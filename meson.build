project(
  'iris',
  'cpp',
  version : '0.0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++20', 'default_library=static'],
)

ftxui = subproject('ftxui')

screen_dep = ftxui.get_variable('screen_dep')
dom_dep = ftxui.get_variable('dom_dep')
component_dep = ftxui.get_variable('component_dep')

dependencies = [
screen_dep, dom_dep, component_dep]

exe = executable(
  'iris',
  'iris.cpp',
  install : true,
  dependencies : dependencies,
)

test('basic', exe)
