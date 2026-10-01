.PHONY: build

build:
	chmod u+x build.sh && ./build.sh

prerequisites: build

target: prerequisites 
