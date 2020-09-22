

# Modal Tool Kit (MTK)
[![Build Status](https://travis-ci.com/chrislupp/MTK.svg?branch=master)](https://travis-ci.com/chrislupp/MTK)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/dddd6c11c65d4066b7ccec9675188171)](https://www.codacy.com/manual/chrislupp/MTK/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=chrislupp/MTK&amp;utm_campaign=Badge_Grade)

The Modal Tool Kit (MTK) is a C++/Python library that defines useful datatypes
for manipulating modal datasets. MTK provides modal comparison tools and a mode
tracking algorithm that has been applied to flutter problems (including
geometrical nonlinearities) and deformed modal analyses.

If you find MTK useful and use it in a work, please cite this work:

    @Misc{Lupp2017,
        author =   {Christopher A. Lupp},
        title =    {{MTK}: {The} {Modal} {Toolkit}},
        howpublished = {\url{https://github.com/chrislupp/MTK}},
        year = {2017--2020}
    }

    @inproceedings{LuppCesnik2018,
        address = {Bristol, UK},
        author = {Lupp, Christopher A and Cesnik, Carlos E S},
        booktitle = {RAeS 6th Aircraft Structural Design Conference},
        publisher = {RAeS},
        title = {{An Efficient Algorithm for Determining Flutter of
            Geometrically Nonlinearly Deformed Aircraft}},
        year = {2018}
    }

## Installation

First, copy the Includes.config.template file and rename it to Includes.config.
This file is used during the build process to find the proper include
directories. In the configuration file that you just created, modify the
following line:

    # Eigen include directory
    /path/to/Eigen

to point to your Eigen 3 include directory. For the purposes of this example,
let us assume that the Eigen installation is located at "/home/username/eigen".
As such, the modified line should now read as follows:

    # Eigen include directory
    /home/username/eigen

Save the file and close it.

Once the configuration file has been modified, MTK can be installed using pip,
for example, by calling:

    pip install .

If the command exits successfully, MTK should now be installed on your system.

## License

Copyright 2017-2020 Christopher A. Lupp

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.