#########################################
# C2S2 Compiler Makefile
#########################################

### Set colors because I like pretty colors
BLUE  =\033[0;34m
PURPLE=\033[0;35m
GREEN =\033[0;32m
RED   =\033[0;31m
ORANGE=\033[0;33m
CYAN  =\033[0;36m
RESET =\033[0m

### Set information about our C++ compiler
LANGUAGE?=C
ifeq ($(LANGUAGE), CPP)
	CC = g++
	SOURCE_SUFFIX = .cpp
	HEADER_SUFFIX = .hpp
else ifeq ($(LANGUAGE), C)
	CC = gcc
	SOURCE_SUFFIX = .c
	HEADER_SUFFIX = .h
else
$(error Language not supported. Please use C or C++)
endif

LDFLAGS = -lm
CFLAGS = -Wall -O3 -Iboard_utils

# Delete default list of suffixes for recipes
.SUFFIXES:

### Compile targets
SOURCES := $(notdir $(wildcard src/*$(SOURCE_SUFFIX)))
OBJECTS  = $(SOURCES:$(SOURCE_SUFFIX)=.o)
TARGETS  = $(basename $(notdir $(wildcard tests/*$(SOURCE_SUFFIX))))

all : intro $(TARGETS) end

.PHONY: intro build end

end:
	@echo ""
	@echo -e "${GREEN}########################################${RESET}"
	@echo -e "${GREEN}## All tests built in build directory${RESET}"
	@echo -e "${GREEN}########################################${RESET}"
	@echo ""

intro :
	@echo ""
	@echo -e "${PURPLE}########################################${RESET}"
	@echo -e "${PURPLE}## C2S2 Build System${RESET}"
	@echo -e "${PURPLE}########################################${RESET}"
	@echo ""

build :
	@echo -e "${BLUE} - Making Build Directory in ${PWD}/build${RESET}"
	@rm -rf build
	@mkdir build


flash: blink.hex
	python3 board_utils/util/caravel_hkflash.py blink.hex

%.o :
	@echo -e "${CYAN} - Building object: $@${RESET}"
	$(eval objectfile=$(addprefix build/,$@))
	$(eval sourcefile=$(addprefix src/,$(notdir $(subst .o,$(SOURCE_SUFFIX),$(objectfile)))))
	@$(CC) $(CFLAGS) -c -o $(objectfile) $(sourcefile) -Iinclude

$(TARGETS) : intro build $(OBJECTS)
	$(eval testfile=$(addprefix tests/,$(addsuffix $(SOURCE_SUFFIX),$@)))
	$(eval object=$(addprefix build/,$(addsuffix .o,$@)))
	$(eval binary=$(addprefix build/,$@))
	@echo -e "${ORANGE} - Building executable: $@${RESET}"
	@$(CC) $(CFLAGS) -c -o $(object) $(testfile) -Iinclude
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(binary) $(addprefix build/,$(OBJECTS)) $(object)
	