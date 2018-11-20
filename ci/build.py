import os
import sys

from common import (
    platform_name, supported_platforms, juce_path, frut_path, pluginval_path,
    build_dir, build_configs, build_archs_win, app_metadata, run_cmd
)


def _build_frut():
    root_path = os.getcwd()
    os.chdir(frut_path)

    build_path = os.path.abspath(os.path.join(frut_path, 'build'))
    if not os.path.exists(build_path):
        os.makedirs(build_path)

    os.chdir(build_path)
    root_path_rel = os.path.relpath(root_path)
    frut_path_rel = os.path.relpath(frut_path)
    juce_path_rel = os.path.relpath(juce_path)

    run_cmd(
        'cmake {path} -DCMAKE_INSTALL_PREFIX=../prefix -DJUCE_ROOT={juce_path}'
            .format(path=frut_path_rel, juce_path=juce_path_rel)
    )

    run_cmd('cmake --build . --target install')

    os.chdir(root_path_rel)


def _build_plugin():
    build_path = os.path.abspath(build_dir)

    if platform_name == 'Darwin':
        root_path = os.getcwd()

        if not os.path.exists(build_path):
            os.makedirs(build_path)

        os.chdir(build_path)
        root_path_rel = os.path.relpath(root_path)

        run_cmd('cmake {path} -G Xcode'.format(path=root_path_rel))

        for config in build_configs:
            run_cmd(
                'cmake --build . --clean-first --config {config}'
                    .format(config=config)
            )

        os.chdir(root_path_rel)
    elif platform_name == 'Windows':
        for arch in build_archs_win:
            arch_build_path = os.path.abspath(os.path.join(build_path, arch))
            if not os.path.exists(arch_build_path):
                os.makedirs(arch_build_path)

            root_path = os.getcwd()
            os.chdir(arch_build_path)
            root_path_rel = os.path.relpath(root_path)

            run_cmd(
                'cmake {path} -G "Visual Studio 15 2017" -A {arch}'
                    .format(arch=arch, path=root_path_rel)
            )

            for config in build_configs:
                run_cmd(
                    'cmake --build . --clean-first --config {config}'
                        .format(config=config)
                )

            os.chdir(root_path_rel)


def run():
    _build_frut()
    _build_plugin()


if __name__ == '__main__':
    sys.exit(run())
