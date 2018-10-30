COLOR_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
COLOR_MAIN_OBJ := $(COLOR_PATH)Color.o
COLOR_CFLAGS := -std=c++11 -O3
COLOR_LFLAGS :=

COLOR_OBJDIR := $(COLOR_PATH).ObjectFiles/
ColorObjectDirectory:
	mkdir -p $(COLOR_OBJDIR)
	@echo "- - - - Color ObjectFile directory created - - - -"

_COLOR_DEPS := Color.hpp
COLOR_DEPS := $(foreach OBJ,$(_COLOR_DEPS),$(COLOR_PATH)$(OBJ))

_COLOR_SUB_OBJS := Color.o
COLOR_SUB_OBJS := $(foreach OBJ,$(_COLOR_SUB_OBJS),$(COLOR_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(COLOR_MAIN_OBJ): $(COLOR_SUB_OBJS)
	@echo "- - - - Color compiled - - - -"
	$(LD) -r $(COLOR_LFLAGS) $(COLOR_SUB_OBJS) -o $@
	@echo "- - - - Color linked - - - -"

# Sub objects
$(COLOR_OBJDIR)%.o: $(COLOR_PATH)%.cpp $(COLOR_DEPS)
	$(CC) -c $(COLOR_CFLAGS) $< -o $@

# Clean
ColorClean:
	rm -f $(COLOR_SUB_OBJS) $(COLOR_MAIN_OBJ)
