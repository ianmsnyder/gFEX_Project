import ROOT
from palettable import colorbrewer
from itertools import cycle

f = ROOT.TFile('hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root')

den = f.Get("turnon/tower/all/denominator")
x = range(5, 100, 5)

colors = cycle(colorbrewer.qualitative.Set1_9.colors)

c = ROOT.TCanvas()
graphs = []

for threshold in x:
  color = ROOT.TColor.GetColor(*next(colors))
  num = f.Get("turnon/tower/all/L1_GFEX_T{0:d}/numerator".format(threshold))
  gr = ROOT.TGraphAsymmErrors(num, den, str(threshold))
  gr.SetTitle('Turn-On Curves for Min-Bias for L1_GFEX_T{0:d}'.format(threshold))
  gr.GetXaxis().SetTitle('small-R jet pT [GeV]')
  gr.GetYaxis().SetTitle('Efficiency')
  graphs.append(gr)
  gr.SetMinimum(0.0)
  gr.SetMaximum(1.1)
  gr.Draw("epal")
  gr.SetLineColor(color)
  gr.SetMarkerColor(color)
  gr.SetFillColor(color)
  for i in range(0, gr.GetN()):
    gr.SetPointEXlow(i, 0.0)
    gr.SetPointEXhigh(i, 0.0)
  c.Modified()
  c.Update()
  c.SaveAs('turnon_L1_GFEX_T{0:d}.pdf'.format(threshold))
