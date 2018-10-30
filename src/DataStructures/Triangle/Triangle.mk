TRIANGLE_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
TRIANGLE_MAIN_OBJ := $(TRIANGLE_PATH)Triangle.o
TRIANGLE_CFLAGS := -std=c++11 -O3
TRIANGLE_LFLAGS :=

TRIANGLE_OBJDIR := $(TRIANGLE_PATH).ObjectFiles/
TriangleObjectDirectory:
	mkdir -p $(TRIANGLE_OBJDIR)
	@echo "- - - - Triangle ObjectFile directory created - - - -"

_TRIANGLE_DEPS := \
	Triangle.hpp \
	../ParticleBinding/ParticleBinding.hpp \
	../../Graphics/Color/Color.hpp
TRIANGLE_DEPS := $(foreach OBJ,$(_TRIANGLE_DEPS),$(TRIANGLE_PATH)$(OBJ))

_TRIANGLE_SUB_OBJS := Triangle.o Plane.o
TRIANGLE_SUB_OBJS := \
	$(foreach OBJ,$(_TRIANGLE_SUB_OBJS),$(TRIANGLE_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(TRIANGLE_MAIN_OBJ): $(TRIANGLE_SUB_OBJS)
	@echo "- - - - Triangle compiled - - - -"
	$(LD) -r $(TRIANGLE_LFLAGS) $(TRIANGLE_SUB_OBJS) -o $@
	@echo "- - - - Triangle linked - - - -"

# Sub objects
$(TRIANGLE_OBJDIR)%.o: $(TRIANGLE_PATH)%.cpp $(TRIANGLE_DEPS)
	$(CC) -c $(TRIANGLE_CFLAGS) $< -o $@

# Clean
TriangleClean:
	rm -f $(TRIANGLE_SUB_OBJS) $(TRIANGLE_MAIN_OBJ)
