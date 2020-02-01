"""
    Modal Tool Kit (MTK)

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
"""
import unittest
from numpy import loadtxt
from MTK import EigenPair, ModeSet, ModeTracker


def LoadData(fname):
    """Loads data from a csv file.
    """
    # open file
    file = open(fname, 'r')

    # load the data from the file
    data = loadtxt(file, delimiter=",")

    # close the file
    file.close()

    return data


def CheckDataFile(results, fname):
    """Checks the results against reference data in a csv file.
    """
    return False



class CheckModeTracker(unittest.TestCase):

    def test_DefaultCreation(self):
        """
        Tests the basic instantiation of a ModeTracker object.
        """
        tracker = ModeTracker()


    def test_ModeTrackingReal(self):
        """
        Tests the basic instantiation of a ModeTracker object.
        """
        tracker = ModeTracker()

        data = []

        for i in range(1, 12):
            # load the data from the csv file
            fname = "deformed_modal/EValueReal_" + str(i) + ".csv"
            evals = LoadData(fname)
            fname = "deformed_modal/VectorsReal_" + str(i) + ".csv"
            evecs = LoadData(fname)

            # create the mode set from the loaded data
            set = ModeSet()

            # populate the mode set
            for j in range(len(evals)):
                # create the eigen pair
                pair = EigenPair()

                # set the eigenvalue and eigenvector
                pair.value = evals[j]
                pair.vector = evecs[:,j]

                # add the pair to the mode set
                set.AddPair(pair)

            # add the mode set to the mode progression
            data += [set,]

        # create the seed set (in this case the first set of modes)
        seed = data[0]

        # add the data and the seed set to the mode tracker
        tracker.seed = seed
        tracker.data = data

        # run the mode tracker
        tracker.Track()

        # obtain the tracked data
        results = tracker.tracked_data

        # check the results compared to the reference data (from file)
        status = CheckDataFile(results, "deformed_modal/results.csv")

        # check if the test passed compared to reference data
        self.assertTrue(status)


    # def test_ModeTrackingImag(self):
    #     """
    #     Tests the basic instantiation of a ModeTracker object.
    #     """
    #     tracker = ModeTracker()


def main():
    unittest.main()


if __name__ == "__main__":
    main()