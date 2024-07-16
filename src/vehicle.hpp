#pragma once

#include <string>

namespace App
{
    class Vehicle
    {
    public:
        Vehicle() = default;

        std::wstring GetRepresentation() const { return L"todo"; }
    };
}
