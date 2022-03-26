import matplotlib.pyplot as plt
import skrf as rf
from matplotlib.ticker import ScalarFormatter
import sys
import numpy as npy

## Create a figure with a number of subplots
fig, ((ax0, ax1, ax2), (ax3, ax4, ax5)) = plt.subplots(nrows = 2, ncols = 3)

# create a Network type from a touchstone file of a horn antenna
magLoop = rf.Network('maxCapacitance.s1p')
magLoop.frequency.unit= 'mhz'

## Look up minimum SWR and Frequency
min_SWR = magLoop.s_vswr[:,0,0].min()
f_match = magLoop.f[npy.argmin(magLoop.s_vswr[:,0,0])]  # frequency for min(|S11|)
print("Minimum SWR is: ",min_SWR , " at frequency: ", f_match)
ax0.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax0.set_title('Lowest resonant frequency')
ax0.scatter(f_match,min_SWR,marker='^')

magLoop = rf.Network('./locationOffice/20m120222.s1p')
magLoop.frequency.unit= 'mhz'

ax1.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax1.scatter(f_match,min_SWR,marker='^')

magLoop = rf.Network('./locationOffice/17m120222.s1p')
ax2.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax2.scatter(f_match,min_SWR,marker='^')

magLoop =rf.Network('./locationOffice/15m120222.s1p')
ax3.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax3.scatter(f_match,min_SWR,marker='^')

magLoop = rf.Network('./locationOffice/12m120222.s1p')
ax4.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax4.scatter(f_match,min_SWR,marker='^')

magLoop = rf.Network('./locationOffice/10m120222.s1p')
ax5.plot(magLoop.f, magLoop.s_vswr[:,0,0])
ax5.scatter(f_match,min_SWR,marker='^')

##ax0.legend(['SWR 40m band']) ## Legend will be skipped
##ax0.set_xlim([7000000,7200000]) ## Beautify this so it gets fist and last element from the data array

min_reading = str(round(min_SWR,2)) + " @ " + str(round(f_match/1000000,4)) + " MHz"
## ax0.text(f_match, 2, min_reading)
ax0.text(0.5, 0.5, min_reading, horizontalalignment='center', verticalalignment='center', transform=ax0.transAxes)
ax1.text(0.5, 0.5, min_reading, horizontalalignment='center', verticalalignment='center', transform=ax1.transAxes)

ax0.set_xlim([10180000,10250000])
ax1.set_xlim([14000000,14400000])
ax2.set_xlim([18000000,18400000])
ax3.set_xlim([21000000,21400000])
ax4.set_xlim([24700000,25200000])
ax5.set_xlim([29500000,30000000])

plotSet = [ax0, ax1, ax2, ax3, ax4, ax5]
titleSet = ['Lowest resonant frequency', '20m band', '17m band', '15m band' ,'12m band', '10m band']

for x in plotSet:
    x.set_ylim([1,10])
    x.set_xlabel('Frequency (MHz)')
    x.set_ylabel('VSWR')
    rf.plotting.scale_frequency_ticks(x,'MHz')
    x.set_title(titleSet[plotSet.index(x)])


fig.suptitle('SWR Coax MagLoop 10.2 to 29 MHz')
plt.show()