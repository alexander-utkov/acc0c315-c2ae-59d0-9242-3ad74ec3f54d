#pragma once

#include <iterator>
#include <type_traits>
#include <memory>
#include <exception>

#include <cstddef>

#include "vehicles.hpp"
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

        /// Псевдоконтейнер для обхода входных идентификаторов типов как
        /// \ref VehicleId.
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

        /// Псевдоконтейнер над \ref Identifiers; создает экземпляры \ref
        /// Vehicles соответствующих типов при помощи \ref VehicleCreator.
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

    class Args::Identifiers::Iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = VehicleId;
        using difference_type = std::ptrdiff_t;
        using pointer = const char**;

        explicit Iterator(pointer ptr);

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(Iterator other) const;
        bool operator!=(Iterator other) const;

        value_type operator*() const;

    private:
        pointer m_ptr;
    };

    /// Целочисленный идентификатор не содержит цифры.
    /// 
    /// Унарный знак допускается при наличии последующей ненулевой цифры.
    /// 
    /// Следующие идентификаторы допустимы неявно: «1z23» (1), «2.34» (2) -
    /// см. ISO C89/90 atoi.
    class Args::Identifiers::BadIdentifier : public std::exception
    {
    public:
        virtual const char* what() const noexcept
        {
            return "bad ID argument";
        }
    };

    class Args::Vehicles::Iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::unique_ptr<Vehicle>;
        using underlying_iterator = Args::Identifiers::Iterator;
        using difference_type = typename underlying_iterator::difference_type;

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
