#ifndef KinematicPlots_Algorithms_H
#define KinematicPlots_Algorithms_H

#include "KinematicPlots/Objects.h"
#include "fastjet/PseudoJet.hh"

#include <limits>
#include <vector>
#include <map>
#include <algorithm>

namespace gFEX {

  void BuildBlocksFromTowers(std::vector<Block>& blocks,
                             const std::vector<Tower>& towers,
                             const int& blockRows=3,
                             const int& blockCols=3);

  void BuildJetsFromTowers(std::vector<Jet>& jets,
                           const std::vector<Tower>& towers,
                           const float& seedThreshold,
                           const float& jetRadius,
                           const bool& jetCenterAsSeed=true);

  void GetJets(std::vector<Jet>& jets,
               int num_jets,
               const std::vector<float>& pt,
               const std::vector<float>& eta,
               const std::vector<float>& phi,
               const std::vector<float>& m,
               const std::vector<int>& nsj = std::vector<int>());

  void GetTowers(std::vector<Tower>& towers,
                 int num_towers,
                 const std::vector<float>& pt,
                 const std::vector<float>& etaGeometric,
                 const std::vector<float>& phiGeometric,
                 const std::vector<float>& etaMin,
                 const std::vector<float>& etaMax,
                 const std::vector<float>& phiMin,
                 const std::vector<float>& phiMax,
                 const std::vector<float>& etaWeighted,
                 const std::vector<float>& phiWeighted);


  double GetRho(const std::vector<Tower>& towers,
                const std::string& calculation_method = "median");

  void PileupCorrection(std::vector<Jet>& corrected_jets,
                        const std::vector<Jet>& uncorrected_jets,
                        const std::vector<Tower>& towers,
                        const std::string& mitigation_method = "area-based",
                        const std::string& calculation_method = "median");


  double ApplySoftKiller(std::vector<Tower>& towersSK,
                         std::vector<Tower>& towers,
                         double gridSpacing,
                         double maxEta,
                         bool isAbs = false,
                         bool applyToOnlyPos = false,
                         bool applyToAbsVal = false);

  void ApplyFixedCut(std::vector<Tower>& towers,
                     double ptCut,
                     bool isAbs = false,
                     bool isPos = false);

  double ApplyFakeSK(std::vector<Tower>& towers,
                     double gridSpacing,
                     double maxEta,
                     double minPt,
                     double maxPt,
                     bool isAbs = false);

  void ApplyAreaSub(std::vector<Tower>& towers_corrected,
                    const std::vector<Tower>& towers);

  double GetFakeMedian(std::vector<Tower>& towers,
                       double maxEta,
                       double min,
                       double max);

  double GetMedian(std::vector<Tower>& towers,
                   double maxEta);

  std::vector<gFEX::Tower> GetSKGrid(std::vector<Tower> towers,
                                     double gridSize,
                                     double maxEta,
                                     bool isAbs = false);

  /// Match Objects - left -> right
  /*
    This assumes a 1-to-1 match. If a single left object has multiple right object matches, only the first right object match is used.

    The default limit for deltaR matching is 1.0.

    The returned iterator is an iterator of matched objects that you explore like this
      for(const auto& match: MatchObjects(leftObjs, rightObjs)){
        auto matchedLeft = match.first;
        for(const auto& index: match.second){
          auto matchedRight = rightObjs.at(index);
        }
      }
  */
  template <typename T1, typename T2>
  std::map<T1, std::vector<int>> MatchObjects(std::vector<T1> leftObjs, std::vector<T2> rightObjs, double limit=1.0){
    std::map<T1, std::vector<int>> matchedObjects;
    for(auto& left: leftObjs){
      matchedObjects[left] = std::vector<int>();
      int index(-1);
      for(auto& right: rightObjs){
        index++;
        if(left.deltaR(right) > limit) continue;
        matchedObjects[left].push_back(index);
      }
    }
    return matchedObjects;
  }

  /// Return the minimum distance between objects in the vector
  template <typename T1>
  double GetMinimumDeltaR(const std::vector<T1>& objects){
    double minDeltaR(std::numeric_limits<double>::max());
    for(auto& objOuter: objects){
      std::vector<double> empty(objects.size()+1, minDeltaR);
      // make sure that we ignore the same jet itself otherwise minDeltaR=0
      std::transform(objects.begin(), objects.end(), empty.begin()+1, [&objOuter, &minDeltaR](T1 innerObj) -> double { if(objOuter != innerObj) {return objOuter.deltaR(innerObj);} else {return minDeltaR;} });
      minDeltaR = *std::min_element(empty.begin(), empty.end());
    }
    return minDeltaR;
  }
}
#endif
