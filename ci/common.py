import os
import platform
import subprocess


platform_name = platform.system()
supported_platforms = ['Darwin', 'Windows']

juce_path = os.path.abspath('sdks/juce')
frut_path = os.path.abspath('sdks/frut')
pluginval_path = os.path.abspath('sdks/pluginval')

build_dir = 'build'
build_configs = ['Release']
build_archs_win = ['Win32', 'x64']


def run_cmd(cmd):
    rv = None

    if platform_name == 'Darwin':
        rv = subprocess.run([cmd], shell=True)
    elif platform_name == 'Windows':
        rv = subprocess.run(cmd, shell=True)

    if rv is not None:
        rv.check_returncode()


def check_platform():
    if platform_name not in supported_platforms:
        raise exceptions.RuntimeError(
            'Platform currently not supported: {platform_name}'
                .format(platform_name=platform_name)
        )


def init_dependencies():
    run_cmd('git submodule update --init --recursive')

