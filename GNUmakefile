#!gmake 

.PHONY: debug release createDebugConfiguration createReleaseConfiguration install clean all

BUILD ?= release
PYTHON ?= python
CMAKE ?= cmake

default: $(BUILD)

clobber:
	rm -rf debug release

clean:
	@-$(MAKE) -C debug clean
	@-$(MAKE) -C release clean

.DEFAULT:
	@$(MAKE) -C $(BUILD) $(MAKECMDGOALS)

debugSyncData:
	@-$(CMAKE) -E copy_directory data/ debug/bin/data

releaseSyncData:
	@-$(CMAKE) -E copy_directory data/ release/bin/data

debugConfig: 
	@mkdir -p debug
	@cd debug; $(CMAKE) .. -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"

debug: debug/Makefile 
	@$(MAKE) -C $@

debug/Makefile:
	@mkdir -p debug
	@cd debug; $(CMAKE) .. -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"

releaseConfig:
	@mkdir -p release
	@cd release; $(CMAKE) .. -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles"


release: release/Makefile 
	@$(MAKE) -C $@

release/Makefile:
	@mkdir -p release
	@cd release; $(CMAKE) .. -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles"

#Just for reference here
xcode:
	@mkdir -p XCode
	@cd XCode; $(CMAKE) -G Xcode .. 

