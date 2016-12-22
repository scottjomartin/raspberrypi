# ****************************************************************************** 
# ******************************************************************************
# ***
# *** PURPOSE: Makefile for Raspberry Pi projects.
# ***
# *** AUTHOR : Scott Martin
# ***
# *** DATE   : 22-Sep-2016
# ***
# ******************************************************************************
# ******************************************************************************

SHELL := /bin/bash

ifndef raspberry_pi_root
	raspberry_pi_root := $(shell pwd)
	export raspberry_pi_root
endif

ifndef target_static_lib_path
	target_static_lib_path := $(raspberry_pi_root)/release/lib
	export target_static_lib_path
endif

ifndef target_bin_path
	target_bin_path := $(raspberry_pi_root)/release/bin
	export target_bin_path
endif

ifndef target_obj_path
	target_obj_path := $(raspberry_pi_root)/release/obj
	export target_obj_path
endif

ifndef toolchain_dir
	toolchain_dir = $(raspberry_pi_root)/toolchain/arm-bcm2708/arm-bcm2708hardfp-linux-gnueabi
endif

# Define all of the directories to build
dirs = \
	os \
	drivers \
	led_test \
	piezoapp

all: $(dirs)

clean:
	@set -e;\
	for dir in $(dirs);\
	do\
		echo "==================================================================";\
		echo "===> CLEANING MODULE $$dir";\
		echo "==================================================================";\
		pushd $(raspberry_pi_root)/$$dir;\
		make clean;\
		popd;\
	done

$(info dirs = $(dirs))
.PHONY: $(dirs)
$(dirs) :
	@echo "=================================================================="
	@echo "===> MAKING MODULE $@"
	@echo "=================================================================="
	cd $@ && $(MAKE) objdir=$(target_obj_path)/$@ all

