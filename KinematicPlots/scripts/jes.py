import ROOT
ROOT.gStyle.SetOptStat(0)

import itertools
import os

scales = [
  78420000*1.0240E+00/1999400,
  78420000*6.7198E-04/1999000,
  2433200*3.3264E-04/1994600,
  26454*3.1963E-04/7884500,
  254.63*5.2982E-04/7979800,
  4.5535*9.2255E-04/7981600
]

def histAdd(a, b):
  a.Add(b)
  return a

# containing canvas for everything
c = ROOT.TCanvas()

dijets = [ROOT.TFile.Open("hist-user.cylin.L1CaloSimu.JZ{0:d}W.tag-00-00-17_OUTPUT.root".format(i)) for i in range(6)]
top_paths = ['precalibration', 'postcalibration']
hist_names = ['gBlockEt', 'gBlockEt_log_pos', 'gBlockEt_log_neg', 'gBlockEtRatio']

hist_names1D = ['gBlockRho', 'EtSigma']

# cache all histograms
hists_cache = []
hists_cache1D = []
# all histogram paths stored in here
hists = {}
hists1D = {}


for top_path in ['precalibration', 'postcalibration']:
  for name in hist_names:
    stored_key = '_'.join([top_path, name])
    for dijet, scale in zip(dijets, scales): # Loops over files, colors, and scales respectively
      hists_cache.append(dijet.Get(os.path.join(top_path, name)))
      hists_cache[-1].Scale(scale*35000000)
      if stored_key in hists:
        hists[stored_key].Add(hists_cache[-1])
      else:
        hists[stored_key] = hists_cache[-1].Clone()


for top_path in ['precalibration', 'postcalibration']:
  for name in hist_names1D:
    stored_key = '_'.join([top_path, name])
    for dijet, scale in zip(dijets, scales): # Loops over files, colors, and scales respectively
      hists_cache1D.append(dijet.Get(os.path.join(top_path, name)))
      hists_cache1D[-1].Scale(scale*35000000)
      if stored_key in hists1D:
        hists1D[stored_key].Add(hists_cache1D[-1])
      else:
        hists1D[stored_key] = hists_cache1D[-1].Clone()

# for k,v in hists1D.iteritems():
#   v.Draw("hist")
#   c.Modified()
#   c.
        
for k, v in hists.iteritems():
  v.Draw("hist colz")
  p = v.ProfileX("profilex")
  p.SetMarkerColor(ROOT.kWhite)
  p.SetLineColor(ROOT.kWhite)
  p.SetMarkerSize(0.1)
  otherp = p.Clone()
  otherp.SetMarkerColor(ROOT.kBlack)
  otherp.SetLineColor(ROOT.kBlack)
  otherp.SetMarkerSize(1.0)
  otherp.Draw("same E1 C")
  p.Draw("same E1 C")
  c.SetLogz()
  c.Modified()
  c.Update()
  c.Print("{0:s}.pdf".format(k))
  c.Clear()

resolution_hists = {}
for top_path in top_paths:
  key_name = '{0:s}_gBlockEtRatio'.format(top_path)
  h = hists[key_name]

  nbins = h.GetNbinsX()
  xlow = h.GetXaxis().GetBinLowEdge(1)
  xhigh = h.GetXaxis().GetBinLowEdge(nbins+1)
  ratio_mean = ROOT.TH1F("ratio_mean_{0:s}".format(top_path), "Mean of gBlock E_{T} / Offline p_{T}", nbins, xlow, xhigh)
  resolution_hists[top_path] = ROOT.TH1F("ratio_resolution_{0:s}".format(top_path), "Resolution of gBlock E_{T} / Offline p_{T}", nbins, xlow, xhigh)
  ratio_mean.SetXTitle(h.GetXaxis().GetTitle())
  ratio_mean_stddev = ratio_mean.Clone()
  ratio_mean_meanerr = ratio_mean.Clone()

  fname = "{0:s}_projections".format(key_name)
  c.Print("{0:s}.pdf[".format(fname))
  for i in range(1,h.GetNbinsX()+1):
    lowedge = h.GetXaxis().GetBinLowEdge(i)
    highedge = h.GetXaxis().GetBinLowEdge(i+1)
    pname = "oJetPt {0:0.1f} - {1:0.1f} [GeV]".format(lowedge, highedge)
    projection = h.ProjectionY(pname, i, i+1)
    projection.Draw("hist")
    projection.SetTitle("Offline Jet p_{{T}} range: {0:0.1f}-{1:0.1f} [GeV]".format(lowedge, highedge))
    projection.SetYTitle("counts")
    c.Modified()
    c.Update()
    c.Print("{0:s}.pdf".format(fname), 'Title:{0}'.format(pname))
    c.Clear()

    mean = projection.GetMean()
    rms = projection.GetStdDev()
    meanerr = projection.GetMeanError()
    if mean==0:
      resolution=0
      resolutionError=0
    else:
      resolution=rms/mean
      resolutionError=(projection.GetStdDev() * projection.GetMeanError()) / (projection.GetMean()*projection.GetMean())
    resolution_hists[top_path].SetBinContent(i, resolution)
    resolution_hists[top_path].SetBinError(i, resolutionError)

    for ratio_plot in [ratio_mean, ratio_mean_stddev, ratio_mean_meanerr]:
      ratio_plot.Fill(lowedge, mean)
    ratio_mean.SetBinError(i, 0.0)
    ratio_mean_stddev.SetBinError(i, rms)
    ratio_mean_meanerr.SetBinError(i, meanerr)
  # due to a bug, you need to close with the last title
  #       even though it was written correctly, otherwise it won't save right
  c.Print("{0:s}.pdf]".format(fname), 'Title:{0}'.format(pname))

  ratio_mean.SetLineColor(ROOT.kGray)
  ratio_mean_stddev.SetFillColorAlpha(ROOT.kBlue, 0.5)
  ratio_mean_meanerr.SetFillColorAlpha(ROOT.kRed, 1.0)
  ratio_mean_stddev.Draw("e5")
  ratio_mean_meanerr.Draw("e5 same")
  ratio_mean.GetXaxis().SetRange(0, ratio_mean.FindLastBinAbove(0))
  ratio_mean.Draw("c hist same")

  l = ROOT.TLegend(.7,.7,.9,.9)
  l.SetFillColor(0)
  l.SetShadowColor(10)
  l.SetLineColor(10)
  l.SetFillColor(10)
  l.SetFillStyle(0)
  l.SetBorderSize(0)

  l.AddEntry(ratio_mean, "Ratio", "lf")
  l.AddEntry(ratio_mean_meanerr, "Standard Dev of Mean","f")
  l.AddEntry(ratio_mean_stddev, "Standard Dev", "f")
  l.Draw()

  c.SetLogx()
  c.Modified()
  c.Update()
  c.Print("{0:s}_ratioMean.pdf".format(fname))
  c.SetLogx(0)
  c.Clear()

