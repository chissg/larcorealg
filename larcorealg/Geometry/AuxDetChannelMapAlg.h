////////////////////////////////////////////////////////////////////////
/// \file  ChannelMapAlg.h
/// \brief Interface to algorithm class for a specific detector channel mapping
/// \ingroup Geometry
///
/// \author  brebel@fnal.gov
////////////////////////////////////////////////////////////////////////
#ifndef GEO_AUXDETCHANNELMAPALG_H
#define GEO_AUXDETCHANNELMAPALG_H

// ROOT libraries
#include "TVector3.h"

// C/C++ standard libraries
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace geo{

  // forward-declaration from geometry
  struct AuxDetGeometryData_t;
  class AuxDetGeo;

  /// \ingroup Geometry
  class AuxDetChannelMapAlg{

    typedef std::pair<uint32_t, size_t> chanAndSV;

  public:

    virtual ~AuxDetChannelMapAlg() = default;

    virtual void Initialize(AuxDetGeometryData_t& geodata) = 0;
    virtual void Uninitialize() = 0;

    // method returns the entry in the sorted AuxDetGeo vector so that the
    // Geometry in turn can return that object
    virtual size_t  NearestAuxDet          (const double*                       point,
                                            std::vector<geo::AuxDetGeo> const& auxDets,
					    double tolerance = 0) const;
    virtual size_t  NearestSensitiveAuxDet (const double*                       point,
                                            std::vector<geo::AuxDetGeo> const& auxDets,
                                            size_t                            & ad,
					    double tolerance = 0) const;
    virtual size_t  ChannelToAuxDet        (std::vector<geo::AuxDetGeo> const& auxDets,
                                            std::string                  const& detName,
                                            uint32_t                     const& channel) const;
    virtual std::pair<size_t, size_t>  ChannelToSensitiveAuxDet(std::vector<geo::AuxDetGeo> const& auxDets,
                                                                std::string                 const& detName,
                                                                uint32_t                    const& channel) const;

    // Experiments must implement these method. It accounts for auxiliary detectors like
    // Multiwire proportional chambers where there is only a single sensitive volume, but
    // multiple channels running through that volume.
    virtual uint32_t PositionToAuxDetChannel(double                      const  worldLoc[3],
                                             std::vector<geo::AuxDetGeo> const& auxDets,
                                             size_t                           & ad,
                                             size_t                           & sv) const = 0;

    virtual const TVector3 AuxDetChannelToPosition(uint32_t                     const& channel,
                                                   std::string                  const& auxDetName,
                                                   std::vector<geo::AuxDetGeo> const& auxDets) const = 0;

 protected:

   std::map<size_t, std::string>             fADGeoToName;         ///< map the AuxDetGeo index to the name
   std::map<std::string, size_t>             fNameToADGeo;         ///< map the names to the AuxDetGeo index
   std::map<size_t, std::vector<chanAndSV> > fADGeoToChannelAndSV; ///< map the AuxDetGeo index to a vector of
                                                                   ///< pairs corresponding to the channel and
                                                                   ///< AuxDetSensitiveGeo index
 };
}
#endif // GEO_AUXDETCHANNELMAPALG_H
