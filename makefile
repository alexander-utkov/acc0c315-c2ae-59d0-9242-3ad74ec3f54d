build:
	cl.exe /std:c++20 /EHsc /Zi src/main.cpp src/args.cpp /link /out:main.exe
