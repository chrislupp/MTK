from MTK.MTK import EigenPair, ModeSet, PlotReal

from matplotlib.pyplot import show


pair = EigenPair()
set1 = ModeSet()

pair["evalue"] = 0.0
set1.AddPair(pair)
pair["evalue"] = 1.0
set1.AddPair(pair)



set2 = ModeSet()

pair["evalue"] = 1.0
set2.AddPair(pair)
pair["evalue"] = 0.0
set2.AddPair(pair)

sets = [set1, set2]
var = [0.0, 1.0]

# plot the mode sets
PlotReal(var, sets)

show()