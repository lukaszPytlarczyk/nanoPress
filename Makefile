# Podstawowy makefile

INC_DIRS = i2c_lib LPS22HD
SRCS_DIRS = i2c_lib LPS22HD
SRCS = main.c gpio.c
# SRCS +=  

DEFS = -DCONROLLER_CONDENSING

#=============================================================================#
# Toolchain configuration
#=============================================================================#

CC = gcc
RM = rm -f

#=============================================================================#
# Project configuration
#=============================================================================#

# project name
PROJECT = nanoPressure

OUT_DIR = out

C_DEFS += -DUSE_FULL_ASSERT=1 -DEBUG -g 

C_EXT = c

C_SRCS = $(wildcard $(patsubst %, %/*.$(C_EXT), . $(SRCS_DIRS)))

C_WARNINGS = -Wall -Wstrict-prototypes -Wextra

#=============================================================================#
# set the VPATH according to SRCS_DIRS
#=============================================================================#

VPATH = $(SRCS_DIRS)

#=============================================================================#
# when using output folder, append trailing slash to its name
#=============================================================================#

ifeq ($(strip $(OUT_DIR)), )
	OUT_DIR_F =
else
	OUT_DIR_F = $(strip $(OUT_DIR))/
endif

#=============================================================================#
# Formating
#=============================================================================#

C_OBJS = $(addprefix $(OUT_DIR_F), $(notdir $(C_SRCS:.$(C_EXT)=.o)))
INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

EXE = $(OUT_DIR_F)$(PROJECT).exe

GENERATED = $(C_OBJS) $(EXE)

#=============================================================================#
# make all
#=============================================================================#

all: make_output_dir $(EXE)

#-----------------------------------------------------------------------------#
# linking - objects -> exe
#-----------------------------------------------------------------------------#

$(EXE) : $(C_OBJS)
	@echo 'Linking target: $(EXE)'
	$(CC) $(C_OBJS) $(LIBS) -o $@
	@echo ' '


#-----------------------------------------------------------------------------#
# compiling - C source -> objects
#-----------------------------------------------------------------------------#

$(OUT_DIR_F)%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(INC_DIRS_F) $(C_DEFS)  $< -o $@
	@echo ' '

#-----------------------------------------------------------------------------#
# create the desired output directory
#-----------------------------------------------------------------------------#

make_output_dir:
	$(shell mkdir $(OUT_DIR_F))

paths:
	@echo 'Inc dirs' $(INC_DIRS_F)
	@echo 'Src dirs' $(C_SRCS)


#=============================================================================#
# make clean
#=============================================================================#

clean:
ifeq ($(strip $(OUT_DIR_F)), )
	@echo 'Removing all generated output files'
else
	@echo 'Removing all generated output files from output directory: $(OUT_DIR_F)'
endif
ifneq ($(strip $(GENERATED)), )
	$(RM) $(GENERATED)
else
	@echo 'Nothing to remove...'
endif
