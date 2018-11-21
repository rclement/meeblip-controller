import os
import sys
import zipfile

from common import (
    platform_name, supported_platforms, juce_path, frut_path, pluginval_path,
    build_dir, build_configs, build_archs_win, app_metadata, run_cmd
)


def _build_installer():
    build_path = os.path.abspath(build_dir)

    installer_output_basename = os.path.join(
        build_path, 'installer', 'output', app_metadata['APP_OUTPUT_BASENAME']
    )

    installer_output_name = installer_output_basename
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

        installer_output_name += '.pkg'
    elif platform_name == 'Windows':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.iss'
        )

        run_cmd(
            'iscc "{installer_path}"'
                .format(installer_path=installer_path)
        )

        installer_output_name += '.exe'
    elif platform_name == 'Linux':
        print(
            'Installer packaging not implemented for this platform: {platform_name}'
                .format(platform_name=platform_name)
        )
        return


    with zipfile.ZipFile(installer_output_arcname, 'w') as z:
        z.write(
            installer_output_name,
            os.path.basename(installer_output_name)
        )


def run():
    _build_installer()


if __name__ == '__main__':
    sys.exit(run())

