Release Notes
=============


Version 3.0.3
-------------

Bugfixes:
    - removed redundant Eigen includes (from Eigency). [found and fixed by
        Bernardo Bahia Monteiro]
    - added numpy includes.


Version 3.0.1
-------------

Bugfixes:
    - changed Environment.config to Includes.config for consistency.
    - changed get_includes to GetIncludeDirectory for consistency.



Version 3.0.0
-------------

Added Features:
    - Added an object-oriented mode tracking alternative
    - Flattened the package namespace. Objects can be called directly from MTK
    instead of MTK.MTK
    - Added Python-based unit tests
    - Added unit testing to CI, so that the tests are run for every commit

Bugfixes:
    - Fixed the EigenPair constructor on the Python side to accept eigen value
    and eigen vector data
    - Fixed the Cython wrapping w.r.t. handling complex numbers

Deprecated Features:
    - The function-based mode tracking is now deprecated and will be removed in
    a future release