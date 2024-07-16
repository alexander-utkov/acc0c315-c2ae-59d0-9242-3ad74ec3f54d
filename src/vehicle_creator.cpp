#include "vehicle_creator.hpp"

using namespace App;

VehicleCreator::~VehicleCreator()
{}

std::unique_ptr<Vehicle>
VehicleCreator::Create(VehicleId id)
{
    switch (id)
    {
    case VehicleId::Motorcycle:
        return std::make_unique<Motorcycle>();
    case VehicleId::Scooter:
        return std::make_unique<Scooter>();
    case VehicleId::Car:
        return std::make_unique<Car>();
    case VehicleId::Bus:
        return std::make_unique<Bus>();
    default:
        return nullptr;
    }
}

std::wstring_view
VehicleCreator::GetName(VehicleId id)
{
    // TBD: C++23: constexpr unique_ptr. Может получиться make_unique в
    // consteval функции а следовательно повторно использовать Create и
    // не создавать объекты только для получения значения характеристики.
    switch (id)
    {
    case VehicleId::Motorcycle:
        return Motorcycle{}.GetName();
    case VehicleId::Scooter:
        return Scooter{}.GetName();
    case VehicleId::Car:
        return Car{}.GetName();
    case VehicleId::Bus:
        return Bus{}.GetName();
    default:
        return L"(unknown)";
    }
}
