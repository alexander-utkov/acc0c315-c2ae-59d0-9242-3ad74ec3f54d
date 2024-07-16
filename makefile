SCR_FILES := $(wildcard src/*.cpp)

build:
	cl.exe /std:c++20 /EHsc /Zi $(SCR_FILES) /link /out:main.exe
