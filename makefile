build:
	cl.exe /std:c++20 /EHsc /Zi src/main.cpp src/args.cpp src/vehicle_id.cpp /link /out:main.exe