# RESOLUTION PLOTS

leg = ROOT.TLegend(.7,.7,.9,.9)
leg.SetFillColor(0)
leg.SetShadowColor(10)
leg.SetLineColor(10)
leg.SetFillColor(10)
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.AddEntry(resolution_hists['precalibration'], "Pre-calibration", "L")
leg.AddEntry(resolution_hists['postcalibration'], "Post-calibration", "L")

resolution_hists['precalibration'].GetXaxis().SetRange(0, resolution_hists['precalibration'].FindLastBinAbove(0))
resolution_hists['postcalibration'].GetXaxis().SetRange(0, resolution_hists['postcalibration'].FindLastBinAbove(0))
resolution_hists['precalibration'].GetXaxis().SetTitle("Uncalibrated isolated Offline Jet p_{T} [GeV]")
resolution_hists['postcalibration'].GetXaxis().SetTitle("Uncalibrated isolated Offline Jet p_{T} [GeV]")
resolution_hists['precalibration'].GetYaxis().SetTitle("#sigma/mean")
resolution_hists['postcalibration'].GetYaxis().SetTitle("#sigma/mean")

resolution_hists['precalibration'].Draw("c hist")
resolution_hists['postcalibration'].Draw("c hist same")
leg.Draw()
resolution_hists['postcalibration'].SetLineStyle(ROOT.kDashed)
resolution_hists['postcalibration'].SetLineColor(ROOT.kRed)
c.Modified()
c.Update()
c.Print("resolution.pdf")

resolution_hists['precalibration'].SetMinimum(0.01)
resolution_hists['postcalibration'].SetMinimum(0.01)
c.SetLogy(0)
c.SetLogx(1)
c.Modified()
c.Update()
c.Print("resolution_logx.pdf")
c.Clear()

# ETA PLOTS
oJet_pt_bins = ['0.000000_10.000000', '10.000000_20.000000', '50.000000_60.000000', '100.000000_110.000000', '200.000000_210.000000']
colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kViolet, ROOT.kOrange]
for top_path in top_paths:
  for name in oJet_pt_bins:
    stored_key = '_'.join([top_path, 'gBlockEtRatio_vs_eta', 'oJetPt_{0:s}'.format(name)])
    for dijet, scale in zip(dijets, scales): # Loops over files, colors, and scales respectively
      hists_cache.append(dijet.Get(os.path.join(top_path, 'gBlockEtRatio_vs_eta', 'oJetPt_{0:s}'.format(name))))
      hists_cache[-1].Scale(scale*35000000)
      if stored_key in hists:
        hists[stored_key].Add(hists_cache[-1])
      else:
        hists[stored_key] = hists_cache[-1].Clone()

for top_path in top_paths:
  l = ROOT.TLegend(.7,.7,.9,.9)
  l.SetFillColor(0)
  l.SetShadowColor(10)
  l.SetLineColor(10)
  l.SetFillColor(10)
  l.SetFillStyle(0)
  l.SetBorderSize(0)

  profiles = []
  icolor = itertools.cycle(colors)
  for name in oJet_pt_bins:
    stored_key = '_'.join([top_path, 'gBlockEtRatio_vs_eta', 'oJetPt_{0:s}'.format(name)])
    color = next(icolor)
    p = hists[stored_key].ProfileX("profilex").Clone()
    p.GetXaxis().SetTitle("Offline Jet #eta")
    p.GetYaxis().SetTitle("Mean of gBlock E_{T} / Offline p_{T}")
    p.SetTitle('{0:s}{1:s}'.format(top_path, p.GetTitle().replace("pre","").replace("post","").replace("calibration","")))
    p.SetMarkerColorAlpha(color, 0.5)
    p.SetLineColorAlpha(color, 0.5)
    p.SetFillColorAlpha(color, 0.5)
    p.SetMarkerSize(0.1)
    p.GetYaxis().SetRangeUser(0.0, 2.0)
    p.Draw("E4{0:s}".format("" if len(profiles)==0 else " same"))
    profiles.append(p)
    l.AddEntry(p, '{0:0.2f}-{1:0.2f} GeV'.format(*map(float,name.split('_'))), "lpf")

  l.Draw()
  c.Modified()
  c.Update()
  c.SetLogx(0)
  c.Print("{0:s}_gBlockEtRatio_vs_eta.pdf".format(top_path))
  c.Clear()

