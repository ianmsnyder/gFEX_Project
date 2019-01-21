import ROOT

f = ROOT.TFile.Open('root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/det-gfex-upgrade/MiniNtuples/MC15-Samples-00-00-17/user.cylin.L1CaloSimu.MinimumBias.tag-00-00-17_OUTPUT/user.cylin.8535514.OUTPUT._000001.root')
maps = f.Get('maps')

maps.GetEntry(0)

eta_bins = sorted([i for i in maps.gTowerEtaBins if abs(i) < 2.5])
phi_bins = sorted([i for i in maps.gTowerPhiBins])

print "      // Auto-generated with",__file__
print "      const int grid_eta = {0:d};".format(len(eta_bins)-1)
print "      const int grid_phi = {0:d};".format(len(phi_bins)-1)
print "      std::vector<int> grid{{{0:d}, -1}};".format((len(eta_bins)-1)*(len(phi_bins)-1))
print "      std::vector<double> eta_bins = {"
for eta in eta_bins:
  print "        {0:0.4f},".format(eta)
print "      };\n"

print "      std::vector<double> phi_bins = {"
for phi in phi_bins:
  print "        {0:0.4f},".format(phi)
print "      };"
