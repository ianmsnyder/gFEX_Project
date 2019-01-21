from ROOT import TFile, TLegend, TCanvas, TGraphAsymmErrors, TH1F, TH2F, kPink, kMagenta, kViolet, kAzure, kRed, kBlack, kBlue, kGreen, kOrange




c= TCanvas()

# For Signal M = 800 Wprime -------------------------------------------------------------------------------------------------------------------------------------------

signal800 = TFile.Open("NoTowerCut.root")

# gTower .pdfs before cut

#m800_gTowerPt  = signal800.Get("gTowers/gtowerPt")
#m800_gTowerPt.SetTitle("gTower_pt")
#m800_gTowerPt.GetXaxis().SetTitle("pt")
#m800_gTowerPt.GetYaxis().SetTitle("number of gTowers")
#m800_gTowerPt.Draw("hist")
#c.SetLogy()
#c.Modified()
#c.Update
#c.Print("m800_gTowerPt.pdf")
#c.Clear()
del c

c = TCanvas()

# 2D histos

hist = signal800.Get("L1/G100_leading/numerator_gJet_v_OffJet_pT")
del c

c = TCanvas()

hist.Draw("hist")


c.Clear()
del c

c = TCanvas()

# Create Pass/Total Histos

print("Getting Numerator/Denominator Histos")
m800_L1_J100_num   = signal800.Get("L1/J100_leading/numerator")
#m800_L1_J100_num.Rebin(5)
m800_L1_J100_denom = signal800.Get("L1/J100_leading/denominator")
#m800_L1_J100_denom.Rebin(5)
m800_L1_G100_num   = signal800.Get("L1/G100_leading/numerator")
#m800_L1_G100_num.Rebin(5)
m800_L1_G100_denom = signal800.Get("L1/G100_leading/denominator")
#m800_L1_G100_denom.Rebin(5)
m800_L1_G140_num   = signal800.Get("L1/G140_leading/numerator")
#m800_L1_G140_num.Rebin(5)
m800_L1_G140_denom = signal800.Get("L1/G140_leading/denominator")
#m800_L1_G140_denom.Rebin(5)
m800_L1_G180_num   = signal800.Get("L1/G180_leading/numerator")
#m800_L1_G180_num.Rebin(5)
m800_L1_G180_denom = signal800.Get("L1/G180_leading/denominator")
#m800_L1_G180_denom.Rebin(5)

print("Getting Numerator/Denominator Histos higher cuts")
m800_L1_G200_num   = signal800.Get("L1/G200_leading/numerator")
#m800_L1_G200_num.Rebin(5)
m800_L1_G200_denom = signal800.Get("L1/G200_leading/denominator")
#m800_L1_G200_denom.Rebin(5)
m800_L1_G250_num   = signal800.Get("L1/G250_leading/numerator")
#m800_L1_G250_num.Rebin(5)
m800_L1_G250_denom = signal800.Get("L1/G250_leading/denominator")
#m800_L1_G250_denom.Rebin(5)
m800_L1_G300_num   = signal800.Get("L1/G300_leading/numerator")
#m800_L1_G300_num.Rebin(5)
m800_L1_G300_denom = signal800.Get("L1/G300_leading/denominator")
#m800_L1_G300_denom.Rebin(5)
m800_L1_G340_num   = signal800.Get("L1/G340_leading/numerator")
#m800_L1_G340_num.Rebin(5)
m800_L1_G340_denom = signal800.Get("L1/G340_leading/denominator")
#m800_L1_G340_denom.Rebin(5)

print("Getting Numerator/Denominator Histos with DeltaR Cuts")
cut_m800_L1_G100_num   = signal800.Get("L1/G100_leading/numerator_wDeltaRcut")
#cut_m800_L1_G100_num.Rebin(5)
cut_m800_L1_G100_denom = signal800.Get("L1/G100_leading/denominator_wDeltaRcut")
#cut_m800_L1_G100_denom.Rebin(5)
cut_m800_L1_G140_num   = signal800.Get("L1/G140_leading/numerator_wDeltaRcut")
#cut_m800_L1_G140_num.Rebin(5)
cut_m800_L1_G140_denom = signal800.Get("L1/G140_leading/denominator_wDeltaRcut")
#cut_m800_L1_G140_denom.Rebin(5)
cut_m800_L1_G180_num   = signal800.Get("L1/G180_leading/numerator_wDeltaRcut")
#cut_m800_L1_G180_num.Rebin(5)
cut_m800_L1_G180_denom = signal800.Get("L1/G180_leading/denominator_wDeltaRcut")
#cut_m800_L1_G180_denom.Rebin(5)

print("Getting Numerator/Denominator Histos with higher pT cuts and DeltaR Cuts")
cut_m800_L1_G200_num   = signal800.Get("L1/G200_leading/numerator_wDeltaRcut")
#cut_m800_L1_G200_num.Rebin(5)
cut_m800_L1_G200_denom = signal800.Get("L1/G200_leading/denominator_wDeltaRcut")
#cut_m800_L1_G200_denom.Rebin(5)
cut_m800_L1_G250_num   = signal800.Get("L1/G250_leading/numerator_wDeltaRcut")
#cut_m800_L1_G250_num.Rebin(5)
cut_m800_L1_G250_denom = signal800.Get("L1/G250_leading/denominator_wDeltaRcut")
#cut_m800_L1_G250_denom.Rebin(5)
cut_m800_L1_G300_num   = signal800.Get("L1/G300_leading/numerator_wDeltaRcut")
#cut_m800_L1_G300_num.Rebin(5)
cut_m800_L1_G300_denom = signal800.Get("L1/G300_leading/denominator_wDeltaRcut")
#cut_m800_L1_G300_denom.Rebin(5)
cut_m800_L1_G340_num   = signal800.Get("L1/G340_leading/numerator_wDeltaRcut")
#cut_m800_L1_G340_num.Rebin(5)
cut_m800_L1_G340_denom = signal800.Get("L1/G340_leading/denominator_wDeltaRcut")
#cut_m800_L1_G340_denom.Rebin(5)


# _wPileupCorrection

print("Getting Numerator/Denominator Histos with pileup correction")
pu_m800_L1_G100_num   = signal800.Get("L1/G100_leading/numerator_wPileupCorrection")
#pu_m800_L1_G100_num.Rebin(5)
pu_m800_L1_G140_num   = signal800.Get("L1/G140_leading/numerator_wPileupCorrection")
#pu_m800_L1_G140_num.Rebin(5)
pu_m800_L1_G180_num   = signal800.Get("L1/G180_leading/numerator_wPileupCorrection")
#pu_m800_L1_G180_num.Rebin(5)


