#include <iostream>
#include <iomanip>
#include <exception>

#include "args.hpp"

int main(int argc, char** argv)
try
{
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
}
catch (App::HelpMessageRequested)
{
    std::wcout
        << argv[0] << L" "
        << "ID [ID...]"
        << std::endl << std::endl;

    const std::streamsize column_0_width = 5;
    std::wcout
        << std::setw(column_0_width) << L"ID" << L" "
        << L"Целочисленный идентификатор транспорта."
        << std::endl;
}
catch (const std::exception& exception)
{
    // TODO: Попробовать перевести.
    std::wcerr << exception.what() << std::endl;
}
catch (...)
{
    std::wcerr << L"неизвестная ошибка" << std::endl;
}
