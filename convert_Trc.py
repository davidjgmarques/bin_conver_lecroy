from readTrc import Trc
import matplotlib.pyplot as plt


trc = Trc()
fName = "./data/test_run_pmt_zoom--3rd--300V_cm--00000.trc"
datX, datY, d = trc.open(fName)
print(d)

plt.plot(datX, datY)
print(len(datX))

for i in range(100):

    print("t: {0} , ampl: {1}".format(datX[i],datY[i]))

plt.show()