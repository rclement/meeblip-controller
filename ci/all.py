import sys

import common
import build
import validate
import package


def run():
    common.check_platform()
    common.init_dependencies()
    build.run()
    package.run()
    validate.run()


if __name__ == '__main__':
    sys.exit(run())

