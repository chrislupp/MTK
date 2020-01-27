# Modal Tool Kit (MTK)

## Installation

First, copy the Environment.config.in file and rename it to Environment.config.
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

   Copyright 2017 Christopher A. Lupp

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.