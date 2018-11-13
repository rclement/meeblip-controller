import os
import platform
import subprocess
import sys


platform_name = platform.system()
supported_platforms = ['Darwin', 'Windows']

juce_path = os.path.abspath('sdks/juce')
frut_path = os.path.abspath('sdks/frut')

build_configs = ['Debug', 'Release']
build_archs_win = ['Win32', 'x64']


def _run(cmd):
  if platform_name == 'Darwin':
    subprocess.run([cmd], shell=True)
  elif platform_name == 'Windows':
    subprocess.run(cmd, shell=True)


def check_platform():
    if platform_name not in supported_platforms:
        print('Platform currently not supported:', platform_name)
        sys.exit()


def init_dependencies():
    _run('git submodule update --init --recursive')


def build_frut():
    root_path = os.getcwd()
    os.chdir(frut_path)

    build_path = os.path.abspath('build')
    if not os.path.exists(build_path):
        os.makedirs(build_path)

    os.chdir(build_path)
    root_path_rel = os.path.relpath(root_path)
    frut_path_rel = os.path.relpath(frut_path)
    juce_path_rel = os.path.relpath(juce_path)

    cmd = (
        'cmake {path} -DCMAKE_INSTALL_PREFIX=../prefix -DJUCE_ROOT={juce_path}'
    ).format(path=frut_path_rel, juce_path=juce_path_rel)
    _run(cmd)

    _run('cmake --build . --target install')

    os.chdir(root_path_rel)


def build_plugin():
    build_path = os.path.abspath('build')

    if platform_name == 'Darwin':
        root_path = os.getcwd()

        if not os.path.exists(build_path):
            os.makedirs(build_path)

        os.chdir(build_path)
        root_path_rel = os.path.relpath(root_path)

        cmd = (
            'cmake {path} -G Xcode'
        ).format(path=root_path_rel)
        _run(cmd)

        for config in build_configs:
            cmd = (
                'cmake --build . --clean-first --config {config}'
            ).format(config=config)
            _run(cmd)

        os.chdir(root_path_rel)
    elif platform_name == 'Windows':
        for arch in build_archs_win:
            arch_build_path = os.path.abspath(os.path.join(build_path, arch))
            if not os.path.exists(arch_build_path):
                os.makedirs(arch_build_path)

            root_path = os.getcwd()
            os.chdir(arch_build_path)
            root_path_rel = os.path.relpath(root_path)

            cmd = (
                'cmake {path} -G "Visual Studio 15 2017" -A {arch}'
            ).format(arch=arch, path=root_path_rel)
            _run(cmd)

            for config in build_configs:
                cmd = (
                    'cmake --build . --clean-first --config {config}'
                ).format(config=config)
                _run(cmd)

            os.chdir(root_path_rel)


def build_installer():
    if platform_name == 'Darwin':
        _run('packagesbuild -v installer/meeblip-controller.pkgproj')
    elif platform_name == 'Windows':
        _run('iscc "installer\meeblip-controller.iss"')


def build_all():
    check_platform()
    init_dependencies()
    build_frut()
    build_plugin()
    build_installer()


if __name__ == '__main__':
    sys.exit(build_all())

