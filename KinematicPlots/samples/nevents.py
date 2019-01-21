import ROOT

import subprocess

for i in range(6):
  chain = ROOT.TChain("mytree")
  print "Running subprocess call now for JZ{0:d}W".format(i)
  output = subprocess.check_output(['xrd','eosatlas.cern.ch','ls','eos/atlas/atlascerngroupdisk/det-gfex-upgrade/MiniNtuples/MC15-Samples-00-00-17/user.cylin.L1CaloSimu.JZ{0:d}W.tag-00-00-17_OUTPUT'.format(i)])
  files = [f.split()[-1] for f in output.strip().split('\n')]
  for f in files:
    chain.AddFile('root://eosatlas.cern.ch/{0:s}'.format(f))
  print "Calculating GetEntries..."
  print "JZ{0:d}W has {1:d} entries".format(i, chain.GetEntries())
