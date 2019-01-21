#ifndef KinematicPlots_Objects_H
#define KinematicPlots_Objects_H
#include "Math/Vector4D.h"
#include "TVector2.h"
#include "math.h"
#include <algorithm>

namespace gFEX {
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > FourMom_t;

  // primarily to make the interface consistent
  class Object : public FourMom_t {
    private:
      double m_area = 0.0;

    public:
      Object() : FourMom_t(0.0, 0.0, 0.0, 0.0) {};
      Object(double pt, double eta, double phi, double m) :
        FourMom_t(pt, eta, phi, m)
      {};
      ~Object () {};
      double et()  const     {return this->Et();};
      double pt()  const     {return this->Pt();};
      void   pt(double pt)   {this->SetPt(pt);};
      double eta() const     {return this->Eta();};
      void   eta(double eta) {this->SetEta(eta);};
      double phi() const     {return this->Phi();};
      void   phi(double phi) {this->SetPhi(phi);};
      double m()   const     {return this->M();};
      void   m(double m)     {this->SetM(m);};
      double area() const    {return m_area;};
      void   area(double a)  {m_area = a;};
      // comparison operators for easy sorting
      friend bool operator<  (const Object &o1, const Object &o2){ return o1.pt() <  o2.pt(); };
      friend bool operator>  (const Object &o1, const Object &o2){ return o1.pt() >  o2.pt(); };
      friend bool operator<= (const Object &o1, const Object &o2){ return o1.pt() <= o2.pt(); };
      friend bool operator>= (const Object &o1, const Object &o2){ return o1.pt() >= o2.pt(); };
      double deltaR(const Object &other) const {
        double deta = this->deltaEta(other);
        double dphi = this->deltaPhi(other);
        return std::sqrt( deta*deta + dphi*dphi );
      };
      double deltaEta(const Object& other) const {
        return this->eta() - other.eta();
      };
      double deltaPhi(const Object &other) const {
        return TVector2::Phi_mpi_pi(this->phi() - other.phi());
      };
      double rho() const {return pt()/area();};

  };

  class Tower : public Object {
    private:
      double m_etaMin = 0.0;
      double m_etaMax = 0.0;
      double m_phiMin = 0.0;
      double m_phiMax = 0.0;
      double m_etaWeighted = 0.0;
      double m_phiWeighted = 0.0;

    public:
      Tower () :
        Object() {};
      Tower (double pt, double etaGeometric, double phiGeometric,
             double etaMin, double etaMax,
             double phiMin, double phiMax,
             double etaWeighted, double phiWeighted) :
        Object(pt, etaGeometric, phiGeometric, 0.0),
        m_etaMin(etaMin), m_etaMax(etaMax),
        m_phiMin(phiMin), m_phiMax(phiMax),
        m_etaWeighted(etaWeighted), m_phiWeighted(phiWeighted)
      {
        this->area(std::fabs(phiMax-phiMin)*std::fabs(etaMax-etaMin));
      };
      double etaMin() const {return m_etaMin;};
      double etaMax() const {return m_etaMax;};
      double phiMin() const {return m_phiMin;};
      double phiMax() const {return m_phiMax;};
      double etaWeighted() const {return m_etaWeighted;};
      double phiWeighted() const {return m_phiWeighted;};
  };

  class Block : public Object {
    private:
      int m_seedIndex = -1;
      int m_numEta;
      int m_numPhi;
      int m_numConstituents = 0;

    public:
      Block () :
        Object() {};
      Block (double pt, double eta, double phi, double m) :
        Object(pt, eta, phi, m) {};

      int seedIndex() const {return m_seedIndex;};
      void seedIndex(int i) {m_seedIndex = i;};
      int numEta() const {return m_numEta;};
      void numEta(int n) {m_numEta = n;};
      int numPhi() const {return m_numPhi;};
      void numPhi(int n) {m_numPhi = n;};
      int numConstituents() const {return m_numConstituents;};
      void numConstituents(int n) {m_numConstituents = n;};
  };

  class Jet : public Object {
    private:
      int m_seedIndex = -1;
      int m_parentIndex = -1;
      int m_numConstituents = 0;
      int m_numSubjets = 0;

    public:
      Jet () :
        Object() {};
      Jet (double pt, double eta, double phi, double m) :
        Object(pt, eta, phi, m) {};

      int seedIndex() const {return m_seedIndex;};
      void seedIndex(int i) {m_seedIndex = i;};
      int parentIndex() const {return m_parentIndex;};
      void parentIndex(int i) {m_parentIndex = i;};
      int numConstituents() const {return m_numConstituents;};
      void numConstituents(int n) {m_numConstituents = n;};
      int numSubjets() const {return m_numSubjets;};
      void numSubjets(int n) {m_numSubjets = n;};

  };

