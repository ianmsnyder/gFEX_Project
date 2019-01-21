from ROOT import *
#gROOT.SetBatch(1)

ptCuts=5

minBiasHists={}

minPtBin=0
maxPtBin=20 #Max pT (100 GeV for now) divided by 5 for looping purposes

for ptCut in xrange(ptCuts+1):
    minBiasFile = TFile("/usatlas/groups/bnl_local/isnyder/samples/gFEX/MinBias"+str(ptCut)+"GeVCut/hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root")

    minBiasMean=[]
    minBiasStdDev=[]
    
    minBin=0
    maxBin=20
    nBins = maxBin-minBin
    binLabels=[]
    
    for i in xrange(minPtBin, maxPtBin):
        ptMin=5*i
        ptMax=5+5*i
        ptString=str(ptMin)+"_"+str(ptMax)
        binLabels.append(ptString)
        minBiasHists[str(ptCut)+"_"+str(ptString)] = minBiasFile.Get("postsel/event/RatiogBlockPtJetPtBinnedByJetPt"+str(ptString))
        minBiasMean.append(minBiasHists[str(ptCut)+"_"+str(ptString)].GetMean())
        minBiasStdDev.append(minBiasHists[str(ptCut)+"_"+str(ptString)].GetStdDev())
        
    minBiasStdDevHist=TH1F("minBiasStdDevHist","", nBins, minBin, maxBin)
    minBiasMeanHist=TH1F("minBiasMeanHist","", nBins, minBin, maxBin)
        
    for i in xrange(minPtBin,maxPtBin):
        minBiasStdDevHist.SetBinContent(i+1, minBiasStdDev[i])
        minBiasMeanHist.SetBinContent(i+1, minBiasMean[i])

        minBiasStdDevHist.GetXaxis().SetBinLabel(i+1, binLabels[i])
        minBiasMeanHist.GetXaxis().SetBinLabel(i+1, binLabels[i])

    MeanCanvas=TCanvas()
    StdDevCanvas=TCanvas()

    MeanCanvas.cd()
    minBiasMeanHist.Draw("hist")
    minBiasMeanHist.GetXaxis().SetTitle("Offline Jet p_{T} Bin")
    minBiasMeanHist.GetYaxis().SetTitle("Ratio Mean")

    MeanCanvas.SaveAs("comparisonPlots/RatioMeangTowerPtCut"+str(ptCut)+".pdf")

    StdDevCanvas.cd()
    minBiasStdDevHist.Draw("hist")
    minBiasStdDevHist.GetXaxis().SetTitle("Offline Jet p_{T} Bin")
    minBiasStdDevHist.GetYaxis().SetTitle("Ratio Standard Deviation")
    StdDevCanvas.SaveAs("comparisonPlots/RatioStdDevgTowerPtCut"+str(ptCut)+".pdf")

    del MeanCanvas, StdDevCanvas, minBiasFile, minBiasStdDevHist, minBiasMeanHist

minBiasHists={}

for i in xrange(1, 3):#maxPtBin):
    ptMin=5*i
    ptMax=5+5*i
    ptString=str(ptMin)+"_"+str(ptMax)


    gBlockCutsCanvas=TCanvas("gBlockCutsCanvas")
    #gPad.DrawFrame(0., 0., 1., 1.)
    leg=TLegend(.7, .7, .9, .9)
    leg.SetFillColor(0)
    leg.SetShadowColor(10)
    leg.SetLineColor(10)
    leg.SetFillColor(10)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    
    for ptCut in xrange(2):#ptCuts+1):
        minBiasFile = TFile("/usatlas/groups/bnl_local/isnyder/samples/gFEX/MinBias"+str(ptCut)+"GeVCut/hist-user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT.root")
        minBiasHists[str(ptCut)+"_"+str(ptString)] = minBiasFile.Get("postsel/event/RatiogBlockPtJetPtBinnedByJetPt"+str(ptString))
        #print type(minBiasFile), type(minBiasHists[str(ptCut)+"_"+str(ptString)])
        #minBiasHists[str(ptCut)+"_"+str(ptString)].Draw()
        nBinsHisto=200#minBiasHists[str(ptCut)+"_"+str(ptString)].GetSize()
        peakBin=0.
        #print "SIze: ", nBinsHisto
        for bI in xrange(1,200):#nBinsHisto+1):
            print bI
            print "Peak: ", minBiasHists[str(ptCut)+"_"+str(ptString)].GetBinContent(bI)
            if minBiasHists[str(ptCut)+"_"+str(ptString)].GetBinContent(bI)>peakBin:
                peakBin=minBiasHists[str(ptCut)+"_"+str(ptString)].GetBinContent(bI)
        #numberBins = minBiasHists[str(ptCut)+"_"+str(ptString)].GetSize()-2
        #minBins=minBiasHists[str(ptCut)+"_"+str(ptString)].GetXaxis().FindBin(1)
        #maxBins=minBiasHists[str(ptCut)+"_"+str(ptString)].GetXaxis().FindBin(numberBins-2)
        #print numberBins, minBins, maxBins
        print peakBin
        newHist=TH1F("newHist","", 200, -10, 10)
        for bI in xrange(1,nBinsHisto+1):
            binContent=minBiasHists[str(ptCut)+"_"+str(ptString)].GetBinContent(bI)
            if peakBin!=0:
                newHist.SetBinContent(bI, binContent/peakBin)
                print newHist.GetBinContent(bI)
            else:
                newHist.SetBinContent(bI, 0)
                print newHist.GetBinContent(bI)
                
        #print type(minBiasHists[str(ptCut)+"_"+str(ptString)])
        gBlockCutsCanvas.cd()
#        minBiasHists[str(ptCut)+"_"+str(ptString)].Draw()
        if ptCut==0:
            newHist.Draw("hist")
            #print "first"
        else:
            newHist.Draw("hist same")
            #print "others"
        
        #newHist.SetLineColor(ptCut)
        print type(newHist)
        leg.AddEntry(newHist, str(ptCut)+ "GeV Cut on gTowers", "L")
        del minBiasFile, newHist
    gBlockCutsCanvas.SetLogy(1)
    leg.Draw()
    print "About to save      comparisonPlots/pTcutsOfflineJetBin"+str(ptString)+".pdf"
    gBlockCutsCanvas.SaveAs("comparisonPlots/pTcutsOfflineJetBin"+str(ptString)+".pdf")
   
    #del gBlockCutsCanvas, leg
