from pkg_resources import resource_filename
import os.path


def get_includes():
    """Returns the include path for MTK.
    """
    root = os.path.dirname(__file__)
    path = [root]
    return path