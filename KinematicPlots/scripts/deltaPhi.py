import ROOT
from palettable import colorbrewer
from itertools import cycle
import os

f = ROOT.TFile('hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root')

for objType, objName in [('offline', 'AntiKt4'), ('offline', 'AntiKt10'), ('offline', 'AntiKt10Trimmed'), ('offline', 'CamKt12')]:
  for kinematic, xaxis_label in zip(['deltaPhi'], ['#Delta#phi']):
    tex = []
    colors = cycle(colorbrewer.qualitative.Set1_9.colors)
    c = ROOT.TCanvas()
    leg = ROOT.TLegend(0.8,0.8,0.9,0.9)
    for selection, drawstyle in zip(['presel', 'postsel'], ['hist', 'hist same']):
      color = ROOT.TColor.GetColor(*next(colors))
      hist = f.Get(os.path.join(selection, objType, objName, kinematic))
      hist.SetStats(0)
      leg.AddEntry(hist, selection, "lf")
      hist.SetTitle('{0:s}/{1:s}'.format(objType, objName.replace('_', ' ')))
      hist.GetXaxis().SetTitle('leading object {0:s}'.format(xaxis_label))
      hist.GetYaxis().SetTitle('Events')
      hist.GetXaxis().SetTitleOffset(1.3)
      hist.GetYaxis().SetTitleOffset(1.3)
      hist.Draw(drawstyle)
      hist.SetLineColor(color)
      hist.SetMarkerColor(color)
      hist.SetLineWidth(2)
      #hist.SetFillColor(color)
    leg.Draw()

    # ATLAS Simulation label
    labelx = 0.12
    labely = 0.86
    tex.append(ROOT.TLatex(labelx,labely,"ATLAS"))
    tex[-1].SetNDC()
    tex[-1].SetTextFont(72)
    tex[-1].SetLineWidth(2)
    tex[-1].Draw()
    tex.append(ROOT.TLatex(labelx+0.12,labely,"Simulation"))
    tex[-1].SetNDC()
    tex[-1].SetTextFont(42)
    tex[-1].SetLineWidth(2)
    tex[-1].Draw()

    c.Modified()
    c.Update()
    c.SaveAs('kinematic_{0:s}_{1:s}_{2:s}.pdf'.format(objType, objName, kinematic))
    c.Clear()
