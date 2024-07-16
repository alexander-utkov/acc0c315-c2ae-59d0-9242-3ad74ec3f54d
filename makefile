_build:
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build .

clean:
	rm -rf build
