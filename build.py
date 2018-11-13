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


def check_platform():
    if platform_name not in supported_platforms:
        print('Platform currently not supported:', platform_name)
        sys.exit()


def init_dependencies():
    cmd = 'git submodule update --init --recursive'
    subprocess.run(cmd.split())


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
    subprocess.run([cmd], shell=True)

    cmd = (
        'cmake --build . --target install'
    )
    subprocess.run([cmd], shell=True)

    os.chdir(root_path_rel)


def build_plugin():
    if platform_name == 'Darwin':
        root_path = os.getcwd()

        build_path = os.path.abspath('build')
        if not os.path.exists(build_path):
            os.makedirs(build_path)

        os.chdir(build_path)
        root_path_rel = os.path.relpath(root_path)

        cmd = (
            'cmake {path} -G Xcode'
        ).format(path=root_path_rel)
        subprocess.run([cmd], shell=True)

        for config in build_configs:
            cmd = (
                'cmake --build . --clean-first --config {config}'
            ).format(config=config)
            subprocess.run([cmd], shell=True)

        os.chdir(root_path_rel)
    elif platform_name == 'Windows':
        for platform in supported_platforms:
            plat_build_path = os.path.abspath(os.path.join(build_path, platform))
            if not os.path.exists(plat_build_path):
                os.makedirs(plat_build_path)

            root_path = os.getcwd()
            os.chdir(plat_build_path)
            root_path_rel = os.path.relpath(root_path)

            cmd = (
                'cmake {path} -G "Visual Studio 15 2017" -A {platform}'
            ).format(platform=platform, path=root_path_rel)
            subprocess.run(cmd, shell=True)

            for config in configs:
                cmd = (
                    'cmake --build . --clean-first --config {config}'
                ).format(config=config)
                subprocess.run(cmd, shell=True)

            os.chdir(root_path_rel)


def build_all():
    check_platform()
    init_dependencies()
    build_frut()
    build_plugin()


if __name__ == '__main__':
    sys.exit(build_all())

