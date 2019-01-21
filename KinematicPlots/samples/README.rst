samples
=======

This repository contains a list of samples used by the gFEX team.

Latest Samples
--------------

Use `tags/latest <tags/latest>`_ which is a symbolic link to the latest set of samples. Update the link via::

  cd tags
  ln -s -f <latestTag> latest

Transferring Locally
--------------------

An example script using UChicago's Tier3 as the local storage is reproduced below::

  for group in KinematicPlots/samples/tags/latest/*.list
  do
    groupName=$(basename $group .list)
    echo $groupName
    mkdir /share/t3data3/kratsg/gFEXSamples/$groupName
    for sample in `cat $group`
    do
      sampleName=${sample/root:\/\/eosatlas.cern.ch\//}
      mkdir /share/t3data3/kratsg/gFEXSamples/$groupName/$(basename $sampleName)
      echo $(basename $sampleName)
      for file in `xrd eosatlas.cern.ch ls $sampleName | cut -d ':' -f 3 | cut -d ' ' -f 2`
      do
        echo $(basename $file)
        xrdcp root://eosatlas.cern.ch/$file /share/t3data3/kratsg/gFEXSamples/$groupName/$(basename $sampleName)/$(basename $file)
      done
    done
  done

References
==========

See the `twiki page <https://twiki.cern.ch/twiki/bin/view/Atlas/L1CaloUpgradeSimulation#Output_files>`_ for more information about these samples.
