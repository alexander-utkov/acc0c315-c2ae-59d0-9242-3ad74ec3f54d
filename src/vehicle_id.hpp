#pragma once

#include <list>
#include <utility>
#include <string_view>

namespace App
{
    enum class VehicleId : int
    {
        Motorcycle = 0,
        Scooter = 1,
        Car = 2,
        Bus = 3,
    };

    /// Получает названия объектов, создаваемых \ref VehicleCreator.
    std::list<std::pair<VehicleId, std::wstring_view>> ListVehicles();
}