print("Getting Numerator/Denominator Histos with pileup correction and deltaR cut")
pu_cut_m800_L1_G100_num   = signal800.Get("L1/G100_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G100_num.Rebin(5)
pu_cut_m800_L1_G140_num   = signal800.Get("L1/G140_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G140_num.Rebin(5)
pu_cut_m800_L1_G180_num   = signal800.Get("L1/G180_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G180_num.Rebin(5)

print("Getting Numerator/Denominator Histos with pileup correction at highter pT cuts")
pu_m800_L1_G200_num   = signal800.Get("L1/G200_leading/numerator_wPileupCorrection")
#pu_m800_L1_G200_num.Rebin(5)
pu_m800_L1_G200_denom = signal800.Get("L1/G200_leading/denominator")
#u_m800_L1_G200_denom.Rebin(5)
pu_m800_L1_G250_num   = signal800.Get("L1/G250_leading/numerator_wPileupCorrection")
#pu_m800_L1_G250_num.Rebin(5)
pu_m800_L1_G250_denom = signal800.Get("L1/G250_leading/denominator")
#u_m800_L1_G250_denom.Rebin(5)
pu_m800_L1_G300_num   = signal800.Get("L1/G300_leading/numerator_wPileupCorrection")
#pu_m800_L1_G300_num.Rebin(5)
pu_m800_L1_G300_denom = signal800.Get("L1/G300_leading/denominator")
#u_m800_L1_G300_denom.Rebin(5)
pu_m800_L1_G340_num   = signal800.Get("L1/G340_leading/numerator_wPileupCorrection")
#pu_m800_L1_G340_num.Rebin(5)
pu_m800_L1_G340_denom = signal800.Get("L1/G340_leading/denominator")
#u_m800_L1_G340_denom.Rebin(5)

print("Getting Numerator/Denominator Histos with pileup correction at higher pT cuts AND deltaR")
pu_cut_m800_L1_G200_num   = signal800.Get("L1/G200_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G200_num.Rebin(5)
pu_cut_m800_L1_G200_denom = signal800.Get("L1/G200_leading/denominator_wDeltaRcut")
#u_cut_m800_L1_G200_denom.Rebin(5)
pu_cut_m800_L1_G250_num   = signal800.Get("L1/G250_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G250_num.Rebin(5)
pu_cut_m800_L1_G250_denom = signal800.Get("L1/G250_leading/denominator_wDeltaRcut")
#u_cut_m800_L1_G250_denom.Rebin(5)
pu_cut_m800_L1_G300_num   = signal800.Get("L1/G300_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G300_num.Rebin(5)
pu_cut_m800_L1_G300_denom = signal800.Get("L1/G300_leading/denominator_wDeltaRcut")
#u_cut_m800_L1_G300_denom.Rebin(5)
pu_cut_m800_L1_G340_num   = signal800.Get("L1/G340_leading/numerator_wDeltaRcut_wPileupCorrection")
#pu_cut_m800_L1_G340_num.Rebin(5)
pu_cut_m800_L1_G340_denom = signal800.Get("L1/G340_leading/denominator_wDeltaRcut")
#u_cut_m800_L1_G340_denom.Rebin(5)


G200_1subjet_num   = signal800.Get("L1/G200/subjets/1subjet_num")
#G200_1subjet_num.Integrate(0, 31)
G200_2subjet_num   = signal800.Get("L1/G200/subjets/2subjet_num")
G200_3subjet_num   = signal800.Get("L1/G200/subjets/3subjet_num")

G200_1subjet_denom = signal800.Get("L1/G200/subjets/1subjet_denom")
G200_2subjet_denom = signal800.Get("L1/G200/subjets/2subjet_denom")
G200_3subjet_denom = signal800.Get("L1/G200/subjets/3subjet_denom")

J100_1subjet_num   = signal800.Get("L1/J100/subjets/1subjet_num")
J100_2subjet_num   = signal800.Get("L1/J100/subjets/2subjet_num")
J100_3subjet_num   = signal800.Get("L1/J100/subjets/3subjet_num")

J100_1subjet_denom = signal800.Get("L1/J100/subjets/1subjet_denom")
J100_2subjet_denom = signal800.Get("L1/J100/subjets/2subjet_denom")
J100_3subjet_denom = signal800.Get("L1/J100/subjets/3subjet_denom")

G200_1subjet_denomVal = G200_1subjet_denom.Integral(0, 31)
print("G200_1subjet_denomVal")
print(G200_1subjet_denomVal)

G200_1subjet_numVal   = G200_1subjet_num.Integral(0, 31)
print("G200_1subjet_numVal")
print(G200_1subjet_numVal)

G200_2subjet_denomVal = G200_2subjet_denom.Integral(0, 31) 
print("G200_2subjet_denomVal")
print(G200_2subjet_denomVal)

G200_2subjet_numVal   = G200_2subjet_num.Integral(0, 31)
print("G200_2subjet_numVal")
print(G200_2subjet_numVal)

G200_3subjet_denomVal = G200_3subjet_denom.Integral(0, 31) 
print("G200_3subjet_denomVal")
print(G200_3subjet_denomVal)

G200_3subjet_numVal   = G200_3subjet_num.Integral(0, 31)
print("G200_3subjet_numVal")
print(G200_3subjet_numVal)

J100_1subjet_denomVal  = J100_1subjet_denom.Integral(0, 31)
print("J100_1subjet_denomVal")
print(J100_1subjet_denomVal)

J100_1subjet_numVal    = J100_1subjet_num.Integral(0, 31)
print("J100_1subjet_numVal")
print(J100_1subjet_numVal)

J100_2subjet_denomVal  = J100_2subjet_denom.Integral(0, 31) 
print("J100_2subjet_denomVal")
print(J100_2subjet_denomVal)

J100_2subjet_numVal    = J100_2subjet_num.Integral(0, 31)
print("J100_2subjet_numVal")
print(J100_2subjet_numVal)

J100_3subjet_denomVal  = J100_3subjet_denom.Integral(0, 31) 
print("J100_3subjet_denomVal")
print(J100_3subjet_denomVal)


J100_3subjet_numVal    = J100_3subjet_num.Integral(0, 31)
print("J100_3subjet_numVal")
print(J100_3subjet_numVal)


c.Close
del c

c = TCanvas()
# Create Efficiency Plots
print("Subjet Plots")

G200_1subjet_effplot = TGraphAsymmErrors(G200_1subjet_num, G200_1subjet_denom, "cl=0.683 b(1,1) mode")
G200_2subjet_effplot = TGraphAsymmErrors(G200_2subjet_num, G200_2subjet_denom, "cl=0.683 b(1,1) mode")
G200_3subjet_effplot = TGraphAsymmErrors(G200_3subjet_num, G200_3subjet_denom, "cl=0.683 b(1,1) mode")

J100_1subjet_effplot = TGraphAsymmErrors(J100_1subjet_num, J100_1subjet_denom, "cl=0.683 b(1,1) mode")
J100_2subjet_effplot = TGraphAsymmErrors(J100_2subjet_num, J100_2subjet_denom, "cl=0.683 b(1,1) mode")
J100_3subjet_effplot = TGraphAsymmErrors(J100_3subjet_num, J100_3subjet_denom, "cl=0.683 b(1,1) mode")

G200_1subjet_effplot.SetTitle("Efficiency with Different # of Constituents")
G200_1subjet_effplot.SetMinimum(0.0)
G200_1subjet_effplot.GetXaxis().SetTitle("uncalibrated p_{T}^{Offline Jets} [GeV]")
G200_1subjet_effplot.GetYaxis().SetTitle("per-jet efficiency")
G200_1subjet_effplot.SetMarkerStyle(20)
G200_1subjet_effplot.SetMarkerColor(kBlue)
G200_1subjet_effplot.SetMarkerSize(.8)
G200_1subjet_effplot.SetLineColor(kBlue)
G200_1subjet_effplot.Draw("epa")
G200_2subjet_effplot.SetMarkerStyle(21)
G200_2subjet_effplot.SetMarkerColor(kBlue)
G200_2subjet_effplot.SetLineColor(kBlue)
G200_2subjet_effplot.SetMarkerSize(.8)
G200_2subjet_effplot.Draw("epsame")
G200_2subjet_effplot.SetMinimum(0.0)
G200_3subjet_effplot.SetMarkerStyle(22)
G200_3subjet_effplot.SetMarkerColor(kBlue)
G200_3subjet_effplot.SetLineColor(kBlue)
G200_3subjet_effplot.SetMarkerSize(.8)
G200_3subjet_effplot.Draw("epsame")
G200_3subjet_effplot.SetMinimum(0.0)


J100_1subjet_effplot.SetMarkerStyle(20)
J100_1subjet_effplot.SetMarkerColor(kRed)
J100_1subjet_effplot.SetMarkerSize(.8)
J100_1subjet_effplot.SetLineColor(kRed)
J100_1subjet_effplot.Draw("epsame")
J100_1subjet_effplot.SetMinimum(0.0)
J100_2subjet_effplot.SetMarkerStyle(21)
J100_2subjet_effplot.SetMarkerColor(kRed)
J100_2subjet_effplot.SetLineColor(kRed)
J100_2subjet_effplot.SetMinimum(0.0)
J100_2subjet_effplot.SetMarkerSize(.8)
J100_2subjet_effplot.Draw("epsame")
J100_3subjet_effplot.SetMarkerStyle(22)
J100_3subjet_effplot.SetMinimum(0.0)
J100_3subjet_effplot.SetMarkerColor(kRed)
J100_3subjet_effplot.SetLineColor(kRed)
J100_3subjet_effplot.SetMarkerSize(.8)
J100_3subjet_effplot.Draw("epsame")


c.Modified()
c.Update
c.Print("m800_subjetsPlots.pdf")
c.Clear


print("Efficiency Plots")
m800_effPlot_L1_G140 = TGraphAsymmErrors(m800_L1_G140_num, m800_L1_G140_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_J100 = TGraphAsymmErrors(m800_L1_J100_num, m800_L1_J100_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_G180 = TGraphAsymmErrors(m800_L1_G180_num, m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_G100 = TGraphAsymmErrors(m800_L1_G100_num, m800_L1_G100_denom, "cl=0.683 b(1,1) mode")

#binning issues here
print("Efficiency Plots with higher pT Cuts")

 
print(m800_L1_G200_num.GetXaxis().GetNbins())
print(m800_L1_G200_denom.GetXaxis().GetNbins())

m800_effPlot_L1_G200 = TGraphAsymmErrors(m800_L1_G200_num, m800_L1_G200_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_G250 = TGraphAsymmErrors(m800_L1_G250_num, m800_L1_G250_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_G300 = TGraphAsymmErrors(m800_L1_G300_num, m800_L1_G300_denom, "cl=0.683 b(1,1) mode")
m800_effPlot_L1_G340 = TGraphAsymmErrors(m800_L1_G340_num, m800_L1_G340_denom, "cl=0.683 b(1,1) mode")

cut_m800_effPlot_L1_G140 = TGraphAsymmErrors(cut_m800_L1_G140_num, cut_m800_L1_G140_denom, "cl=0.683 b(1,1) mode")
cut_m800_effPlot_L1_G180 = TGraphAsymmErrors(cut_m800_L1_G180_num, cut_m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
cut_m800_effPlot_L1_G100 = TGraphAsymmErrors(cut_m800_L1_G100_num, cut_m800_L1_G100_denom, "cl=0.683 b(1,1) mode")

cut_m800_effPlot_L1_G200 = TGraphAsymmErrors(cut_m800_L1_G200_num, cut_m800_L1_G200_denom, "cl=0.683 b(1,1) mode")
cut_m800_effPlot_L1_G250 = TGraphAsymmErrors(cut_m800_L1_G250_num, cut_m800_L1_G250_denom, "cl=0.683 b(1,1) mode")
cut_m800_effPlot_L1_G300 = TGraphAsymmErrors(cut_m800_L1_G300_num, cut_m800_L1_G300_denom, "cl=0.683 b(1,1) mode")
cut_m800_effPlot_L1_G340 = TGraphAsymmErrors(cut_m800_L1_G340_num, cut_m800_L1_G340_denom, "cl=0.683 b(1,1) mode")

#for pileup

print("Efficiency Plots with pileup correction")
pu_m800_effPlot_L1_G140 = TGraphAsymmErrors(pu_m800_L1_G140_num, m800_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_m800_effPlot_L1_G180 = TGraphAsymmErrors(pu_m800_L1_G180_num, m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_m800_effPlot_L1_G100 = TGraphAsymmErrors(pu_m800_L1_G100_num, m800_L1_G100_denom, "cl=0.683 b(1,1) mode")

print("Efficiency Plots with pileup correction at higher pT cuts")
pu_m800_effPlot_L1_G200 = TGraphAsymmErrors(pu_m800_L1_G200_num, m800_L1_G200_denom, "cl=0.683 b(1,1) mode")
pu_m800_effPlot_L1_G250 = TGraphAsymmErrors(pu_m800_L1_G250_num, m800_L1_G250_denom, "cl=0.683 b(1,1) mode")
pu_m800_effPlot_L1_G300 = TGraphAsymmErrors(pu_m800_L1_G300_num, m800_L1_G300_denom, "cl=0.683 b(1,1) mode")
pu_m800_effPlot_L1_G340 = TGraphAsymmErrors(pu_m800_L1_G340_num, m800_L1_G340_denom, "cl=0.683 b(1,1) mode")

print("Efficiency Plots with pileup correction AND deltaR cut")
pu_cut_m800_effPlot_L1_G140 = TGraphAsymmErrors(pu_cut_m800_L1_G140_num, cut_m800_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_cut_m800_effPlot_L1_G180 = TGraphAsymmErrors(pu_cut_m800_L1_G180_num, cut_m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_cut_m800_effPlot_L1_G100 = TGraphAsymmErrors(pu_cut_m800_L1_G100_num, cut_m800_L1_G100_denom, "cl=0.683 b(1,1) mode")

print("Efficiency Plots with pileup correction AND deltaR cut at higher pT cuts")
pu_cut_m800_effPlot_L1_G200 = TGraphAsymmErrors(pu_cut_m800_L1_G200_num, cut_m800_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_cut_m800_effPlot_L1_G250 = TGraphAsymmErrors(pu_cut_m800_L1_G250_num, cut_m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_cut_m800_effPlot_L1_G300 = TGraphAsymmErrors(pu_cut_m800_L1_G300_num, cut_m800_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_cut_m800_effPlot_L1_G340 = TGraphAsymmErrors(pu_cut_m800_L1_G340_num, cut_m800_L1_G100_denom, "cl=0.683 b(1,1) mode")

WithTowerCut = TFile.Open("WithTowerCut.root")
NoTowerCut = TFile.Open("NoTowerCut.root")

# Draw pT overlay

m800_gJetPt          = NoTowerCut.Get("trigger/gjetPt")
m800_gJetPtCorrected = NoTowerCut.Get("trigger/gjet_pTcorrected")

m800_gJetPt.SetTitle("gJet pT")
m800_gJetPt.GetXaxis().SetTitle("gJet pT [GeV]")
#m800_gJetPt.GetYaxis().SetTitle("number of gJets")
m800_gJetPt.SetLineColor(kBlue)
m800_gJetPtCorrected.SetLineColor(kRed)
m800_gJetPt.Draw("hist")
m800_gJetPtCorrected.Draw("hist same")
c.Modified()
c.Update
c.Print("gJetPt_m800_overlay.pdf")
c.Clear

# Draw Rho Plots

m800_rho_withCut = WithTowerCut.Get("trigger/gjet_rho")
m800_rho_noCut   = NoTowerCut.Get("trigger/gjet_rho")

m800_rho_noCut.SetTitle("Median Rho per Event")
m800_rho_noCut.GetXaxis().SetTitle("Rho [GeV/Area]")
m800_rho_noCut.GetYaxis().SetTitle("# of Events")
m800_rho_withCut.SetLineColor(kRed)
m800_rho_noCut.SetLineColor(kBlue)
m800_rho_noCut.Draw("hist")
m800_rho_withCut.Draw("hist same")

c.Modified()
c.Update
c.Print("rho_m800_effPlots.pdf")
c.Clear


# Draw Efficiency Plots

m800_effPlot_L1_J100.SetTitle("Efficiency")
m800_effPlot_L1_J100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_effPlot_L1_J100.GetYaxis().SetTitle("Efficiency")

m800_effPlot_L1_G100.SetMarkerColor(kRed)
m800_effPlot_L1_G100.SetLineColor(kRed)
m800_effPlot_L1_G140.SetMarkerColor(kOrange)
m800_effPlot_L1_G140.SetLineColor(kOrange)
m800_effPlot_L1_G180.SetMarkerColor(kGreen)
m800_effPlot_L1_G180.SetLineColor(kGreen)
m800_effPlot_L1_J100.SetMarkerColor(kBlue)
m800_effPlot_L1_J100.SetLineColor(kBlue)

m800_effPlot_L1_G200.SetMarkerColor(kPink+10)
m800_effPlot_L1_G200.SetLineColor(kPink+10)
m800_effPlot_L1_G250.SetMarkerColor(kMagenta+3)
m800_effPlot_L1_G250.SetLineColor(kMagenta+3)
m800_effPlot_L1_G300.SetMarkerColor(kViolet+1)
m800_effPlot_L1_G300.SetLineColor(kViolet+1)
m800_effPlot_L1_G340.SetMarkerColor(kAzure+10)
m800_effPlot_L1_G340.SetLineColor(kAzure+10)

m800_effPlot_L1_J100.Draw("epa")
m800_effPlot_L1_G100.Draw("epsame")
m800_effPlot_L1_G140.Draw("epsame")
m800_effPlot_L1_G180.Draw("epsame")
c.Modified()
c.Update
c.Print("leading_m800_effPlots.pdf")
c.Clear 

m800_effPlot_L1_J100.Draw("epa")
m800_effPlot_L1_G200.Draw("epsame")
m800_effPlot_L1_G250.Draw("epsame")
m800_effPlot_L1_G300.Draw("epsame")
m800_effPlot_L1_G340.Draw("epsame")


c.Modified()
c.Update
c.Print("leading_m800_effPlots_more.pdf")
c.Clear

m800_effPlot_L1_J100.SetTitle("Efficiency with DeltaR Cut < 1.0")
m800_effPlot_L1_J100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_effPlot_L1_J100.GetYaxis().SetTitle("Efficiency")

cut_m800_effPlot_L1_G100.SetMarkerColor(kRed)
cut_m800_effPlot_L1_G100.SetLineColor(kRed)
cut_m800_effPlot_L1_G140.SetMarkerColor(kOrange)
cut_m800_effPlot_L1_G140.SetLineColor(kOrange)
cut_m800_effPlot_L1_G180.SetMarkerColor(kGreen)
cut_m800_effPlot_L1_G180.SetLineColor(kGreen)
m800_effPlot_L1_J100.SetMarkerColor(kBlue)
m800_effPlot_L1_J100.SetLineColor(kBlue)

cut_m800_effPlot_L1_G200.SetMarkerColor(kPink+10)
cut_m800_effPlot_L1_G200.SetLineColor(kPink+10)
cut_m800_effPlot_L1_G250.SetMarkerColor(kMagenta+3)
cut_m800_effPlot_L1_G250.SetLineColor(kMagenta+3)
cut_m800_effPlot_L1_G300.SetMarkerColor(kViolet+1)
cut_m800_effPlot_L1_G300.SetLineColor(kViolet+1)
cut_m800_effPlot_L1_G340.SetMarkerColor(kAzure+10)
cut_m800_effPlot_L1_G340.SetLineColor(kAzure+10)

m800_effPlot_L1_J100.Draw("epa")
cut_m800_effPlot_L1_G100.Draw("epsame")
cut_m800_effPlot_L1_G140.Draw("epsame")
cut_m800_effPlot_L1_G180.Draw("epsame")

c.Modified()
c.Update
c.Print("leading_cut_m800_effPlots.pdf")
c.Clear

m800_effPlot_L1_J100.Draw("epa")
cut_m800_effPlot_L1_G200.Draw("epsame")
cut_m800_effPlot_L1_G250.Draw("epsame")
cut_m800_effPlot_L1_G300.Draw("epsame")
cut_m800_effPlot_L1_G340.Draw("epsame")


c.Modified()
c.Update
c.Print("leading_cut_m800_effPlots_more.pdf")
c.Clear


del c

c = TCanvas()

c.SetLogy()
c.SetTitle("Offline Jets pT for Different Cuts, W' = 800 GeV")

m800_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_L1_G140_num.GetYaxis().SetTitle("number of Offline Jets") 
m800_L1_G100_num.SetMarkerColor(kRed)
m800_L1_G100_num.SetLineColor(kRed)
m800_L1_G140_num.SetMarkerColor(kOrange)
m800_L1_G140_num.SetLineColor(kOrange)
m800_L1_G180_num.SetMarkerColor(kGreen)
m800_L1_G180_num.SetLineColor(kGreen)
m800_L1_J100_num.SetMarkerColor(kBlue)
m800_L1_J100_num.SetMarkerColor(kBlue)
m800_L1_G140_num.Draw("hist")
m800_L1_G140_num.SetTitle("Offline Jets pT for different cuts, W' Signal, m = 800 GeV")
m800_L1_G180_denom.SetMarkerColor(kBlack)
m800_L1_G180_denom.SetLineColor(kBlack)
m800_L1_G180_denom.Draw("histsame")
m800_L1_G180_num.Draw("histsame")
m800_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m800_numPlots_L1_G100_G140_G180.pdf")

c.Clear


cut_m800_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
cut_m800_L1_G140_num.GetYaxis().SetTitle("number of Offline Jets")
cut_m800_L1_G100_num.SetMarkerColor(kRed)
cut_m800_L1_G100_num.SetLineColor(kRed)
cut_m800_L1_G140_num.SetMarkerColor(kOrange)
cut_m800_L1_G140_num.SetLineColor(kOrange)
cut_m800_L1_G180_num.SetMarkerColor(kGreen)
cut_m800_L1_G180_num.SetLineColor(kGreen)
cut_m800_L1_G140_num.Draw("hist")
cut_m800_L1_G140_num.SetTitle("Offline Jets pT for different cuts, W' Signal, m = 800 GeV")
cut_m800_L1_G180_denom.SetMarkerColor(kBlack)
cut_m800_L1_G180_denom.SetLineColor(kBlack)
cut_m800_L1_G180_denom.Draw("histsame")
cut_m800_L1_G180_num.Draw("histsame")
cut_m800_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m800_cut_numPlots_L1_G100_G140_G180.pdf")

c.Clear

m800_L1_J100_num.SetMarkerColor(kBlue)
m800_L1_J100_num.SetLineColor(kBlue)
m800_L1_J100_denom.SetMarkerColor(kBlack)
m800_L1_J100_denom.SetLineColor(kBlack)
m800_L1_J100_num.Draw("hist")
m800_L1_J100_num.SetTitle("Numerator/Denominator for Run2 L1 jet pT, 100 GeV cut")
m800_L1_J100_denom.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m800_numPlots_L1_J100.pdf")

c.Close()
del c

c = TCanvas()


c.Close()
del c

c = TCanvas()

#pu_m800_effPlot_L1_G100.SetTitle("Efficiency")
#pu_m800_effPlot_L1_G100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
#pu_m800_effPlot_L1_G100.GetYaxis().SetTitle("Efficiency")
#pu_m800_effPlot_L1_G100.SetMarkerColor(kRed)
#pu_m800_effPlot_L1_G100.SetLineColor(kRed)
#pu_m800_effPlot_L1_G140.SetMarkerColor(kOrange)
#pu_m800_effPlot_L1_G140.SetLineColor(kOrange)
#pu_m800_effPlot_L1_G180.SetMarkerColor(kGreen)
#pu_m800_effPlot_L1_G180.SetLineColor(kGreen)
#pu_m800_effPlot_L1_G100.Draw("epa")
#pu_m800_effPlot_L1_G140.Draw("epsame")
#pu_m800_effPlot_L1_G180.Draw("epsame")
#c.Modified()
#c.Update
#c.Print("pu_leading_m800_effPlots.pdf")

#c.Clear

m800_effPlot_L1_J100.SetTitle("Efficiency")
m800_effPlot_L1_J100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_effPlot_L1_J100.GetYaxis().SetTitle("Efficiency")
pu_m800_effPlot_L1_G100.SetMarkerColor(kRed-3)
pu_m800_effPlot_L1_G100.SetMarkerStyle(20)
pu_m800_effPlot_L1_G140.SetMarkerStyle(20)
pu_m800_effPlot_L1_G180.SetMarkerStyle(20)
pu_m800_effPlot_L1_G100.SetMarkerSize(.5)
pu_m800_effPlot_L1_G140.SetMarkerSize(.5)
pu_m800_effPlot_L1_G180.SetMarkerSize(.5)
pu_m800_effPlot_L1_G100.SetLineColor(kRed)
pu_m800_effPlot_L1_G140.SetMarkerColor(kOrange-3)
pu_m800_effPlot_L1_G140.SetLineColor(kOrange)
pu_m800_effPlot_L1_G180.SetMarkerColor(kGreen+2)
pu_m800_effPlot_L1_G180.SetLineColor(kGreen)

m800_effPlot_L1_J100.SetMarkerColor(kBlue)
m800_effPlot_L1_J100.SetLineColor(kBlue)
m800_effPlot_L1_J100.SetMarkerStyle(20)
m800_effPlot_L1_J100.SetMarkerSize(.5)

pu_m800_effPlot_L1_G200.SetMarkerStyle(20)
pu_m800_effPlot_L1_G250.SetMarkerStyle(20)
pu_m800_effPlot_L1_G300.SetMarkerStyle(20)
pu_m800_effPlot_L1_G340.SetMarkerStyle(20)

pu_m800_effPlot_L1_G200.SetMarkerSize(.5)
pu_m800_effPlot_L1_G250.SetMarkerSize(.5)
pu_m800_effPlot_L1_G300.SetMarkerSize(.5)
pu_m800_effPlot_L1_G340.SetMarkerSize(.5)

pu_m800_effPlot_L1_G200.SetMarkerColor(kPink+10)
pu_m800_effPlot_L1_G200.SetLineColor(kPink+10)
pu_m800_effPlot_L1_G250.SetMarkerColor(kMagenta+3)
pu_m800_effPlot_L1_G250.SetLineColor(kMagenta+3)
pu_m800_effPlot_L1_G300.SetMarkerColor(kViolet+1)
pu_m800_effPlot_L1_G300.SetLineColor(kViolet+1)
pu_m800_effPlot_L1_G340.SetMarkerColor(kAzure+10)
pu_m800_effPlot_L1_G340.SetLineColor(kAzure+10)

m800_effPlot_L1_J100.Draw("epa")
pu_m800_effPlot_L1_G100.Draw("epsame")
pu_m800_effPlot_L1_G140.Draw("epsame")
pu_m800_effPlot_L1_G180.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m800_effPlots.pdf")
c.Clear

m800_effPlot_L1_J100.Draw("epa")
pu_m800_effPlot_L1_G200.Draw("epsame")
pu_m800_effPlot_L1_G250.Draw("epsame")
pu_m800_effPlot_L1_G340.Draw("epsame")
pu_m800_effPlot_L1_G300.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m800_effPlots_more.pdf")
c.Clear

c.Close()
del c
c = TCanvas()

pu_cut_m800_effPlot_L1_G100.SetTitle("Efficiency with cut on deltaR < 1.0")
pu_cut_m800_effPlot_L1_G100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
pu_cut_m800_effPlot_L1_G100.GetYaxis().SetTitle("Efficiency")
pu_cut_m800_effPlot_L1_G100.SetMarkerColor(kRed-3)
pu_cut_m800_effPlot_L1_G100.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G140.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G180.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G100.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G140.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G180.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G100.SetLineColor(kRed)
pu_cut_m800_effPlot_L1_G140.SetMarkerColor(kOrange-3)
pu_cut_m800_effPlot_L1_G140.SetLineColor(kOrange)
pu_cut_m800_effPlot_L1_G180.SetMarkerColor(kGreen+2)
pu_cut_m800_effPlot_L1_G180.SetLineColor(kGreen)

m800_effPlot_L1_J100.SetMarkerColor(kBlue)
m800_effPlot_L1_J100.SetLineColor(kBlue)
m800_effPlot_L1_J100.SetMarkerStyle(20)
m800_effPlot_L1_J100.SetMarkerSize(.5)

pu_cut_m800_effPlot_L1_G200.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G250.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G300.SetMarkerStyle(20)
pu_cut_m800_effPlot_L1_G340.SetMarkerStyle(20)

pu_cut_m800_effPlot_L1_G200.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G250.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G300.SetMarkerSize(.5)
pu_cut_m800_effPlot_L1_G340.SetMarkerSize(.5)

pu_cut_m800_effPlot_L1_G200.SetMarkerColor(kPink+10)
pu_cut_m800_effPlot_L1_G200.SetLineColor(kPink+10)
pu_cut_m800_effPlot_L1_G250.SetMarkerColor(kMagenta+3)
pu_cut_m800_effPlot_L1_G250.SetLineColor(kMagenta+3)
pu_cut_m800_effPlot_L1_G300.SetMarkerColor(kViolet+1)
pu_cut_m800_effPlot_L1_G300.SetLineColor(kViolet+1)
pu_cut_m800_effPlot_L1_G340.SetMarkerColor(kAzure+10)
pu_cut_m800_effPlot_L1_G340.SetLineColor(kAzure+10)

m800_effPlot_L1_J100.SetTitle("Efficiency with cut on deltaR < 1.0")
m800_effPlot_L1_J100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_effPlot_L1_J100.GetYaxis().SetTitle("Efficiency")
m800_effPlot_L1_J100.Draw("epa")
pu_cut_m800_effPlot_L1_G100.Draw("epsame")
pu_cut_m800_effPlot_L1_G140.Draw("epsame")
pu_cut_m800_effPlot_L1_G180.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m800_cut_effPlots.pdf")
c.Clear

#m800_effPlot_L1_J100.Draw("epa")
#pu_cut_m800_effPlot_L1_G200.Draw("epsame")

m800_effPlot_L1_J100.SetTitle("Efficiency with DeltaR Cut < 1.0")
m800_effPlot_L1_J100.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m800_effPlot_L1_J100.GetYaxis().SetTitle("Efficiency")
m800_effPlot_L1_J100.Draw("epa")
pu_cut_m800_effPlot_L1_G200.Draw("epsame")
pu_cut_m800_effPlot_L1_G250.Draw("epsame")
pu_cut_m800_effPlot_L1_G340.Draw("epsame")
pu_cut_m800_effPlot_L1_G300.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m800_cut_effPlots_more.pdf")
c.Clear



c.Clear
c.Close()
del c
c = TCanvas()

# For Signal M = 3000, Wprime -----------------------------------------------------------------------------------------------------------------------------------------
signal3000 = TFile.Open("hist.cylin.L1CaloSimu.Wprime_WZqqqq_m3000.tag-00-00-17_OUTPUT.root")

# gTower .pdfs before cut

m3000_gTowerPt  = signal3000.Get("gTowers/gtowerPt")
c.SetLogy()
c.Modified()
c.Update
c.Print("m3000_gTowerPt.pdf")
c.Clear()

del c

c = TCanvas()
m3000_cut_gTowerPt  = signal3000.Get("gTowers/gtowerPt")
m3000_cut_gTowerPt.SetTitle("gTower_pt")
m3000_cut_gTowerPt.GetXaxis().SetTitle("pt")
m3000_cut_gTowerPt.GetYaxis().SetTitle("number of gTowers")
m3000_cut_gTowerPt.Draw("hist")
c.SetLogy()
c.Modified()
c.Update
c.Print("m3000_cut_gTowerPt.pdf")
c.Clear()

del c

c = TCanvas()

# Create Pass/Total Histos

m3000_L1_G140_num   = signal3000.Get("L1/G140_leading/numerator")
m3000_L1_G140_num.Rebin(4)
m3000_L1_G140_denom = signal3000.Get("L1/G140_leading/denominator")
m3000_L1_G140_denom.Rebin(4)
m3000_L1_J100_num   = signal3000.Get("L1/J100_leading/numerator")
m3000_L1_J100_num.Rebin(4)
m3000_L1_J100_denom = signal3000.Get("L1/J100_leading/denominator")
m3000_L1_J100_denom.Rebin(4)
m3000_L1_G180_num   = signal3000.Get("L1/G180_leading/numerator")
m3000_L1_G180_num.Rebin(4)
m3000_L1_G180_denom = signal3000.Get("L1/G180_leading/denominator")
m3000_L1_G180_denom.Rebin(4)
m3000_L1_G100_num   = signal3000.Get("L1/G100_leading/numerator")
m3000_L1_G100_num.Rebin(4)
m3000_L1_G100_denom = signal3000.Get("L1/G100_leading/denominator")
m3000_L1_G100_denom.Rebin(4)


cut_m3000_L1_G140_num   = signal3000.Get("L1/G140_leading/numerator_wDeltaRcut")
cut_m3000_L1_G140_num.Rebin(4)
cut_m3000_L1_G140_denom = signal3000.Get("L1/G140_leading/denominator_wDeltaRcut")
cut_m3000_L1_G140_denom.Rebin(4)
cut_m3000_L1_G180_num   = signal3000.Get("L1/G180_leading/numerator_wDeltaRcut")
cut_m3000_L1_G180_num.Rebin(4)
cut_m3000_L1_G180_denom = signal3000.Get("L1/G180_leading/denominator_wDeltaRcut")
cut_m3000_L1_G180_denom.Rebin(4)
cut_m3000_L1_G100_num   = signal3000.Get("L1/G100_leading/numerator_wDeltaRcut")
cut_m3000_L1_G100_num.Rebin(4)
cut_m3000_L1_G100_denom = signal3000.Get("L1/G100_leading/denominator_wDeltaRcut")
cut_m3000_L1_G100_denom.Rebin(4)

# For pileup

pu_m3000_L1_G100_num   = signal3000.Get("L1/G100_leading/numerator_wPileupCorrection")
pu_m3000_L1_G100_num.Rebin(4)
pu_m3000_L1_G140_num   = signal3000.Get("L1/G140_leading/numerator_wPileupCorrection")
pu_m3000_L1_G140_num.Rebin(4)
pu_m3000_L1_G180_num   = signal3000.Get("L1/G180_leading/numerator_wPileupCorrection")
pu_m3000_L1_G180_num.Rebin(4)

pu_cut_m3000_L1_G100_num   = signal3000.Get("L1/G100_leading/numerator_wDeltaRcut_wPileupCorrection")
pu_cut_m3000_L1_G100_num.Rebin(4)
pu_cut_m3000_L1_G140_num   = signal3000.Get("L1/G140_leading/numerator_wDeltaRcut_wPileupCorrection")
pu_cut_m3000_L1_G140_num.Rebin(4)
pu_cut_m3000_L1_G180_num   = signal3000.Get("L1/G180_leading/numerator_wDeltaRcut_wPileupCorrection")
pu_cut_m3000_L1_G180_num.Rebin(4)


c.Close()
del c

c = TCanvas()
# Create Efficiency Plots

m3000_effPlot_L1_G140 = TGraphAsymmErrors(m3000_L1_G140_num, m3000_L1_G140_denom, "cl=0.683 b(1,1) mode")
m3000_effPlot_L1_J100 = TGraphAsymmErrors(m3000_L1_J100_num, m3000_L1_J100_denom, "cl=0.683 b(1,1) mode")
m3000_effPlot_L1_G180 = TGraphAsymmErrors(m3000_L1_G180_num, m3000_L1_G180_denom, "cl=0.683 b(1,1) mode")
m3000_effPlot_L1_G100 = TGraphAsymmErrors(m3000_L1_G100_num, m3000_L1_G100_denom, "cl=0.683 b(1,1) mode")



cut_m3000_effPlot_L1_G140 = TGraphAsymmErrors(cut_m3000_L1_G140_num, cut_m3000_L1_G140_denom, "cl=0.683 b(1,1) mode")
cut_m3000_effPlot_L1_G180 = TGraphAsymmErrors(cut_m3000_L1_G180_num, cut_m3000_L1_G180_denom, "cl=0.683 b(1,1) mode")
cut_m3000_effPlot_L1_G100 = TGraphAsymmErrors(cut_m3000_L1_G100_num, cut_m3000_L1_G100_denom, "cl=0.683 b(1,1) mode")


pu_m3000_effPlot_L1_G140 = TGraphAsymmErrors(pu_m3000_L1_G140_num, m3000_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_m3000_effPlot_L1_G180 = TGraphAsymmErrors(pu_m3000_L1_G180_num, m3000_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_m3000_effPlot_L1_G100 = TGraphAsymmErrors(pu_m3000_L1_G100_num, m3000_L1_G100_denom, "cl=0.683 b(1,1) mode")


pu_cut_m3000_effPlot_L1_G140 = TGraphAsymmErrors(pu_cut_m3000_L1_G140_num, cut_m3000_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_cut_m3000_effPlot_L1_G180 = TGraphAsymmErrors(pu_cut_m3000_L1_G180_num, cut_m3000_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_cut_m3000_effPlot_L1_G100 = TGraphAsymmErrors(pu_cut_m3000_L1_G100_num, cut_m3000_L1_G100_denom, "cl=0.683 b(1,1) mode")


# Draw Efficiency Plots


m3000_effPlot_L1_G140.SetTitle("Efficiency")
m3000_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m3000_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
m3000_effPlot_L1_G100.SetMarkerColor(kRed)
m3000_effPlot_L1_G100.SetLineColor(kRed)
m3000_effPlot_L1_G140.SetMarkerColor(kOrange)
m3000_effPlot_L1_G140.SetLineColor(kOrange)
m3000_effPlot_L1_G180.SetMarkerColor(kGreen)
m3000_effPlot_L1_G180.SetLineColor(kGreen)
m3000_effPlot_L1_J100.SetMarkerColor(kBlue)
m3000_effPlot_L1_J100.SetMarkerColor(kBlue)
m3000_effPlot_L1_G140.Draw("epa")
m3000_effPlot_L1_J100.Draw("epsame")
m3000_effPlot_L1_G180.Draw("epsame")
m3000_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("leading_m3000_effPlots_L1_G100_G140_G180_J100.pdf")
c.Clear


cut_m3000_effPlot_L1_G140.SetTitle("Efficiency with cut on deltaR < 1.0")
cut_m3000_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
cut_m3000_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
cut_m3000_effPlot_L1_G100.SetMarkerColor(kRed)
cut_m3000_effPlot_L1_G100.SetLineColor(kRed)
cut_m3000_effPlot_L1_G140.SetMarkerColor(kOrange)
cut_m3000_effPlot_L1_G140.SetLineColor(kOrange)
cut_m3000_effPlot_L1_G180.SetMarkerColor(kGreen)
cut_m3000_effPlot_L1_G180.SetLineColor(kGreen)
cut_m3000_effPlot_L1_G140.Draw("epa")
cut_m3000_effPlot_L1_G180.Draw("epsame")
cut_m3000_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("leading_m3000_cut_effPlots_L1_G100_G140_G180.pdf")
c.Clear


c.SetLogy()
c.SetTitle("Offline Jets pT for Different Cuts, W' = 3000 GeV")
m3000_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
m3000_L1_G140_num.GetYaxis().SetTitle("Efficiency")
m3000_L1_G100_num.SetMarkerColor(kRed)
m3000_L1_G100_num.SetLineColor(kRed)
m3000_L1_G140_num.SetMarkerColor(kOrange)
m3000_L1_G140_num.SetLineColor(kOrange)
m3000_L1_G180_num.SetMarkerColor(kGreen)
m3000_L1_G180_num.SetLineColor(kGreen)
m3000_L1_J100_num.SetMarkerColor(kBlue)
m3000_L1_J100_num.SetMarkerColor(kBlue)
m3000_L1_G140_num.Draw("hist")
m3000_L1_G140_num.SetTitle("Offline Jets pT for different cuts, W' = 3000 GeV")
m3000_L1_G180_denom.SetMarkerColor(kBlack)
m3000_L1_G180_denom.SetLineColor(kBlack)
m3000_L1_G180_denom.Draw("histsame")
m3000_L1_G180_num.Draw("histsame")
m3000_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m3000_numPlots_L1_G100_G140_G180.pdf")

c.Clear


c.SetLogy()
c.SetTitle("Offline Jets pT for Different Cuts, W' = 3000 GeV")
cut_m3000_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
cut_m3000_L1_G140_num.GetYaxis().SetTitle("Efficiency")
cut_m3000_L1_G100_num.SetMarkerColor(kRed)
cut_m3000_L1_G100_num.SetLineColor(kRed)
cut_m3000_L1_G140_num.SetMarkerColor(kOrange)
cut_m3000_L1_G140_num.SetLineColor(kOrange)
cut_m3000_L1_G180_num.SetMarkerColor(kGreen)
cut_m3000_L1_G180_num.SetLineColor(kGreen)
cut_m3000_L1_G140_num.Draw("hist")
cut_m3000_L1_G140_num.SetTitle("Offline Jets pT for different cuts, W' = 3000 GeV")
cut_m3000_L1_G180_denom.SetMarkerColor(kBlack)
cut_m3000_L1_G180_denom.SetLineColor(kBlack)
cut_m3000_L1_G180_denom.Draw("histsame")
cut_m3000_L1_G180_num.Draw("histsame")
cut_m3000_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m3000_cut_numPlots_L1_G100_G140_G180.pdf")

c.Clear


c.Close()
del c

c = TCanvas()

# For Pileup Correction

pu_m3000_effPlot_L1_G140.SetTitle("Efficiency")
pu_m3000_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
pu_m3000_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
pu_m3000_effPlot_L1_G100.SetMarkerColor(kRed)
pu_m3000_effPlot_L1_G100.SetLineColor(kRed)
pu_m3000_effPlot_L1_G140.SetMarkerColor(kOrange)
pu_m3000_effPlot_L1_G140.SetLineColor(kOrange)
pu_m3000_effPlot_L1_G180.SetMarkerColor(kGreen)
pu_m3000_effPlot_L1_G180.SetLineColor(kGreen)
pu_m3000_effPlot_L1_G140.Draw("epa")
pu_m3000_effPlot_L1_G180.Draw("epsame")
pu_m3000_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m3000_effPlots_L1_G100_G140_G180.pdf")
c.Clear

c.Close()
del c
c = TCanvas()

pu_cut_m3000_effPlot_L1_G140.SetTitle("Efficiency")
pu_cut_m3000_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
pu_cut_m3000_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
pu_cut_m3000_effPlot_L1_G100.SetMarkerColor(kRed)
pu_cut_m3000_effPlot_L1_G100.SetLineColor(kRed)
pu_cut_m3000_effPlot_L1_G140.SetMarkerColor(kOrange)
pu_cut_m3000_effPlot_L1_G140.SetLineColor(kOrange)
pu_cut_m3000_effPlot_L1_G180.SetMarkerColor(kGreen)
pu_cut_m3000_effPlot_L1_G180.SetLineColor(kGreen)
pu_cut_m3000_effPlot_L1_G140.Draw("epa")
pu_cut_m3000_effPlot_L1_G180.Draw("epsame")
pu_cut_m3000_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_m3000_cut_effPlots_L1_G100_G140_G180.pdf")
c.Clear


m3000_L1_J100_num.SetMarkerColor(kBlue)
m3000_L1_J100_num.SetLineColor(kBlue)
m3000_L1_J100_denom.SetMarkerColor(kBlack)
m3000_L1_J100_denom.SetLineColor(kBlack)
m3000_L1_J100_num.Draw("hist")
m3000_L1_J100_num.SetTitle("Numerator/Denominator for Run2 L1 jet pT, 100 GeV cut")
m3000_L1_J100_denom.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_m3000_numPlots_L1_J100.pdf")



c.Close()
del c

c = TCanvas()

# For QCD Multijet Background Samples: --------------------------------------------------------------------------------------------------------------------------------
# Load the JZX Files:

scales = [
  78420000*1.0240E+00/1999400,
  78420000*6.7198E-04/1999000,
  2433200*3.3264E-04/1994600,
  26454*3.1963E-04/7884500,
  254.63*5.2982E-04/7979800,
  4.5535*9.2255E-04/7981600
]


#Declare the pass/total histograms
dijet_L1_G140_num = TH1F("numerator1",'',1000,0.,3000.)
dijet_L1_G140_denom = TH1F("denominator1",'',1000,0.,3000.)
dijet_L1_J100_num = TH1F("numerator2",'',1000,0.,3000.)
dijet_L1_J100_denom = TH1F("denominator2",'',1000,0.,3000.)
dijet_L1_G180_num = TH1F("numerator3", '', 1000,0.,3000.)
dijet_L1_G180_denom = TH1F("denominator3", '', 1000, 0., 3000.)
dijet_L1_G100_num = TH1F("numerator", '', 1000, 0., 3000.)
dijet_L1_G100_denom = TH1F("denominator", '', 1000, 0., 3000.)

cut_dijet_L1_G140_num = TH1F("numerator1c",'',1000,0.,3000.)
cut_dijet_L1_G140_denom = TH1F("denominator1c",'',1000,0.,3000.)
cut_dijet_L1_G180_num = TH1F("numerator3c", '', 1000,0.,3000.)
cut_dijet_L1_G180_denom = TH1F("denominator3c", '', 1000, 0., 3000.)
cut_dijet_L1_G100_num = TH1F("numeratorc", '', 1000, 0., 3000.)
cut_dijet_L1_G100_denom = TH1F("denominatorc", '', 1000, 0., 3000.)



pu_dijet_L1_G140_num = TH1F("numerator1_pu",'',1000,0.,3000.)
pu_dijet_L1_G140_denom = TH1F("denominator1_pu",'',1000,0.,3000.)
pu_dijet_L1_G180_num = TH1F("numerator3_pu", '', 1000,0.,3000.)
pu_dijet_L1_G180_denom = TH1F("denominator3_pu", '', 1000, 0., 3000.)
pu_dijet_L1_G100_num = TH1F("numerator_pu", '', 1000, 0., 3000.)
pu_dijet_L1_G100_denom = TH1F("denominator_pu", '', 1000, 0., 3000.)


pu_cut_dijet_L1_G140_num = TH1F("numerator1c_pu",'',1000,0.,3000.)
pu_cut_dijet_L1_G140_denom = TH1F("denominator1c_pu",'',1000,0.,3000.)
pu_cut_dijet_L1_G180_num = TH1F("numerator3c_pu", '', 1000,0.,3000.)
pu_cut_dijet_L1_G180_denom = TH1F("denominator3c_pu", '', 1000, 0., 3000.)
pu_cut_dijet_L1_G100_num = TH1F("numeratorc_pu", '', 1000, 0., 3000.)
pu_cut_dijet_L1_G100_denom = TH1F("denominatorc_pu", '', 1000, 0., 3000.)


Hist_DeltaR = TH2F("DeltaR_v_pT", "Offline Jet pT versus DeltaR", 1000, 0., 3000., 100, 0., 10.)
Hist_pT     = TH2F("gJetpT_v_offJetpT", "Offline Jet pT versus gJet pT", 1000, 0., 3000., 1000, 0., 3000.)

dijet_rho_withCut = TH1F("Dijet_RhoCut", "Rho Cut", 100, -100., 300.) 
dijet_rho_noCut   = TH1F("Dijet_Rho", "Rho", 100, -100., 300.)

dijet_gTowerPt = TH1F("Dijet_gTowerPt", "Dijets gTower pT", 100, -1000, 300


# gTower Histograms
# for i in range(6) 

dijets = [TFile.Open("hist.cylin.L1CaloSimu.JZ{0:d}W.tag-00-00-17_OUTPUT.root".format(i)) for i in range(6)]

#dijets = [TFile.Open("hist.cylin.L1CaloSimu.JZ2W.tag-00-00-17_OUTPUT.root"), TFile.Open("hist.cylin.L1CaloSimu.JZ3W.tag-00-00-17_OUTPUT.root"), TFile.Open("hist.cylin.L1CaloSimu.JZ4W.tag-00-00-17_OUTPUT.root"), TFile.Open("hist.cylin.L1CaloSimu.JZ5W.tag-00-00-17_OUTPUT.root")]
for dijets, scale in zip(dijets, scales): # Loops over files, colors, and scales respectively
   
        RhoCut = WithTowerCut.Get("trigger/gjet_rho")
        Rho    = NoTowerCut.Get("trigger/gjet_rho")

        RhoCut.Scale(scale)
        Rho.Scale(scale)
  
	pt  = dijets.Get("gTowers/gtowerPt")
	pt.Scale(scale)
        dijet_gTowerPt.Add(pt)       

        D1 = dijets.Get("L1/G140_leading/numerator_deltaR_v_OffJet_pT")
	D2 = dijets.Get("L1/G140_leading/numerator_gJet_v_OffJet_pT")
 
	D1.Scale(scale)
	D2.Scale(scale)
       
	Hist_DeltaR.Add(D1)
	Hist_pT.Add(D2)

	#declaring pass/total
        total1 = dijets.Get("L1/G140_leading/denominator") 
        total2 = dijets.Get("L1/J100_leading/denominator")
	total3 = dijets.Get("L1/G180_leading/denominator")
	total4 = dijets.Get("L1/G100_leading/denominator")

	pass1  = dijets.Get("L1/G140_leading/numerator")
        pass2  = dijets.Get("L1/J100_leading/numerator")
	pass3  = dijets.Get("L1/G180_leading/numerator")
	pass4  = dijets.Get("L1/G100_leading/numerator")

        cut_total1 = dijets.Get("L1/G140_leading/denominator_wDeltaRcut")
        cut_total3 = dijets.Get("L1/G180_leading/denominator_wDeltaRcut")
        cut_total4 = dijets.Get("L1/G100_leading/denominator_wDeltaRcut")
        cut_pass1  = dijets.Get("L1/G140_leading/numerator_wDeltaRcut")
        cut_pass3  = dijets.Get("L1/G180_leading/numerator_wDeltaRcut")
        cut_pass4  = dijets.Get("L1/G100_leading/numerator_wDeltaRcut")


	# For Pileup
        

        pu_pass1  = dijets.Get("L1/G140_leading/numerator_wPileupCorrection")
        pu_pass3  = dijets.Get("L1/G180_leading/numerator_wPileupCorrection")
        pu_pass4  = dijets.Get("L1/G100_leading/numerator_wPileupCorrection")

        pu_cut_pass1  = dijets.Get("L1/G140_leading/numerator_wDeltaRcut_wPileupCorrection")
        pu_cut_pass3  = dijets.Get("L1/G180_leading/numerator_wDeltaRcut_wPileupCorrection")
        pu_cut_pass4  = dijets.Get("L1/G100_leading/numerator_wDeltaRcut_wPileupCorrection")


        # Scaling pt region for each pass/total histogram
        total1.Scale(scale)
	total2.Scale(scale)
	total3.Scale(scale)
	total4.Scale(scale)
        pass1.Scale(scale)
	pass2.Scale(scale)
	pass3.Scale(scale)
	pass4.Scale(scale)

	dijet_L1_G140_num.Add(pass1)
        dijet_L1_G140_denom.Add(total1)
	
	dijet_L1_J100_num.Add(pass2)
	dijet_L1_J100_denom.Add(total2)	
	
	dijet_L1_G180_num.Add(pass3)
	dijet_L1_G180_denom.Add(total3)

	dijet_L1_G100_num.Add(pass4)
	dijet_L1_G100_denom.Add(total4)

        cut_total1.Scale(scale)
        cut_total3.Scale(scale)
        cut_total4.Scale(scale)
        cut_pass1.Scale(scale)
        cut_pass3.Scale(scale)
        cut_pass4.Scale(scale)

        cut_dijet_L1_G140_num.Add(cut_pass1)
        cut_dijet_L1_G140_denom.Add(cut_total1)

        cut_dijet_L1_G180_num.Add(cut_pass3)
        cut_dijet_L1_G180_denom.Add(cut_total3)

        cut_dijet_L1_G100_num.Add(cut_pass4)
        cut_dijet_L1_G100_denom.Add(cut_total4)

        # For Pileup Correction - > No J series because those are trimmed already. Only providing pileup correction for gJets :-)
        pu_pass1.Scale(scale)
        pu_pass3.Scale(scale)
        pu_pass4.Scale(scale)

        pu_dijet_L1_G140_num.Add(pu_pass1)
        pu_dijet_L1_G140_denom.Add(total1)

        pu_dijet_L1_G180_num.Add(pu_pass3)
        pu_dijet_L1_G180_denom.Add(total3)

        pu_dijet_L1_G100_num.Add(pu_pass4)
        pu_dijet_L1_G100_denom.Add(total4)

        pu_cut_pass1.Scale(scale)
        pu_cut_pass3.Scale(scale)
        pu_cut_pass4.Scale(scale)

        pu_cut_dijet_L1_G140_num.Add(pu_cut_pass1)
        pu_cut_dijet_L1_G140_denom.Add(cut_total1)

        pu_cut_dijet_L1_G180_num.Add(pu_cut_pass3)
        pu_cut_dijet_L1_G180_denom.Add(cut_total3)

        pu_cut_dijet_L1_G100_num.Add(pu_cut_pass4)
        pu_cut_dijet_L1_G100_denom.Add(cut_total4)

        dijet_rho_withCut.Add(RhoCut)
        dijet_rho_noCut.Add(Rho)
  
dijet_rho_noCut.SetTitle("Median Rho per Event")
dijet_rho_noCut.GetXaxis().SetTitle("Rho [GeV/Area]")
dijet_rho_noCut.GetYaxis().SetTitle("# of Events")
dijet_rho_withCut.SetLineColor(kRed)
dijet_rho_noCut.SetLineColor(kBlue)
dijet_rho_noCut.Draw("hist")
dijet_rho_withCut.Draw("hist same")

c.Modified()
c.Update
c.Print("dijet_rho_dijet_effPlots.pdf")
c.Clear

dijet_gTowerPt.SetTitle("Multijet QCD Background gTower pT")
dijet_gTOwerPt.GetXaxis().SetTitle("gTower pT [GeV]")
dijet_gTowerPt.GetYaxis().SetTItle("number of gTowers")
gijet_gTowerPt.Draw("hist")
c.Modified()
c.Update
c.Print("dijet_gTowerPt.pdf")
c.Clear



dijet_L1_G140_num.Rebin(4)
dijet_L1_G140_denom.Rebin(4)
dijet_L1_J100_num.Rebin(4)
dijet_L1_J100_denom.Rebin(4)
dijet_L1_G180_num.Rebin(4)
dijet_L1_G180_denom.Rebin(4)
dijet_L1_G100_num.Rebin(4)
dijet_L1_G100_denom.Rebin(4)

cut_dijet_L1_G140_num.Rebin(4)
cut_dijet_L1_G140_denom.Rebin(4)
cut_dijet_L1_G180_num.Rebin(4)
cut_dijet_L1_G180_denom.Rebin(4)
cut_dijet_L1_G100_num.Rebin(4)
cut_dijet_L1_G100_denom.Rebin(4)


pu_dijet_L1_G140_num.Rebin(4)
pu_dijet_L1_G140_denom.Rebin(4)
pu_dijet_L1_G180_num.Rebin(4)
pu_dijet_L1_G180_denom.Rebin(4)
pu_dijet_L1_G100_num.Rebin(4)
pu_dijet_L1_G100_denom.Rebin(4)

pu_cut_dijet_L1_G140_num.Rebin(4)
pu_cut_dijet_L1_G140_denom.Rebin(4)
pu_cut_dijet_L1_G180_num.Rebin(4)
pu_cut_dijet_L1_G180_denom.Rebin(4)
pu_cut_dijet_L1_G100_num.Rebin(4)
pu_cut_dijet_L1_G100_denom.Rebin(4)


# Create Plots of gTower Information

Hist_DeltaR.SetTitle("DeltaR versus Offline Jet pT")
Hist_DeltaR.GetXaxis().SetTitle("pT^{for Offline Jets} [GeV]")
Hist_DeltaR.GetYaxis().SetTitle("Delta R")
Hist_DeltaR.Draw("colz")
c.Modified()
c.Update
c.Print("2DHist_DeltaR.pdf")
c.Clear()

Hist_DeltaR.SetTitle("gJet pT versus Offline Jet pT")
Hist_DeltaR.GetXaxis().SetTitle("pT^{Offline Jets} [GeV]")
Hist_DeltaR.GetYaxis().SetTitle("pT^{gJets} [GeV]")
Hist_DeltaR.Draw("hist")
c.SetLogx()
c.SetLogy()
c.Modified()
c.Update
c.Print("2DHist_pT.pdf")
c.Clear()

c = TCanvas()


del c

c = TCanvas()
# Create Efficiency Plots

dijet_effPlot_L1_G140 = TGraphAsymmErrors(dijet_L1_G140_num, dijet_L1_G140_denom, "cl=0.683 b(1,1) mode")
dijet_effPlot_L1_G140.SetMinimum(0.)
dijet_effPlot_L1_J100 = TGraphAsymmErrors(dijet_L1_J100_num, dijet_L1_J100_denom, "cl=0.683 b(1,1) mode")
dijet_effPlot_L1_J100.SetMinimum(0.)
dijet_effPlot_L1_G180 = TGraphAsymmErrors(dijet_L1_G180_num, dijet_L1_G180_denom, "cl=0.683 b(1,1) mode")
dijet_effPlot_L1_G180.SetMinimum(0.)
dijet_effPlot_L1_G100 = TGraphAsymmErrors(dijet_L1_G100_num, dijet_L1_G100_denom, "cl=0.683 b(1,1) mode")
dijet_effPlot_L1_G100.SetMinimum(0.)


cut_dijet_effPlot_L1_G140 = TGraphAsymmErrors(cut_dijet_L1_G140_num, cut_dijet_L1_G140_denom, "cl=0.683 b(1,1) mode")
cut_dijet_effPlot_L1_G140.SetMinimum(0.)
cut_dijet_effPlot_L1_G180 = TGraphAsymmErrors(cut_dijet_L1_G180_num, cut_dijet_L1_G180_denom, "cl=0.683 b(1,1) mode")
cut_dijet_effPlot_L1_G180.SetMinimum(0.)
cut_dijet_effPlot_L1_G100 = TGraphAsymmErrors(cut_dijet_L1_G100_num, cut_dijet_L1_G100_denom, "cl=0.683 b(1,1) mode")
cut_dijet_effPlot_L1_G100.SetMinimum(0.)

pu_dijet_effPlot_L1_G140 = TGraphAsymmErrors(pu_dijet_L1_G140_num, pu_dijet_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_dijet_effPlot_L1_G140.SetMinimum(0.)
pu_dijet_effPlot_L1_G180 = TGraphAsymmErrors(pu_dijet_L1_G180_num, pu_dijet_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_dijet_effPlot_L1_G180.SetMinimum(0.)
pu_dijet_effPlot_L1_G100 = TGraphAsymmErrors(pu_dijet_L1_G100_num, pu_dijet_L1_G100_denom, "cl=0.683 b(1,1) mode")
pu_dijet_effPlot_L1_G100.SetMinimum(0.)


pu_cut_dijet_effPlot_L1_G140 = TGraphAsymmErrors(pu_cut_dijet_L1_G140_num, pu_cut_dijet_L1_G140_denom, "cl=0.683 b(1,1) mode")
pu_cut_dijet_effPlot_L1_G140.SetMinimum(0.)
pu_cut_dijet_effPlot_L1_G180 = TGraphAsymmErrors(pu_cut_dijet_L1_G180_num, pu_cut_dijet_L1_G180_denom, "cl=0.683 b(1,1) mode")
pu_cut_dijet_effPlot_L1_G180.SetMinimum(0.)
pu_cut_dijet_effPlot_L1_G100 = TGraphAsymmErrors(pu_cut_dijet_L1_G100_num, pu_cut_dijet_L1_G100_denom, "cl=0.683 b(1,1) mode")
pu_cut_dijet_effPlot_L1_G100.SetMinimum(0.)


# Draw Efficiency Plots


c.SetTitle("Efficiency")
dijet_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jet} [GeV]")
dijet_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
dijet_effPlot_L1_G100.SetMarkerColor(kRed)
dijet_effPlot_L1_G100.SetLineColor(kRed)
dijet_effPlot_L1_G140.SetMarkerColor(kOrange)
dijet_effPlot_L1_G140.SetLineColor(kOrange)
dijet_effPlot_L1_G180.SetMarkerColor(kGreen)
dijet_effPlot_L1_G180.SetLineColor(kGreen)
dijet_effPlot_L1_J100.SetMarkerColor(kBlue)
dijet_effPlot_L1_J100.SetLineColor(kBlue)
dijet_effPlot_L1_G140.Draw("epa")
dijet_effPlot_L1_J100.Draw("epsame")
dijet_effPlot_L1_G180.Draw("epsame")
dijet_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("leading_dijet_effPlots_L1_G100_G140_G180_J100.pdf")
c.Clear

c.SetTitle("Efficiency")
cut_dijet_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jet} [GeV]")
cut_dijet_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
cut_dijet_effPlot_L1_G100.SetMarkerColor(kRed)
cut_dijet_effPlot_L1_G100.SetLineColor(kRed)
cut_dijet_effPlot_L1_G140.SetMarkerColor(kOrange)
cut_dijet_effPlot_L1_G140.SetLineColor(kOrange)
cut_dijet_effPlot_L1_G180.SetMarkerColor(kGreen)
cut_dijet_effPlot_L1_G180.SetLineColor(kGreen)
cut_dijet_effPlot_L1_G140.Draw("epa")
cut_dijet_effPlot_L1_G180.Draw("epsame")
cut_dijet_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("leading_dijet_cut_effPlots_L1_G100_G140_G180.pdf")
c.Clear



c.SetLogy()
dijet_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
dijet_L1_G140_num.GetYaxis().SetTitle("Efficiency")
dijet_L1_G100_num.SetMarkerColor(kRed)
dijet_L1_G100_num.SetLineColor(kRed)
dijet_L1_G140_num.SetMarkerColor(kOrange)
dijet_L1_G140_num.SetLineColor(kOrange)
dijet_L1_G180_num.SetMarkerColor(kGreen)
dijet_L1_G180_num.SetLineColor(kGreen)
dijet_L1_G180_denom.SetMarkerColor(kBlack)
dijet_L1_G180_denom.SetLineColor(kBlack)
dijet_L1_G140_num.Draw("hist")
dijet_L1_G140_num.SetTitle("Offline Jets pT for different cuts, Multijet QCD Background")
dijet_L1_G180_denom.Draw("histsame")
dijet_L1_G180_num.Draw("histsame")
dijet_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_dijet_numPlots_L1_G100_G140_G180.pdf")

c.Clear


c.SetLogy()
cut_dijet_L1_G140_num.GetXaxis().SetTitle("p_{T}^{Offline Jets} [GeV]")
cut_dijet_L1_G140_num.GetYaxis().SetTitle("Efficiency with cut on deltaR < 1.0")
cut_dijet_L1_G100_num.SetMarkerColor(kRed)
cut_dijet_L1_G100_num.SetLineColor(kRed)
cut_dijet_L1_G140_num.SetMarkerColor(kOrange)
cut_dijet_L1_G140_num.SetLineColor(kOrange)
cut_dijet_L1_G180_num.SetMarkerColor(kGreen)
cut_dijet_L1_G180_num.SetLineColor(kGreen)
cut_dijet_L1_G180_denom.SetMarkerColor(kBlack)
cut_dijet_L1_G180_denom.SetLineColor(kBlack)
cut_dijet_L1_G140_num.Draw("hist")
cut_dijet_L1_G140_num.SetTitle("Offline Jets pT for different cuts, Multijet QCD Background")
cut_dijet_L1_G180_denom.Draw("histsame")
cut_dijet_L1_G180_num.Draw("histsame")
cut_dijet_L1_G100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_dijet_cut_numPlots_L1_G100_G140_G180.pdf")

c.Clear

dijet_L1_J100_num.SetMarkerColor(kBlue)
dijet_L1_J100_num.SetLineColor(kBlue)
dijet_L1_J100_denom.SetMaximum(10000)
dijet_L1_J100_denom.SetMarkerColor(kBlack)
dijet_L1_J100_denom.SetLineColor(kBlack)
dijet_L1_J100_denom.Draw("hist")
dijet_L1_J100_num.SetTitle("Numerator/Denominator for Run2 L1 jet pT, 100 GeV cut")
dijet_L1_J100_num.Draw("histsame")
c.Modified()
c.Update
c.Print("leading_dijet_numPlots_L1_J100.pdf")
c.Clear
del c

c = TCanvas()

# For pileup
pu_dijet_effPlot_L1_G140.SetTitle("Efficiency for Multijet QCD Background")
pu_dijet_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jet} [GeV]")
pu_dijet_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
pu_dijet_effPlot_L1_G100.SetMarkerColor(kRed)
pu_dijet_effPlot_L1_G100.SetLineColor(kRed)
pu_dijet_effPlot_L1_G140.SetMarkerColor(kOrange)
pu_dijet_effPlot_L1_G140.SetLineColor(kOrange)
pu_dijet_effPlot_L1_G180.SetMarkerColor(kGreen)
pu_dijet_effPlot_L1_G180.SetLineColor(kGreen)
pu_dijet_effPlot_L1_G140.Draw("epa")
pu_dijet_effPlot_L1_G180.Draw("epsame")
pu_dijet_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_dijet_effPlots_L1_G100_G140_G180.pdf")
c.Clear

del c

c = TCanvas()

pu_cut_dijet_effPlot_L1_G140.SetTitle("Efficiency for Multijet QCD Background with cut on deltaR < 1.0")
pu_cut_dijet_effPlot_L1_G140.GetXaxis().SetTitle("p_{T}^{Offline Jet} [GeV]")
pu_cut_dijet_effPlot_L1_G140.GetYaxis().SetTitle("Efficiency")
pu_cut_dijet_effPlot_L1_G100.SetMarkerColor(kRed)
pu_cut_dijet_effPlot_L1_G100.SetLineColor(kRed)
pu_cut_dijet_effPlot_L1_G140.SetMarkerColor(kOrange)
pu_cut_dijet_effPlot_L1_G140.SetLineColor(kOrange)
pu_cut_dijet_effPlot_L1_G180.SetMarkerColor(kGreen)
pu_cut_dijet_effPlot_L1_G180.SetLineColor(kGreen)
pu_cut_dijet_effPlot_L1_G140.Draw("epa")
pu_cut_dijet_effPlot_L1_G180.Draw("epsame")
pu_cut_dijet_effPlot_L1_G100.Draw("epsame")
c.Modified()
c.Update
c.Print("pu_leading_dijet_cut_effPlots_L1_G100_G140_G180.pdf")
c.Clear

c.Clear

del c

