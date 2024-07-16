#pragma once

#include <iterator>
#include <type_traits>
#include <memory>
#include <exception>

#include <cstddef>

#include "vehicle.hpp"
#include "vehicle_id.hpp"

namespace App
{
    struct HelpMessageRequested
    {};

    class Args final
    {
    public:
        /// \exception \ref HelpMessageRequested Сигнальное исключение когда
        /// пользователь запрашивает справку. Его смысл в том, чтобы вынести
        /// код данной справки в \ref main.
        Args(int argc, char** argv);

        class Identifiers
        {
        public:
            Identifiers(const Args& owner);

            class Iterator;
            class BadIdentifier;

            Iterator begin() const;
            Iterator end() const;

        private:
            const Args& m_owner;
        };

        inline Identifiers GetIdentifiers() const &
        {
            return *this;
        }

        class Vehicles
        {
        public:
            Vehicles(const Args& owner);

            class Iterator;

            Iterator begin() const;
            Iterator end() const;

        private:
            const Args& m_owner;
        };

        inline Vehicles GetVehicles() const &
        {
            return *this;
        }

    private:
        int m_argc;
        char** m_argv;
    };

    class Args::Identifiers::Iterator :
        public std::iterator<
            std::input_iterator_tag,
            VehicleId,
            std::ptrdiff_t,
            const char**,
            int
        >
    {
    public:
        explicit Iterator(pointer ptr);

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(Iterator other) const;
        bool operator!=(Iterator other) const;

        value_type operator*() const;

    private:
        pointer m_ptr;
    };

    /// Идентификатор начинается не с цифры: «-1», «z0». Однако следующие
    /// идентификаторы допустимы: «1z23» (1), «1.23» (1) - см. ISO C89/90
    /// atoi.
    class Args::Identifiers::BadIdentifier : public std::exception
    {
    public:
        virtual const char* what() const
        {
            return "bad ID argument";
        }
    };

    class Args::Vehicles::Iterator :
        public std::iterator<
            std::input_iterator_tag,
            std::unique_ptr<Vehicle>,
            typename Args::Identifiers::Iterator::difference_type,
            Args::Identifiers::Iterator,
            int
        >
    {
    public:
        using underlying_iterator = pointer;

        explicit Iterator(underlying_iterator it);

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(Iterator other) const;
        bool operator!=(Iterator other) const;

        value_type operator*() const;

    private:
        underlying_iterator m_it;
    };
}
