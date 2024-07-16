#include "vehicle_id.hpp"

std::list<std::pair<App::VehicleId, const wchar_t*>>
App::ListVehicles()
{
    return
    {
        { VehicleId::A, L"test A" },
        { VehicleId::B, L"test B" },
        { VehicleId::C, L"test C" },
        { VehicleId::D, L"test D" },
    };
}
