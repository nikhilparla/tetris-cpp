TARGET = tetris

CC=g++
# compilation flags here
CFLAGS= -c -DLINUX -I. -LSDL/lib

LINKER=g++
#linking flags here
LDFLAGS= -lSDL -lSDL_gfx

# directoris of sources
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCLUDEDIR = include

SOURCES		:= $(wildcard $(SRCDIR)/*.cpp) 
INCLUDES	:= $(wildcard $(INCLUDEDIR)/*.h) 
OBJECTS 	:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE=tetris

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LDFLAGS) -o	$@
	@echo "Linking Complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $< -o $@
	@echo "Compilation Complete!"

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
	@echo "Cleanup Complete!"

