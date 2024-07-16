#pragma once

#include <memory>
#include <string_view>

#include "vehicles.hpp"
#include "vehicle_id.hpp"

namespace App
{
    class VehicleCreator
    {
    public:
        virtual ~VehicleCreator();

        static std::wstring_view GetName(VehicleId id);

        virtual std::unique_ptr<Vehicle> Create(VehicleId id);
    };
}
