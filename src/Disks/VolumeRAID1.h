#pragma once

#include <Disks/createVolume.h>
#include <Disks/VolumeJBOD.h>

namespace DB
{

class VolumeRAID1 : public VolumeJBOD
{
    friend VolumePtr createVolumeFromReservation(const ReservationPtr & reservation, VolumePtr other_volume);
public:
    VolumeRAID1(String name_, Disks disks_, UInt64 max_data_part_size_, bool are_merges_allowed_in_config_)
        : VolumeJBOD(name_, disks_, max_data_part_size_, are_merges_allowed_in_config_)
    {
    }

    VolumeRAID1(
        String name_,
        const Poco::Util::AbstractConfiguration & config,
        const String & config_prefix,
        DiskSelectorPtr disk_selector
    ) : VolumeJBOD(name_, config, config_prefix, disk_selector)
    {
    }

    void updateFromConfig(const Poco::Util::AbstractConfiguration & config, const String & config_prefix)
    {
        VolumeJBOD::updateFromConfig(config, config_prefix);
    }

    VolumeType getType() const override { return VolumeType::RAID1; }

    ReservationPtr reserve(UInt64 bytes) override;
};

using VolumeRAID1Ptr = std::shared_ptr<VolumeRAID1>;
using VolumesRAID1Ptr = std::vector<VolumeRAID1Ptr>;

}
