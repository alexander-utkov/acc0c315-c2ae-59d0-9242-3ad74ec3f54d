#include "args.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>

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

App::Args::Args(int argc, char** argv) :
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

App::Args::Identifiers::Identifiers(const Args& owner) :
    m_owner(owner)
{}

App::Args::Identifiers::Iterator
App::Args::Identifiers::begin()
const
{
    return Iterator((const char**)m_owner.m_argv + 1);
}

App::Args::Identifiers::Iterator
App::Args::Identifiers::end()
const
{
    return Iterator((const char**)m_owner.m_argv + m_owner.m_argc);
}

#pragma endregion
#pragma region App::Args::Identifiers::Iterator

App::Args::Identifiers::Iterator::Iterator(pointer ptr) :
    m_ptr(ptr)
{}

App::Args::Identifiers::Iterator&
App::Args::Identifiers::Iterator::operator++()
{
    m_ptr++;
    return *this;
}

App::Args::Identifiers::Iterator
App::Args::Identifiers::Iterator::operator++(int)
{
    Iterator result = *this;
    ++(*this);
    return result;
}

bool
App::Args::Identifiers::Iterator::operator==(Iterator other)
const
{
    return m_ptr == other.m_ptr;
}

bool
App::Args::Identifiers::Iterator::operator!=(Iterator other)
const
{
    return m_ptr != other.m_ptr;
}

App::Args::Identifiers::Iterator::value_type
App::Args::Identifiers::Iterator::operator*()
const
{
    if (std::isdigit(**m_ptr) == 0)
    {
        throw BadIdentifier();
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

App::Args::Vehicles::Vehicles(const Args& owner) :
    m_owner(owner)
{}

App::Args::Vehicles::Iterator
App::Args::Vehicles::begin()
const
{
    return Iterator(m_owner.GetIdentifiers().begin());
}

App::Args::Vehicles::Iterator
App::Args::Vehicles::end()
const
{
    return Iterator(m_owner.GetIdentifiers().end());
}

#pragma endregion
#pragma region App::Args::Vehicles::Iterator

App::Args::Vehicles::Iterator::Iterator(underlying_iterator it) :
    m_it(it)
{}

App::Args::Vehicles::Iterator&
App::Args::Vehicles::Iterator::operator++()
{
    m_it++;
    return *this;
}

App::Args::Vehicles::Iterator
App::Args::Vehicles::Iterator::operator++(int)
{
    Iterator result = *this;
    ++(*this);
    return result;
}

bool
App::Args::Vehicles::Iterator::operator==(Iterator other)
const
{
    return m_it == other.m_it;
}

bool
App::Args::Vehicles::Iterator::operator!=(Iterator other)
const
{
    return m_it != other.m_it;
}

App::Args::Vehicles::Iterator::value_type
App::Args::Vehicles::Iterator::operator*()
const
{
    // #error TODO
    throw "todo";
    return nullptr;
}

#pragma endregion
