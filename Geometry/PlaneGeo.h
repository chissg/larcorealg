////////////////////////////////////////////////////////////////////////
/// \file  PlaneGeo.h
/// \brief Encapsulate the construction of a single detector plane
///
/// \version $Id: PlaneGeo.h,v 1.7 2009/12/01 21:07:51 brebel Exp $
/// \author  brebel@fnal.gov
////////////////////////////////////////////////////////////////////////
#ifndef GEO_PLANEGEO_H
#define GEO_PLANEGEO_H
#include <vector>
#include <algorithm>
class TGeoNode;
class TGeoHMatrix;
class TVector3;

#include "SimpleTypesAndConstants/geo_types.h"
#include "Geometry/GeoObjectSorter.h"

namespace geo {
  class WireGeo;

  //......................................................................
  
  /// Geometry information for a single readout plane
  class PlaneGeo {
  public:
    /// Construct a representation of a single plane of the detector
    PlaneGeo(std::vector<const TGeoNode*>& path, int depth);
    ~PlaneGeo();

    /// Method to sort WireGeo objects
    void SortWires(geo::GeoObjectSorter const& sorter);

    /// Number of wires in this plane
    unsigned int Nwires()                                     const { return fWire.size();   }

    /// Return the iwire'th wire in the plane. 
    const WireGeo& Wire(unsigned int iwire)                   const { return *fWire[iwire];  }
    
    /// Which coordinate does this plane measure
    View_t View()                                             const { return fView;          }
    
    /// What is the orienation of the plane
    Orient_t Orientation()                                    const { return fOrientation;   }

    /// What is the signal type for the plane
    SigType_t SignalType()                                    const { return fSignalType;    }

    /// Set the signal type and view from TPCGeo
    void SetSignalType(geo::SigType_t sigtype)                      { fSignalType = sigtype; }
    void SetView(geo::View_t view)                                  { fView = view; }

    double WirePitch()                                        const { return fWirePitch; }
    
    /**
     * @brief Returns the direction normal to the plane
     * @return a TVector3 versor with a direction normal to the plane
     *
     * The versor is orthogonal to the plane.
     * Its direction is defined so that the cross product of it and the wires
     * direction points to wires of larger ID.
     * The wire direction is as returned by geo::WireGeo::Direction(),
     * and defined by the geometry.
     */
    TVector3 GetNormalDirection() const;

    /**
     * @brief Returns the direction of increasing wires
     * @return a TVector3 versor with the direction of increasing wires
     *
     * The versor is orthogonal to the wires (assumed parallel),
     * lies on the plane and its direction goes toward increasing wire IDs.
     */
    TVector3 GetIncreasingWireDirection() const;

    /// Transform point from local plane frame to world frame
    void LocalToWorld(const double* plane, double* world)     const;
    
    /// Transform direction vector from local to world
    void LocalToWorldVect(const double* plane, double* world) const;

    // Again, with TVectors
    const TVector3 LocalToWorld( const TVector3& local )      const;

    /// Transform point from world frame to local plane frame
    void WorldToLocal(const double* world, double* plane)     const;

    /// Transform direction vector from world to local
    void WorldToLocalVect(const double* world, double* plane) const;
    
    // Again, with TVectors
    const TVector3 WorldToLocal( const TVector3& world )      const;
    
  private:
    
    void FindWire(std::vector<const TGeoNode*>& path,
		  unsigned int depth);
    void MakeWire(std::vector<const TGeoNode*>& path, 
		  int depth);
    
  private:
    TGeoHMatrix*          fGeoMatrix;   ///< Plane to world transform
    View_t                fView;        ///< Does this plane measure U,V, or W?
    Orient_t              fOrientation; ///< Is the plane vertical or horizontal?
    SigType_t             fSignalType;  ///< Is the plane induction or collection?
    std::vector<WireGeo*> fWire;        ///< List of wires in this plane
    double                fWirePitch;   ///< pitch of wires in this plane
  };
}

#endif
////////////////////////////////////////////////////////////////////////
