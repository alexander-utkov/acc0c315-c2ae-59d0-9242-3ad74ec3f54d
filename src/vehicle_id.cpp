#include "vehicle_id.hpp"
#include "vehicle_creator.hpp"

using namespace App;

std::list<std::pair<VehicleId, std::wstring_view>>
App::ListVehicles()
{
    static std::list<std::pair<VehicleId, std::wstring_view>> result =
    {
        {
            VehicleId::Motorcycle,
            VehicleCreator::GetName(VehicleId::Motorcycle),
        },
        {
            VehicleId::Scooter,
            VehicleCreator::GetName(VehicleId::Scooter),
        },
        {
            VehicleId::Car,
            VehicleCreator::GetName(VehicleId::Car),
        },
        {
            VehicleId::Bus,
            VehicleCreator::GetName(VehicleId::Bus),
        },
    };
    return result;
}
