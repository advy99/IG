# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################


HOME    = .
INCLUDE = $(HOME)/include
SRC     = $(HOME)/src
OBJ     = $(HOME)/obj
BIN     = $(HOME)/bin

.SUFFIXES:
.PHONY: x

exe             := $(BIN)/pracs_exe
units_cc        := $(wildcard $(SRC)/*.cc) $(wildcard $(SRC)/*.cpp)
units_o         := $(addsuffix .o, $(basename $(units_cc)))
units_o			 := $(notdir $(units_o))
units_o         := $(addprefix $(OBJ)/, $(units_o))
headers         := $(wildcard $(INCLUDE)/*.h*)
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++11 -g -I/usr/include -I$(INCLUDE)
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

glu_flag_macos  := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL -lSDL2 -lSDL2_mixer
ld_libs_macos  := -framework OpenGL -framework SDL2 -framework SDL2_mixer -framework GLUT $(glu_flag_macos)
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: init $(exe)
	@echo Enlazando para: $(sistoper)
	$(exe)

init:
	-mkdir $(OBJ)
	-mkdir $(BIN)

$(exe): $(units_o) makefile
	@echo $(units_o)
	$(compiler) -o $(exe)  $(units_o) $(ld_libs)

$(OBJ)/%.o : $(SRC)/%.cc
	$(compiler) -c -o $@ $(cc_flags) $<

$(OBJ)/%.o : $(SRC)/%.cpp
	$(compiler) -c -o $@ $(cc_flags) $<

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	-rm -f $(OBJ)/*.o $(BIN)/*_exe
