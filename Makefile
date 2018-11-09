

all: build
	cd build && make -j$(nproc)

build:
	mkdir -p build && cd build && cmake ..
