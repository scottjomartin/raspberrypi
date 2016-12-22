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

cpp_source := $(filter %.cpp, $(sources))
objects := $(cpp_source:.cpp=.o)
toolchaindir := $(HOME)/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64
host_compiler := $(toolchaindir)/bin/arm-linux-gnueabihf-g++
AR := $(toolchaindir)/bin/arm-linux-gnueabihf-ar
ARFLAGS := rc

include_dirs := $(toolchaindir)/arm-linux-gnueabihf/include \
                $(toolchaindir)/arm-linux-gnueabihf/include/c++/4.8.3 \
                $(toolchaindir)/arm-linux-gnueabihf/include/c++/4.8.3/arm-linux-gnueabihf \
                $(toolchaindir)/arm-linux-gnueabihf/include/c++/4.8.3/backward \
                $(toolchaindir)/arm-linux-gnueabihf/libc/usr/include \
                $(toolchaindir)/arm-linux-gnueabihf/libc/usr/include/arm-linux-gnueabihf \
                $(toolchaindir)/lib/gcc/arm-linux-gnueabihf/4.8.3/include \
                $(toolchaindir)/lib/gcc/arm-linux-gnueabihf/4.8.3/include-fixed \
                $(raspberry_pi_root)

includes := $(addprefix -I, $(include_dirs))

library_dirs := $(toolchaindir)/arm-linux-gnueabihf/lib \
                $(toolchaindir)/arm-linux-gnueabihf/libc/lib/arm-linux-gnueabihf \
                $(toolchaindir)/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf \
                $(target_static_lib_path)

library_dirs := $(addprefix -L, $(library_dirs))

stdlibs := -lgcc -lc -lstdc++

static: $(target_static_lib_path)/lib$(project_name).a

$(target_static_lib_path)/lib$(project_name).a: $(target_static_lib_path) $(objects)
	@echo "============================================================================"
	@echo "===> Building static library lib$(project_name).a"
	@echo "============================================================================"
	$(AR) $(ARFLAGS) $@ $(objects)

executable: $(target_bin_path)/$(project_name)

$(target_bin_path)/$(project_name): $(target_bin_path) $(objects)
	@echo "============================================================================"
	@echo "===> Building executable $(project_name)"
	@echo "============================================================================"
	$(host_compiler) $(library_dirs) $(objects) $(module_libraries) $(stdlibs) -o $@

%.o: %.cpp
	$(host_compiler) $(includes) -c -MD -o $@ $< $(include_dirs)

.PHONY: $(target_static_lib_path)
$(target_static_lib_path):
	@ mkdir -p $(target_static_lib_path)

.PHONY: $(target_bin_path)
$(target_bin_path):
	@ mkdir -p $(target_bin_path)
	
clean:
	rm -f *.o
	rm -f $(target_static_lib_path)/lib$(project_name).a
	rm -f $(target_bin_path)/$(project_name)
	