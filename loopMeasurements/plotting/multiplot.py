import matplotlib.pyplot as plt
import skrf as rf
from matplotlib.ticker import ScalarFormatter
import sys
import numpy as npy

measurementLocation = 'locationLivingRoom'
date = '310322'
extension = '.s1p'

titleSet = ['Lowest resonant frequency', '20m band', '17m band', '15m band' ,'12m band', '10m band']
bandSet = ["20m", '20m', '17m', '15m', '12m', '10m']

## Create a figure with a number of subplots
fig, ((ax0, ax1, ax2), (ax3, ax4, ax5)) = plt.subplots(nrows = 2, ncols = 3)

def myPlotter(plotContainer,band):
    magLoop = rf.Network('../'+measurementLocation+'/'+band+date+extension)
    magLoop.frequency.unit= 'mhz'

    ## Look up minimum SWR and Frequency
    min_SWR = magLoop.s_vswr[:,0,0].min()
    f_match = magLoop.f[npy.argmin(magLoop.s_vswr[:,0,0])]  # frequency for min(|S11|)
    print("Minimum SWR is: ",min_SWR , " at frequency: ", f_match)

    plotContainer.plot(magLoop.f, magLoop.s_vswr[:,0,0])
    plotContainer.set_title('Lowest resonant frequency')
    plotContainer.scatter(f_match,min_SWR,marker='^')
    min_reading = str(round(min_SWR,2)) + " @ " + str(round(f_match/1000000,4)) + " MHz"
    print("Minimum SWR is: ",min_SWR , " at frequency: ", f_match)
    plotContainer.text(0.5, 0.5, min_reading, horizontalalignment='center', verticalalignment='center', transform=plotContainer.transAxes)

myPlotter(ax0,"20m")
myPlotter(ax1,"20m")
myPlotter(ax2,"17m")
myPlotter(ax3,"15m")
myPlotter(ax4,"12m")
myPlotter(ax5,"10m")

plotSet = [ax0, ax1, ax2, ax3, ax4, ax5]

ax0.set_xlim([14000000,14100000])
ax1.set_xlim([13650000,14350000])
ax2.set_xlim([18050000,18170000])
ax3.set_xlim([21000000,21450000])
ax4.set_xlim([24890000,24990000])
ax5.set_xlim([28000000,30000000])

for x in plotSet:
    x.set_ylim([1,10])
    x.set_xlabel('Frequency (MHz)')
    x.set_ylabel('VSWR')
    rf.plotting.scale_frequency_ticks(x,'MHz')
    x.set_title(titleSet[plotSet.index(x)])

fig.suptitle('SWR Magnetic Loop')
plt.show()