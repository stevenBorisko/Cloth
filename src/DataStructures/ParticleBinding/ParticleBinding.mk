PARTICLEBINDING_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
PARTICLEBINDING_MAIN_OBJ := $(PARTICLEBINDING_PATH)ParticleBinding.o
PARTICLEBINDING_CFLAGS := -std=c++11 -O3
PARTICLEBINDING_LFLAGS :=

PARTICLEBINDING_OBJDIR := $(PARTICLEBINDING_PATH).ObjectFiles/
ParticleBindingObjectDirectory:
	mkdir -p $(PARTICLEBINDING_OBJDIR)
	@echo "- - - - ParticleBinding ObjectFile directory created - - - -"

_PARTICLEBINDING_DEPS := ParticleBinding.hpp
PARTICLEBINDING_DEPS := $(foreach OBJ,$(_PARTICLEBINDING_DEPS),$(PARTICLEBINDING_PATH)$(OBJ))

_PARTICLEBINDING_SUB_OBJS := \
	Binding.o \
	Particle.o
PARTICLEBINDING_SUB_OBJS := \
	$(foreach OBJ,$(_PARTICLEBINDING_SUB_OBJS),$(PARTICLEBINDING_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(PARTICLEBINDING_MAIN_OBJ): $(PARTICLEBINDING_SUB_OBJS)
	@echo "- - - - ParticleBinding compiled - - - -"
	$(LD) -r $(PARTICLEBINDING_LFLAGS) $(PARTICLEBINDING_SUB_OBJS) -o $@
	@echo "- - - - ParticleBinding linked - - - -"

# Sub objects
$(PARTICLEBINDING_OBJDIR)%.o: $(PARTICLEBINDING_PATH)%.cpp $(PARTICLEBINDING_DEPS) 
	$(CC) -c $(PARTICLEBINDING_CFLAGS) $< -o $@

# Clean
ParticleBindingClean:
	rm -f $(PARTICLEBINDING_SUB_OBJS) $(PARTICLEBINDING_MAIN_OBJ)
