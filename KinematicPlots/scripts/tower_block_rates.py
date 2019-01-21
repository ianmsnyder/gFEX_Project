import ROOT
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pl
import palettable

f = ROOT.TFile('hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root')

factor = 2736*11.2450 # this is in kHz

# for plotting
fig, ax = pl.subplots()
ax.set_color_cycle(palettable.tableau.Tableau_20.mpl_colors)

# this loop fills up the above lists with values for every single dang inclusive trigger
for n in range(6):
  nth_tower_central = f.Get("rates/{0:d}tower_central".format(n+1))
  nth_block_central = f.Get("rates/{0:d}block_central".format(n+1))

  tower_x = []
  tower_y = []
  tower_err = []

  for i in range(1, nth_tower_central.GetSize()):
    threshold = nth_tower_central.GetBinLowEdge(i)
    num = nth_tower_central.Integral(i,-1)
    den = nth_tower_central.GetBinContent(0)
    rate = num/den * factor
    tower_x.append(threshold)
    tower_y.append(rate)
    tower_err.append(np.sqrt(num)/den * factor)

  block_x = []
  block_y = []
  block_err = []
  for i in range(1, nth_block_central.GetSize()):
    threshold = nth_block_central.GetBinLowEdge(i)
    num = nth_block_central.Integral(i,-1)
    den = nth_block_central.GetBinContent(0)
    rate = num/den * factor
    block_x.append(threshold)
    block_y.append(rate)
    block_err.append(np.sqrt(num)/den * factor)

  table = {}
  for thresh, value in zip(tower_x, tower_y):
    if thresh not in table:
       table[thresh] = {}
    table[thresh]['tower'] = value
  for thresh, value in zip(block_x, block_y):
    if thresh not in table:
       table[thresh] = {}
    table[thresh]['block'] = value

  # plot the stuff
  _, tower_caps, _ = ax.errorbar(tower_x, tower_y, label='{0:d}T'.format(n+1), yerr=tower_err, linewidth='2', capsize=5)
  _, block_caps, _ = ax.errorbar(block_x, block_y, label='{0:d}B'.format(n+1), yerr=block_err, linewidth='2', capsize=5)
  for cap in tower_caps + block_caps:
    cap.set_markeredgewidth(1)

  print "{0:>25s}{1:>25s}{2:>25s}".format("Threshold [GeV]", "{0:d} Tower Rate [kHz]".format(n+1), "{0:d} Block Rate [kHz]".format(n+1))
  for thresh in sorted(table.keys()):
    printStr = []
    printStr.append("{0:25.1f}".format(thresh))
    printStr.append("{0:25.1f}".format(table[thresh]['tower']) if 'tower' in table[thresh] else "{0:25s}".format(""))
    printStr.append("{0:25.1f}".format(table[thresh]['block']) if 'block' in table[thresh] else "{0:25s}".format(""))
    print "".join(printStr)

ax.set_yscale('log', nonposy='clip')
ax.set_xlabel('tower/block threshold [GeV]')
ax.set_ylabel('rate [kHz]')
ax.set_title('Rates of Min-Bias <$\mu$>=80 Sample for different gTower/gBlock thresholds')

ax.xaxis.grid(True, which='major')
ax.yaxis.grid(True, which='major', linestyle='-')
ax.yaxis.grid(True, which='minor')

ticks = np.arange(0, 210, 10)
ax.xaxis.set_ticks(ticks)
ax.set_xlim([ticks[0], ticks[-1]+10])
ax.set_ylim([0.1, 100000.0])

twinx = ax.twinx()
twinx.set_yscale('log', nonposy='clip')
twinx.set_yticks(ax.get_yticks().tolist())

twinx.set_yticklabels(['0.01 kHz', '0.1 kHz', '1 kHz', '10 kHz', '100 kHz', '1 MHz', '10 MHz', '100 MHz', '1 GHz'])
twinx.set_ylim(ax.get_ylim())

ax.axhspan(0, 5, alpha=0.5, color='red')

ax.text(90, 1, 'Low Statistics', weight='bold', va='center', ha='center', color='w', size='x-large')

ax.legend(ncol=6)

pl.show()
