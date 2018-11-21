import os
import sys

from common import (
    platform_name, supported_platforms, juce_path, frut_path, pluginval_path,
    build_dir, build_configs, build_archs_win, app_metadata, run_cmd
)


def _build_pluginval():
    root_path = os.getcwd()

    pluginval_build_path = os.path.join(pluginval_path, 'install')
    os.chdir(pluginval_build_path)
    root_path_rel = os.path.relpath(root_path)

    if platform_name == 'Darwin':
        plugin_build_bin_name = 'mac_build'
    elif platform_name == 'Windows':
        plugin_build_bin_name = 'windows_build.bat'
    elif platform_name == 'Linux':
        plugin_build_bin_name = 'linux_build'

    pluginval_build_bin_path = os.path.join(
        pluginval_build_path,
        plugin_build_bin_name
    )

    run_cmd(pluginval_build_bin_path)

    os.chdir(root_path_rel)


def _validate_plugins():
    build_path = os.path.abspath(build_dir)
    pluginval_bin_path = None
    plugin_paths = []

    if platform_name == 'Darwin':
        pluginval_bin_path = os.path.join(
            pluginval_path,
            'bin', 'mac', 'pluginval.app', 'Contents', 'MacOS', 'pluginval'
        )

        for c in build_configs:
            plugin_paths += [
                os.path.join(build_path, c, 'Meeblip Controller.component'),
                os.path.join(build_path, c, 'Meeblip Controller.vst'),
                os.path.join(build_path, c, 'Meeblip Controller.vst3'),
            ]
    elif platform_name == 'Windows':
        pluginval_bin_path = os.path.join(
            pluginval_path,
            'bin', 'windows', 'pluginval.exe'
        )

        for c in build_configs:
            arch_x64 = build_archs_win[1]
            plugin_paths += [
                os.path.join(build_path, arch_x64, c, 'VST', 'Meeblip Controller.dll'),
                os.path.join(build_path, arch_x64, c, 'VST3', 'Meeblip Controller.vst3'),
            ]
    elif platform_name == 'Linux':
        pluginval_bin_path = os.path.join(
            pluginval_path,
            'bin', 'linux', 'pluginval'
        )

        for c in build_configs:
            plugin_paths += [
                os.path.join(build_path, c, 'Meeblip Controller.vst'),
                os.path.join(build_path, c, 'Meeblip Controller.vst3'),
            ]

    for p in plugin_paths:
        run_cmd(
            '{pluginval_path} --strictness-level 5 --validate "{plugin_path}"'
                .format(pluginval_path=pluginval_bin_path, plugin_path=p)
        )


def run():
    _build_pluginval()
    _validate_plugins()


if __name__ == '__main__':
    sys.exit(run())

