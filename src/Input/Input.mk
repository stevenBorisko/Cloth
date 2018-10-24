INPUT_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
INPUT_MAIN_OBJ := $(INPUT_PATH)Input.o
INPUT_CFLAGS := -std=c++11 -O3
INPUT_LFLAGS :=

INPUT_OBJDIR := $(INPUT_PATH).ObjectFiles/
InputObjectDirectory:
	mkdir $(INPUT_OBJDIR)
	@echo "- - - - Input ObjectFile directory created - - - -"

_INPUT_DEPS := Input.hpp ../DataStructures/Scene/Scene.hpp
INPUT_DEPS := $(foreach OBJ,$(_INPUT_DEPS),$(INPUT_PATH)$(OBJ))

_INPUT_SUB_OBJS := \
	Grid.o \
	FilePART.o
INPUT_SUB_OBJS := \
	$(foreach OBJ,$(_INPUT_SUB_OBJS),$(INPUT_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(INPUT_MAIN_OBJ): $(INPUT_SUB_OBJS)
	@echo "- - - - Input compiled - - - -"
	$(LD) -r $(INPUT_LFLAGS) $(INPUT_SUB_OBJS) -o $@
	@echo "- - - - Input linked - - - -"

# Sub objects
$(INPUT_OBJDIR)%.o: $(INPUT_PATH)%.cpp $(INPUT_DEPS)
	$(CC) -c $(INPUT_CFLAGS) $< -o $@

# Clean
InputClean:
	rm -f $(INPUT_SUB_OBJS) $(INPUT_MAIN_OBJ)
