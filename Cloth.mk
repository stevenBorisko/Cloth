# --- Definitions ---

CLOTH_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
CLOTH_MAIN_OBJ := $(CLOTH_PATH)Cloth.o
CLOTH_CFLAGS := -std=c++11 -O3
CLOTH_LFLAGS :=

include $(CLOTH_PATH)lib/Matrix4/Matrix4.mk
include $(CLOTH_PATH)lib/Color/Color.mk
include $(CLOTH_PATH)src/DataStructures/ParticleBinding/ParticleBinding.mk
include $(CLOTH_PATH)src/DataStructures/Scene/Scene.mk
include $(CLOTH_PATH)src/DataStructures/Triangle/Triangle.mk
include $(CLOTH_PATH)src/Input/Input.mk
include $(CLOTH_PATH)src/Physics/Physics.mk

CLOTH_OBJDIR := $(CLOTH_PATH).ObjectFiles/
ClothObjectDirectory: \
	Matrix4ObjectDirectory \
	ParticleBindingObjectDirectory \
	SceneObjectDirectory \
	TriangleObjectDirectory \
	InputObjectDirectory \
	PhysicsObjectDirectory \
	ColorObjectDirectory
	mkdir -p $(CLOTH_OBJDIR)
	@echo "- - - - Cloth ObjectFile directory created - - - -"

_CLOTH_DEPS :=
CLOTH_DEPS := $(foreach OBJ,$(_CLOTH_DEPS),$(CLOTH_PATH)$(OBJ))

_CLOTH_SUB_OBJS :=
CLOTH_SUB_OBJS := $(foreach OBJ,$(_CLOTH_SUB_OBJS),$(CLOTH_OBJDIR)$(OBJ))

# --- Rules ---

# Main object
$(CLOTH_MAIN_OBJ): \
	$(CLOTH_SUB_OBJS) \
	$(MATRIX4_MAIN_OBJ) \
	$(PARTICLEBINDING_MAIN_OBJ) \
	$(SCENE_MAIN_OBJ) \
	$(TRIANGLE_MAIN_OBJ) \
	$(INPUT_MAIN_OBJ) \
	$(PHYSICS_MAIN_OBJ) \
	$(COLOR_MAIN_OBJ)
	@echo "- - - - Cloth compiled - - - -"
	$(LD) -r $(CLOTH_LFLAGS) $^ -o $@
	@echo "- - - - Cloth linked - - - -"

# Sub objects
$(CLOTH_OBJDIR)%.o: $(CLOTH_PATH)%.cpp $(CLOTH_DEPS)
	$(CC) -c $(CLOTH_CFLAGS) $< -o $@

# Clean
ClothClean: \
	Matrix4Clean \
	ParticleBindingClean \
	SceneClean \
	TriangleClean \
	InputClean \
	PhysicsClean \
	ColorClean
	rm -f $(CLOTH_SUB_OBJS) $(CLOTH_MAIN_OBJ)
