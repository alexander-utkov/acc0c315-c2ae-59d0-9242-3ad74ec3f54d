#pragma once

#include <list>
#include <utility>

namespace App
{
    enum class VehicleId : int
    {
        A = 0, B, C, D,
    };

    std::list<std::pair<VehicleId, const wchar_t*>> ListVehicles();
}
