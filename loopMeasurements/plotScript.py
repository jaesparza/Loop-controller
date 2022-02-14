import matplotlib.pyplot as plt
import skrf as rf
from matplotlib.ticker import ScalarFormatter
import sys
import numpy as npy

## rf.stylely()

# create a Network type from a touchstone file of a horn antenna
magLoop = rf.Network('maxCapacitance.s1p')
magLoop.frequency.unit= 'mhz'

## Look up minimum SWR and Frequency
min_SWR = magLoop.s_vswr[:,0,0].min()
f_match = magLoop.f[npy.argmin(magLoop.s_vswr[:,0,0])]  # frequency for min(|S11|)
print("Minimum SWR is: ",min_SWR , " at frequency: ", f_match)

plt.plot(magLoop.f,
            magLoop.s_vswr[:,0,0])

##magLoop.plot_s_vswr(m=0,n=0, label='40m band') ## Plot SWR


plt.title('VSWR 40m band')
plt.ylabel('VSWR')
plt.xlabel('Frequency (MHz)')
plt.scatter(f_match,min_SWR,marker='^') 

min_reading = str(round(min_SWR,2)) + " @ " + str(round(f_match/1000000,4)) + " MHz"
#plt.text(f_match, 2, min_reading)

ax = plt.gca() ## Get the axis so it can be edited

plt.text(0.5, 0.5, min_reading, horizontalalignment='center', verticalalignment='center', transform=ax.transAxes)


rf.plotting.scale_frequency_ticks(ax,'Mhz')
## ax.legend(['SWR 40m band'])
ax.set_xlim([10180000,10280000]) ## Beautify this so it gets fist and last element from the data array
ax.set_ylim([1,10])
plt.show()