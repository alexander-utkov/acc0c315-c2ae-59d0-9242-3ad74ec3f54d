# Not cross platform; use cmake instead.
# 
# When using windows you need:
# 
# 1) linux subsystem (git, wsl, etc);
# 2) developer command prompt (vsdevcmd.bat).

BUILD_DIR := build/
ifeq ($(OS),Windows_NT)
	BUILD_DIR := $(BUILD_DIR)windows/
else
	BUILD_DIR := $(BUILD_DIR)other/
endif

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../..
	cd $(BUILD_DIR) && cmake --build .

clean:
	rm -rf build
