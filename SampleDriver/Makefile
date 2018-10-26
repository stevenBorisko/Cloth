CC := g++
LD := ld
CFLAGS := -std=c++11
LFLAGS := -lGL -lGLU -lglut -lX11 -pthread
EXEC := execute.out

# Main target
compile: $(EXEC)
test: compile
	./$(EXEC)

include Cloth/Cloth.mk

MAIN_OBJDIR := .ObjectFiles/
ObjectDirectory: ClothObjectDirectory
	mkdir -p $(MAIN_OBJDIR)
	@echo "- - - - Main ObjectFile directory created - - - -"

MAIN_DEPS := \
	Cloth/src/DataStructures/Scene/Scene.hpp \
	Cloth/src/Input/Input.hpp
MAIN_OBJ := main.o

# Rules
$(EXEC): $(MAIN_OBJ) $(CLOTH_MAIN_OBJ)
	$(CC) $^ -o $@ $(LFLAGS)

$(MAIN_OBJ): main.cpp $(MAIN_DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

# Clean
clean: ClothClean
	rm -f $(MAIN_OBJ) $(EXEC)