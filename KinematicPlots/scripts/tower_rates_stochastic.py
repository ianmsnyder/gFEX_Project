import ROOT
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pl
from scipy import optimize

f = ROOT.TFile('hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root')

den = f.Get("turnon/tower/all/denominator").Integral()
factor = 2736*11.2450 # this is in kHz
x = np.arange(5, 100, 5)
y = []

for threshold in x:
  y.append(f.Get("turnon/tower/all/L1_GFEX_T{0:d}/numerator_negative".format(threshold)).Integral()/den * factor)

"""
# http://scipy-cookbook.readthedocs.io/items/FittingData.html
logx = np.log10(x)
logy = np.log10(y)
yerr = np.array([0.1]*len(logy))

powerlaw_40 = lambda x, amp, exponent: amp * (x**exponent)

fitfunc_40 = lambda p, x: p[0] + p[1] * x
errfunc_40 = lambda p, x, y, err: (y - fitfunc_40(p, x)) / err
pinit_40 = [1.0, -1.0]

# first fit only to 40 GeV and above
index_40 = np.where(x >= 40)
out_40 = optimize.leastsq(errfunc_40, pinit_40, args=(logx[index_40], logy[index_40], yerr[index_40]), full_output=1)
pfinal_40 = out_40[0]
covar_40 = out_40[1]
exponent_40 = pfinal_40[1]
amp_40 = 10.0**pfinal_40[0]
exponentErr_40 = np.sqrt( covar_40[0][0] )
ampErr_40 = np.sqrt( covar_40[1][1] ) * amp_40


powerlaw_10 = lambda x, amp1, exponent1, amp2, exponent2: amp1 * (x**exponent1) + amp2 * (x**exponent2)

# redo again, fixing the 40+ and fit the 10-25 bins
fitfunc_10 = lambda p, x: (p[0] + p[1] * x)
errfunc_10 = lambda p, x, y, err: (y - fitfunc_10(p, x)) / err
pinit_10 = [1.0, -1.0]

index_10 = np.where(np.logical_and(x >= 10, x <= 25))
out_10 = optimize.leastsq(errfunc_10, pinit_10, args=(logx[index_10], logy[index_10], yerr[index_10]), full_output=1)
pfinal_10 = out_10[0]
covar_10 = out_10[1]
exponent_10 = pfinal_10[1]
amp_10 = 10.0**pfinal_10[0]
exponentErr_10 = np.sqrt( covar_10[0][0] )
ampErr_10 = np.sqrt( covar_10[1][1] ) * amp_10
"""
# plot the stuff
fig, ax = pl.subplots()
#ax.plot(x, powerlaw_10(x, amp_10, exponent_10, 0, 0), color='red')
#ax.plot(x, powerlaw_40(x, amp_40, exponent_40), color='blue')
ax.scatter(x, y)
for xp,yp in zip(x,y):
  print xp, yp
#ax.set_yscale('log', nonposy='clip')
ax.set_xlabel('tower threshold [GeV]')
ax.set_ylabel('rate [kHz]')
ax.set_title('Rates of Min-Bias <$\mu$>=80 Sample for different gTower thresholds')

#ax.text(5, 6.5, 'f = %5.2f*x^%5.2f' % (amp_10/1.e3, exponent_10), color='red')
#ax.text(5, 4.5, 'f = %5.2f*x^%5.2f' % (amp_40/1.e3, exponent_40), color='blue')

ax.xaxis.grid(True, which='major')
ax.xaxis.set_ticks(np.arange(0, x.max(), 10))

pl.show()
