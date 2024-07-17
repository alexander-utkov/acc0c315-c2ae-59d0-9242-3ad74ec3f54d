#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>

#if defined(OS_LINUX)
#include <clocale>
#else
#include <io.h>
#include <fcntl.h>
#endif

#include "args.hpp"
#include "vehicles.hpp"
#include "vehicle_id.hpp"

int main(int argc, char** argv)
try
{
    #if defined(OS_LINUX)
    std::setlocale(LC_ALL, "");
    #else
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    #endif
    
    App::Args args(argc, argv);
    for (std::unique_ptr<App::Vehicle> vehicle : args.GetVehicles())
    {
        if (vehicle)
        {
            std::wcout << vehicle->GetRepresentation() << std::endl;
        }
        else
        {
            std::wcout << L"НЕИЗВЕСТНЫЙ ТИП ТРАНСПОРТА\n" << std::endl;
        }
    }
    return 0;
}
catch (App::HelpMessageRequested)
{
    std::wcout
        << argv[0]
        << L" " << L"ID [ID...]"
        << L" " << L"[--help]"
        << std::endl << std::endl;

    const std::streamsize column_0_width = 2;
    std::wcout
        << std::left << std::setw(column_0_width) << L"ID" << L"   "
        << L"Целочисленный идентификатор транспорта:"
        << std::endl;
    for (auto vehicle : App::ListVehicles())
    {
        std::wcout
            << std::right << std::setw(column_0_width) << L"" << L"   "
            << std::left << std::setw(1) << (int)vehicle.first << L" - "
            << vehicle.second
            << std::endl;
    }
    return 0;
}
catch (const std::exception& exception)
{
    // TODO: .what() как идентификатор перевода.
    std::wcerr
        << argv[0] << L" failed: "
        << exception.what()
        << std::endl;
    return -1;
}
catch (...)
{
    std::wcerr
        << argv[0] << L" failed: "
        << L"неизвестная ошибка"
        << std::endl;
    return -1;
}
