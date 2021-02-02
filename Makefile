export PROJECT_NAME = cpp
.PHONY: $(PROJECT_NAME)
build:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=FALSE -D PROJECT_NAME=$(PROJECT_NAME) && make
run:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=FALSE -D PROJECT_NAME=$(PROJECT_NAME) && make && cd .. && ./build/$(PROJECT_NAME)
run-test:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=TRUE -D PROJECT_NAME=$(PROJECT_NAME) && make && cd .. && ./build/$(PROJECT_NAME)