  class TowerGrid {
    public:
      // build up the grid
      TowerGrid(const std::vector<Tower>& towers){
        grid = std::vector<int>(grid_eta*grid_phi, -1);
        for(const auto& tower: towers){
          int towerIndex = std::find(towers.begin(), towers.end(), tower) - towers.begin();
          this->add_tower(tower, towerIndex);
        }
      };
      void add_tower(const Tower& tower, int towerIndex){
        int gridIndex = get_index(tower);
        if(gridIndex >= 0){
          grid[gridIndex] = towerIndex;
        }
      };
      // normalization functions
      std::pair<int, int> normalize_coord(std::pair<int, int> coord) const {
        while(coord.second < 0) coord.second+= grid_phi;
        return coord;
      };
      int normalize_index(int index) const {
        while(index < 0) index+= grid_eta*grid_phi;
        return index;
      };
      // get_index functions
      int get_index(const Tower& tower) const {
        return get_index(get_coord(tower));
      };
      int get_index(std::pair<int, int> coord) const {
        coord = normalize_coord(coord);
        if(coord.first < 0) return -1;
        if(coord.first >= grid_eta) return -1;
        return coord.second*grid_eta + coord.first;
      };
      // get_coord functions
      std::pair<int, int> get_coord(const Tower& tower) const {
        int ieta(-1);
        for(const auto& eta: eta_bins){
          if(tower.eta() < eta) break;
          ieta++;
        }
        int iphi(-1);
        for(const auto& phi: phi_bins){
          if(tower.phi() < phi) break;
          iphi++;
        }
        return std::pair<int, int>(ieta, iphi);
      };
      std::pair<int, int> get_coord(int index) const {
        index = normalize_index(index);
        int iphi = std::floor(index/grid_eta);
        int ieta = index - iphi*grid_eta;
        return std::pair<int, int>(ieta, iphi);
      };
      // neighbors functions
      std::vector<int> neighbors(const Tower& tower, int nrows=3, int ncols=3) const {
        return neighbors(get_coord(tower), nrows, ncols);
      };
      std::vector<int> neighbors(const std::pair<int, int>& coord, int nrows=3, int ncols=3) const {
        std::vector<int> neighbors;
        if(nrows%2==0 || ncols%2==0) return neighbors;
        for(int irow=-(nrows-1)/2; irow <= (nrows-1)/2; ++irow){
          for(int icol=-(nrows-1)/2; icol <= (ncols-1)/2; ++icol){
            // don't include itself
            if(irow==0 && icol==0) continue;
            std::pair<int, int> neighbor(coord.first + icol, coord.second + irow);
            int index = this->at(normalize_coord(neighbor));
            // only if the tower exists in that grid
            if(index >= 0){
              neighbors.push_back(index);
            }
          }
        }
        return neighbors;
      }
      // at functions
      int at(const std::pair<int, int>& coord) const {
        return this->at(get_index(coord));
      };
      int at(int index) const {
        // out-of-bounds return -1
        if(index < 0) return -1;
        if(index >= static_cast<int>(grid.size())) return -1;
        // otherwise, it's within the range of the grid
        return grid.at(index);
      };
    private:
      // Auto-generated with scripts/make_central_grid.py
      const int grid_eta = 24;
      const int grid_phi = 32;
      std::vector<int> grid;
      std::vector<double> eta_bins = {
        -2.4000,
        -2.2000,
        -2.0000,
        -1.8000,
        -1.6000,
        -1.4000,
        -1.2000,
        -1.0000,
        -0.8000,
        -0.6000,
        -0.4000,
        -0.2000,
        0.0000,
        0.2000,
        0.4000,
        0.6000,
        0.8000,
        1.0000,
        1.2000,
        1.4000,
        1.6000,
        1.8000,
        2.0000,
        2.2000,
        2.4000
      };

      std::vector<double> phi_bins = {
        -3.1416,
        -2.9452,
        -2.7489,
        -2.5525,
        -2.3562,
        -2.1598,
        -1.9635,
        -1.7671,
        -1.5708,
        -1.3744,
        -1.1781,
        -0.9817,
        -0.7854,
        -0.5890,
        -0.3927,
        -0.1963,
        0.0000,
        0.1963,
        0.3927,
        0.5890,
        0.7854,
        0.9817,
        1.1781,
        1.3744,
        1.5708,
        1.7671,
        1.9635,
        2.1598,
        2.3562,
        2.5525,
        2.7489,
        2.9452,
        3.1416
      };


  };
}

#endif
