from xAH_config import xAH_config
c = xAH_config()

c.setalg("gFEX.Analysis",
    {"m_rhoThreshold": 3.0,  # maximum value for gTower Et to be considered for pileup calculation [GeV]
     "m_seedThreshold": 15.0,  # minimum value for gTower Et to be considered a seed [GeV]
     "m_noiseFilter": 0.0,  # minimum value for gTower Et to be considered for the event
     "m_dR": 1.0,  # radius of trigger jet in eta-phi units
     "m_useSeedAsCenter": True, # If true, the seed is used for the resulting jet eta/phi
     "m_doMCQualityCut": True, # If true, apply MC Quality Cut (see Analysis.cxx)
     "m_doIsolationCut": False, # If true, apply isolation cut to offline large-R trimmed jets
     "m_debug": False, # add some extra verbosity
     "m_minDistanceFrontBunchTrain": 20, # remove the first N bunches in the train, see #7 and Analysis.h
     "m_rhoCalculation": "median", # how to calculate rho
     "m_pileupMitigation": "area-based", # how to remove pileup
     "m_doAreaSub": False, # If true, SoftKiller is calculated and applied to the abs. value of the pT of all towers
     "m_doSoftKiller": False, # If true, SoftKiller is calculated and applied to the abs. value of the pT of all towers
     "m_doSoftKillerAbsVal": False, # If true, SoftKiller is calculated and applied to the abs. value of the pT of all towers
     "m_doFakeSoftKiller": False # If true, SoftKiller is calculated and applied to the abs. value of the pT of all towers
    })
