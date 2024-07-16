#pragma once

#include <string>
#include <string_view>
#include <utility>

#include <cstddef>

namespace App
{
    template<class T>
    class VehicleFeature
    {
    public:
        using value_type = T;

        VehicleFeature() = default;

        template<class U>
        VehicleFeature(U&& value) :
            m_value(std::forward<U>(value))
        {}

        virtual std::wstring_view GetName() const = 0;

        inline value_type GetValue() const
        {
            return m_value;
        }

    protected:
        value_type m_value;
    };
}

#define APP_DEFINE_VEHICLE_FEATURE(type, name, label)                          \
    class name##VehicleFeature :                                               \
        public App::VehicleFeature<type>                                       \
    {                                                                          \
    public:                                                                    \
        using App::VehicleFeature<type>::VehicleFeature;                       \
                                                                               \
        using App::VehicleFeature<type>::GetValue;                             \
                                                                               \
        virtual std::wstring_view GetName() const                              \
        {                                                                      \
            return label;                                                      \
        }                                                                      \
    };

namespace App
{
    APP_DEFINE_VEHICLE_FEATURE(
        std::wstring_view,
        Name,
        L"Наименование транспорта"
    );
    APP_DEFINE_VEHICLE_FEATURE(
        std::size_t,
        Wheels,
        L"Кол-во колес"
    );
    APP_DEFINE_VEHICLE_FEATURE(
        std::size_t,
        MaxSpeed,
        L"Максимальная скорость"
    );
    APP_DEFINE_VEHICLE_FEATURE(
        std::size_t,
        MaxPassengers,
        L"Максимальное количество пассажиров"
    );
}

#undef APP_DEFINE_VEHICLE_FEATURE
