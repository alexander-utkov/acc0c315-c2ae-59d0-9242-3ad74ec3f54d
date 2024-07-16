#include <iostream>
#include <iomanip>
#include <locale>
#include <exception>

#include "args.hpp"
#include "vehicle.hpp"
#include "vehicle_id.hpp"

int main(int argc, char** argv)
try
{
    std::locale locale("rus_rus.1251");
    std::wcout.imbue(locale);
    std::wcerr.imbue(locale);
    
    App::Args args(argc, argv);
    for (std::unique_ptr<App::Vehicle> vehicle : args.GetVehicles())
    {
        if (vehicle)
        {
            std::wcout << vehicle->GetRepresentation() << std::endl;
        }
        else
        {
            std::wcout << L"НЕИЗВЕСТНЫЙ ТИП ТРАНСПОРТА" << std::endl;
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
    // TODO: Попробовать перевести.
    std::wcerr << exception.what() << std::endl;
    return -1;
}
catch (...)
{
    std::wcerr << L"неизвестная ошибка" << std::endl;
    return -1;
}
