SCENE_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
SCENE_MAIN_OBJ := $(SCENE_PATH)Scene.o
SCENE_CFLAGS := -std=c++11 -O3
SCENE_LFLAGS :=

SCENE_OBJDIR := $(SCENE_PATH).ObjectFiles/
SceneObjectDirectory:
	mkdir -p $(SCENE_OBJDIR)
	@echo "- - - - Scene ObjectFile directory created - - - -"

_SCENE_DEPS := Scene.hpp ../ParticleBinding/ParticleBinding.hpp
SCENE_DEPS := $(foreach OBJ,$(_SCENE_DEPS),$(SCENE_PATH)$(OBJ))

_SCENE_SUB_OBJS := \
	Scene.o
SCENE_SUB_OBJS := \
	$(foreach OBJ,$(_SCENE_SUB_OBJS),$(SCENE_OBJDIR)$(OBJ))


# --- Rules ---

# Main object
$(SCENE_MAIN_OBJ): $(SCENE_SUB_OBJS)
	@echo "- - - - Scene compiled - - - -"
	$(LD) -r $(SCENE_LFLAGS) $(SCENE_SUB_OBJS) -o $@
	@echo "- - - - Scene linked - - - -"

# Sub objects
$(SCENE_OBJDIR)%.o: $(SCENE_PATH)%.cpp $(SCENE_DEPS)
	$(CC) -c $(SCENE_CFLAGS) $< -o $@

# Clean
SceneClean:
	rm -f $(SCENE_SUB_OBJS) $(SCENE_MAIN_OBJ)
