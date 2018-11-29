import os
import sys
import zipfile

from common import (
    platform_name, supported_platforms, juce_path, frut_path, pluginval_path,
    build_dir, build_configs, build_archs_win, app_metadata, run_cmd
)


def _build_installer():
    build_path = os.path.abspath(build_dir)

    installer_output_path = os.path.join(build_path, 'installer', 'output')
    installer_output_appname = os.path.join(
        installer_output_path, app_metadata['APP_NAME']
    )
    installer_output_basename = os.path.join(
        installer_output_path, app_metadata['APP_OUTPUT_BASENAME']
    )

    output_files = []
    installer_output_arcname = (
        installer_output_basename + '.zip'
    ).replace(' ', '_')

    if platform_name == 'Darwin':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.pkgproj'
        )

        run_cmd(
            'packagesbuild -v "{installer_path}"'
                .format(installer_path=installer_path)
        )

        output_files.append(installer_output_basename + '.pkg')
    elif platform_name == 'Windows':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.iss'
        )

        run_cmd(
            'iscc "{installer_path}"'
                .format(installer_path=installer_path)
        )

        output_files = [installer_output_basename + '.exe']
    elif platform_name == 'Linux':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.sh'
        )

        run_cmd(
            'sh "{installer_path}"'
                .format(installer_path=installer_path)
        )

        output_files = [
            installer_output_basename + '.AppImage',
            installer_output_appname + '.so',
            os.path.join(installer_output_path, 'presets'),
            os.path.join(installer_output_path, 'licenses')
        ]

    with zipfile.ZipFile(installer_output_arcname, 'w') as z:
        for of in output_files:
            z.write(of, os.path.basename(of))


def run():
    _build_installer()


if __name__ == '__main__':
    sys.exit(run())

