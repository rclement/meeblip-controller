import os
import sys

from common import (
    platform_name, supported_platforms, juce_path, frut_path, pluginval_path,
    build_dir, build_configs, build_archs_win, run_cmd
)


def _build_installer():
    build_path = os.path.abspath(build_dir)

    if platform_name == 'Darwin':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.pkgproj'
        )

        run_cmd(
            'packagesbuild -v "{installer_path}"'
                .format(installer_path=installer_path)
        )
    elif platform_name == 'Windows':
        installer_path = os.path.join(
            build_path, 'installer', 'meeblip-controller.iss'
        )

        run_cmd(
            'iscc "{installer_path}"'
                .format(installer_path=installer_path)
        )


def run():
    _build_installer()


if __name__ == '__main__':
    sys.exit(run())

