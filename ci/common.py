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

app_metadata_file = 'metadata.txt'
app_metadata = {}


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


def load_app_metadata():
    filepath = os.path.abspath(app_metadata_file)
    with open(filepath) as f:
        for line in f:
            k, v = line.partition('=')[::2]
            app_metadata[k.strip()] = v.strip()

    app_metadata['APP_OUTPUT_BASENAME'] = (
        '{app_name} - {app_version} - {app_os}'
            .format(
                app_name=app_metadata['APP_NAME'],
                app_version=app_metadata['APP_VERSION'],
                app_os='MacOS' if platform_name == 'Darwin' else 'Windows'
            )
    )


load_app_metadata()

