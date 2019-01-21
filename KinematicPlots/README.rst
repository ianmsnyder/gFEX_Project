KinematicPlots
==============

This is a repository whose sole focus is to produce histograms (with selections) of various kinematic features of the samples that gFEX studies.

This package was developed by Giordon Stark and modified by Ian Snyder.

Set-Up
------

To get started, we use ``xAH_run.py`` to spin up jobs so we need `xAODAnaHelpers <https://xaodanahelpers.readthedocs.io/en/latest>`_. First make a directory containing all code for the analysis and set up RootCore::

  mkdir gFEX && cd $_
  rcSetup Base,2.4.9

Next, grab the required packages::

  git clone https://github.com/UCATLAS/xAODAnaHelpers.git
  git clone --recursive ssh://git@gitlab.cern.ch:7999/l1calo-gfex/KinematicPlots.git

Build the dependency list and then compile::

  rc find_packages --restrict KinematicPlots
  rc compile


Updating List of Samples
------------------------

The list of samples is in `samples <https://gitlab.cern.ch/l1calo-gfex/samples>`_ which is a submodule. You just need to ``cd KinematicPlots`` and then run::

  git submodule update --remote

to update things.

Running
-------

We have prepared file lists in `samples <https://gitlab.cern.ch/l1calo-gfex/samples>`_ which can be used with ``xAH_run.py`` to submit jobs. To run a quick job, you can do::

  xAH_run.py --files "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/det-gfex-upgrade/MiniNtuples/MC15-Samples-00-00-17/user.cylin.L1CaloSimu.JZ0W.tag-00-00-17_OUTPUT/" --scanXRD --config KinematicPlots/data/config.py -vvv -f --treeName mytree --nevents 1000 direct

which will run over 1000 events of a single sample ``user.cylin.L1CaloSimu.JZ0W.tag-00-00-17_OUTPUT`` (which contains multiple files) using the specified `configuration <data/config.py>`_.

To run over all samples, you can just do::

  xAH_run.py --config KinematicPlots/data/config.py --files KinematicPlots/samples/tags/latest/*.list --inputList --scanXRD -f -vvv --treeName mytree --submitDir submitDir_allSamples direct

However, the Minimum Bias samples do not have any truth jet information so they will never pass the MC Quality Cuts. Make sure those cuts are disabled whenr unning over minimum bias samples.

Running over Min-Bias
~~~~~~~~~~~~~~~~~~~~~

A special configuration is added for minimum bias samples::

  xAH_run.py --config KinematicPlots/data/config_minbias.py --files KinematicPlots/samples/tags/latest/MinBias.list --inputList --scanXRD -f -vvv --treeName mytree --submitDir submitDir_2016_08_24_MinBias condor

Don't forget to change the submit directory name.

Running over all other samples
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For all other samples, the same configuration could (and should) be used::

  xAH_run.py --config KinematicPlots/data/config.py --files KinematicPlots/samples/tags/latest/Dijets.list KinematicPlots/samples/tags/latest/Higgs.list KinematicPlots/samples/tags/latest/Wprime.list KinematicPlots/samples/tags/latest/Zee.list KinematicPlots/samples/tags/latest/Zprime.list --inputList --scanXRD -f -vvv --treeName mytree --submitDir submitDir_2016_08_24 condor

Don't forget to change the submit directory name.

Configuration
=============

See `data/config.py <data/config.py>`_ for information about all the current configuration options. If you have any questions, contact the mailing list.

More Information
================

GJet Definition
---------------

The gFEX Trigger Jets that exist in these ntuples are formed from the (at the moment) outdated code found `here <https://svnweb.cern.ch/trac/atlasgroups/browser/Trigger/L1CaloUpgrade/TrigT1CaloCommon/trunk/src/GJet.cxx>`_.


Building the Tower Grid Map
---------------------------

A `helper script <scripts/make_central_grid.py>`_ is provided to generate the necessary C++ header code that goes in `Objects.h <KinematicPlots/Objects.h>`_ for the ``TowerGrid`` class.

Calculating the Rates
---------------------

After talking with David Strom, see `this excel sheet <https://espace.cern.ch/HiLumi/PLC/_layouts/15/WopiFrame.aspx?sourcedoc=%2FHiLumi%2FPLC%2FSiteAssets%2FParameter%20Table%2Exlsx&action=view>`_ for some numbers. The procedure is relatively straightforward for right now:

- run the same code on the MinBias samples
- integrate the number of events in numerator (passing trigger) and denominator
- divide these two numbers to get the fraction of events passing the trigger for your MinBias sample
- multiply this number by the BC rate ``2736*11245``
  - 2736 is the number of bunches
  - 11245 is the LHC frequency (how long it takes a particle to go around the ring)

Merging Outputs
---------------

If you are running this on condor, or another batch system, you'll have files in ``submitDir/fetch/`` which have names like ``sample-0.root, sample-1.root, ...``. For convenience, a merge script is provided in those cases which can be run::

  ./KinematicPlots/scripts/merge_outputs.sh submitDir

Inspiration
-----------
Many thanks to Christian Johnson's original code::

  svn co svn+ssh://svn.cern.ch/reps/atlas-cjohnson/RootCore_gFEX_Generic/tags/RootCore_gFEX_Generic-00-00-11
