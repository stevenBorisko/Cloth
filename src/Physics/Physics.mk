PHYSICS_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
PHYSICS_MAIN_OBJ := $(PHYSICS_PATH)Physics.o
PHYSICS_CFLAGS := -std=c++11 -O3
PHYSICS_LFLAGS :=

PHYSICS_OBJDIR := $(PHYSICS_PATH).ObjectFiles/
PhysicsObjectDirectory:
	mkdir -p $(PHYSICS_OBJDIR)
	@echo "- - - - Physics ObjectFile directory created - - - -"

_PHYSICS_DEPS := Physics.hpp ../DataStructures/Scene/Scene.hpp
PHYSICS_DEPS := $(foreach OBJ,$(_PHYSICS_DEPS),$(PHYSICS_PATH)$(OBJ))

_PHYSICS_SUB_OBJS := \
	Collisions.o \
	Forces.o \
	PhysicsEngine.o \
	UpdateParticle.o
PHYSICS_SUB_OBJS := \
	$(foreach OBJ,$(_PHYSICS_SUB_OBJS),$(PHYSICS_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(PHYSICS_MAIN_OBJ): $(PHYSICS_SUB_OBJS)
	@echo "- - - - Physics compiled - - - -"
	$(LD) -r $(PHYSICS_LFLAGS) $(PHYSICS_SUB_OBJS) -o $@
	@echo "- - - - Physics linked - - - -"

# Sub objects
$(PHYSICS_OBJDIR)%.o: $(PHYSICS_PATH)%.cpp $(PHYSICS_DEPS)
	$(CC) -c $(PHYSICS_CFLAGS) $< -o $@

# Clean
PhysicsClean:
	rm -f $(PHYSICS_SUB_OBJS) $(PHYSICS_MAIN_OBJ)
