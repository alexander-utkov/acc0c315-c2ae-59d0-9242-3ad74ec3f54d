#include "args.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>

#include "vehicle_creator.hpp"

using namespace App;

#pragma region App::Args

bool IsHelpOption(const char* option)
{
    return
    (
        #if !defined(__GNUC__)
        std::strcmp(option, "/?") == 0 ||
        #endif
        std::strcmp(option, "-h") == 0 ||
        std::strcmp(option, "--help") == 0
    );
}

Args::Args(int argc, char** argv) :
    m_argc(argc),
    m_argv(argv)
{
    if (argc < 2 || IsHelpOption(argv[argc - 1]))
    {
        throw HelpMessageRequested();
    }
}

#pragma endregion
#pragma region App::Args::Identifiers

Args::Identifiers::Identifiers(const Args& owner) :
    m_owner(owner)
{}

Args::Identifiers::Iterator
Args::Identifiers::begin()
const
{
    return Iterator((const char**)m_owner.m_argv + 1);
}

Args::Identifiers::Iterator
Args::Identifiers::end()
const
{
    return Iterator((const char**)m_owner.m_argv + m_owner.m_argc);
}

#pragma endregion
#pragma region App::Args::Identifiers::Iterator

Args::Identifiers::Iterator::Iterator(pointer ptr) :
    m_ptr(ptr)
{}

Args::Identifiers::Iterator&
Args::Identifiers::Iterator::operator++()
{
    m_ptr++;
    return *this;
}

Args::Identifiers::Iterator
Args::Identifiers::Iterator::operator++(int)
{
    Iterator result = *this;
    ++(*this);
    return result;
}

bool
Args::Identifiers::Iterator::operator==(Iterator other)
const
{
    return m_ptr == other.m_ptr;
}

bool
Args::Identifiers::Iterator::operator!=(Iterator other)
const
{
    return m_ptr != other.m_ptr;
}

Args::Identifiers::Iterator::value_type
Args::Identifiers::Iterator::operator*()
const
{
    if (std::isdigit(**m_ptr) == 0)
    {
        // Допускаем унарный знак: '[+-](0|[1-9][0-9]*)'.
        if (**m_ptr == '+' || **m_ptr == '-')
        {
            char next = *(*m_ptr + 1);
            if (std::isdigit(next) == 0)
            {
                throw BadIdentifier();
            }
            else if (next == '0')
            {
                if (*(*m_ptr + 2) != '\0')
                {
                    throw BadIdentifier();
                }
            }
        }
        else throw BadIdentifier();
    }
    using underlying_type = std::underlying_type_t<value_type>;
    underlying_type raw;
    if constexpr (std::is_same_v<underlying_type, int>)
    {
        raw = std::atoi(*m_ptr);
    }
    else static_assert(std::is_same_v<underlying_type, int>);
    return static_cast<value_type>(raw);
}

#pragma endregion
#pragma region App::Args::Vehicles

Args::Vehicles::Vehicles(const Args& owner) :
    m_owner(owner)
{}

Args::Vehicles::Iterator
Args::Vehicles::begin()
const
{
    return Iterator(m_owner.GetIdentifiers().begin());
}

Args::Vehicles::Iterator
Args::Vehicles::end()
const
{
    return Iterator(m_owner.GetIdentifiers().end());
}

#pragma endregion
#pragma region App::Args::Vehicles::Iterator

Args::Vehicles::Iterator::Iterator(underlying_iterator it) :
    m_it(it)
{}

Args::Vehicles::Iterator&
Args::Vehicles::Iterator::operator++()
{
    m_it++;
    return *this;
}

Args::Vehicles::Iterator
Args::Vehicles::Iterator::operator++(int)
{
    Iterator result = *this;
    ++(*this);
    return result;
}

bool
Args::Vehicles::Iterator::operator==(Iterator other)
const
{
    return m_it == other.m_it;
}

bool
Args::Vehicles::Iterator::operator!=(Iterator other)
const
{
    return m_it != other.m_it;
}

Args::Vehicles::Iterator::value_type
Args::Vehicles::Iterator::operator*()
const
{
    return App::VehicleCreator{}.Create(*m_it);
}

#pragma endregion
