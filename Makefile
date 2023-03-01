########################################
#
# CMake wrapper commands for common uses
#
########################################

PROJECT_NAME:=learn-cpp

PROJECT_DIR:=$(shell cd -P -- '$(shell dirname -- "$0")' && pwd -P)

.PHONY: config build test help clean realclean eclipse-setup

config:
	cd $(PROJECT_DIR) && cmake -S . -B ./build

build:
	cd $(PROJECT_DIR) && cmake --build ./build

test:
	cd $(PROJECT_DIR)/build/test && ctest --output-on-failure

help:
	cd $(PROJECT_DIR) && cmake --build ./build --target help

clean:
	cd $(PROJECT_DIR) && cmake --build ./build --target clean

realclean:
	cd $(PROJECT_DIR) && rm -rf ./build

eclipse-setup:
	cd $(PROJECT_DIR) && mkdir -p eclipse/$(PROJECT_NAME)
	cd eclipse/$(PROJECT_NAME) && \
	cmake "../../" -G"Eclipse CDT4 - Unix Makefiles"

