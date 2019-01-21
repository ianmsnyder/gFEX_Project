#!/usr/bin/env bash

samples=()
for f in $(find ${1}/fetch/*-0.root)
do
  samples+=(`basename $f | sed 's/-0.root//g'`)
done


for sample in "${samples[@]}"
do
  echo "Doing ${sample}"
  hadd "${1}/${sample}.root" $(find ${1}/fetch/${sample}-*.root)
done
