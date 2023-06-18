"""
    Modal Tool Kit (MTK)

    Copyright 2017-2023 Christopher A. Lupp

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
"""
import unittest

from MTK import EigenPair


class CheckEigenPair(unittest.TestCase):

    def test_DefaultCreation(self):
        """
        Tests the basic creation of an EigenPair.
        """
        a = EigenPair()

    def test_AlternateCreation(self):
        """
        Tests the basic creation of an EigenPair with initial values.
        """
        a = EigenPair(1.0, [0.0, 1.0])

        # check the value and vector
        self.assertTrue(a["value"] == 1.0)
        self.assertTrue((a["vector"] == [0.0, 1.0]).all())

    def test_AlternateCreationComplex(self):
        """
        Tests the basic creation of an EigenPair with initial complex values.
        """
        a = EigenPair(1.0 + 1.0*1j, [0.0, 1.0 + 1.0 * 1j])

        # check the value and vector
        self.assertTrue(a["value"] == 1.0 + 1*1j)
        self.assertTrue((a["vector"] == [0.0, 1.0 + 1.0*1j]).all())

    def test_Properties(self):
        """
        Tests the evaluation of the value and vector properties.
        """
        a = EigenPair(1.0 + 1.0*1j, [0.0, 1.0 + 1.0 * 1j])

        # check the value and vector
        self.assertTrue(a.value == 1.0 + 1*1j)
        self.assertTrue((a.vector == [0.0, 1.0 + 1.0*1j]).all())


def main():
    unittest.main()


if __name__ == "__main__":
    main()
