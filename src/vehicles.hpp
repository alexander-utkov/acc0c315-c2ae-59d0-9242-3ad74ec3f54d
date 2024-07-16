#pragma once

#include <string>
#include <string_view>

#if defined(__GNUC__)
#include <fmt/format.h>
#include <fmt/xchar.h>
using fmt::format;
#else
#include <format>
using std::format;
#endif

#include "vehicle_features.hpp"

#define APP_ADD_VEHICLE_FEATURE(name, member)                                  \
    protected:                                                                 \
        App::name##VehicleFeature member;                                      \
                                                                               \
    public:                                                                    \
        inline                                                                 \
        typename decltype(member)::value_type                                  \
        Get##name()                                                            \
        const                                                                  \
        {                                                                      \
            return member.GetValue();                                          \
        }

namespace App
{
    /// Базовый класс транспорта, в частности реализации - наземного.
    class Vehicle
    {
        // NOTE: Из-за наличия характеристики с именем «Name» может возникнуть
        // путаница:
        // 
        // - m_*.GetName(); // статическое имя характеристики «*»
        // - GetName();     // значение характеристики «Name»
        //   - m_name.GetValue()

        APP_ADD_VEHICLE_FEATURE(Name, m_name);
        APP_ADD_VEHICLE_FEATURE(Wheels, m_wheels);
        APP_ADD_VEHICLE_FEATURE(MaxSpeed, m_max_speed);

    public:
        virtual ~Vehicle() = default;

        /// Получает представление всех характеристик.
        virtual std::wstring GetRepresentation() const
        {
            return format(
                (
                    L"{}: {}\n"
                    L"{}: {}\n"
                    L"{}: {}км/ч\n"
                ),
                m_name.GetName(),
                m_name.GetValue(),
                m_wheels.GetName(),
                m_wheels.GetValue(),
                m_max_speed.GetName(),
                m_max_speed.GetValue()
            );
        }

    protected:
        Vehicle(
            typename decltype(m_name)::value_type name,
            typename decltype(m_wheels)::value_type wheels,
            typename decltype(m_max_speed)::value_type max_speed
        ) :
            m_name(name),
            m_wheels(wheels),
            m_max_speed(max_speed)
        {}
    };

    class Motorcycle : public Vehicle
    {
    public:
        Motorcycle() :
            Vehicle(L"мотоцикл", 2, 200)
        {}
    };

    class Scooter : public Vehicle
    {
    public:
        Scooter() :
            Vehicle(L"самокат", 3, 40)
        {}
    };

    class Car : public Vehicle
    {
    public:
        Car() :
            Vehicle(L"автомобиль", 4, 150)
        {}
    };

    class Bus : public Vehicle
    {
        APP_ADD_VEHICLE_FEATURE(MaxPassengers, m_max_passengers);

    public:
        Bus() :
            Vehicle(L"автобус", 6, 100),
            m_max_passengers(20)
        {}

        Bus(
            typename decltype(m_max_passengers)::value_type max_passengers
        ) :
            Vehicle(L"автобус", 6, 100),
            m_max_passengers(max_passengers)
        {}

        std::wstring GetRepresentation() const override
        {
            return format(
                (
                    L"{}"
                    L"{}: {}\n"
                ),
                Vehicle::GetRepresentation(),
                m_max_passengers.GetName(),
                m_max_passengers.GetValue()
            );
        }
    };
}
