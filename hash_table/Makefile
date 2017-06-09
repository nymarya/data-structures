# Makefile #

# Mayra D A #


## DIRS
INCDIR = include
SRCDIR = src
OBJDIR = build

# TARGET
TARGET = $(OBJDIR)/drive_hash

## EXTENSIONS
SRCEXT = cpp

## SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

## OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

## COMPILER
CC = g++

## FLAGS
WARN = -Wall
INCFLAG = -I $(INCDIR)
CFLAGS = $(WARN) -std=c++11 $(INCFLAG) -c
COMPILE_FLAGS = $(WARN) -std=c++11 $(INCFLAG) -g

all: $(TARGET) clean	
	
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Creating directories..."
	@mkdir -p $(OBJDIR)
	$(CC) $(COMPILE_FLAGS) $(CFLAGS) $^ -o $@

$(TARGET): $(OBJS)
	@echo "Compiling..."
	$(CC) $^ $(INLFLAG) -o $@  

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR)/*.o

.PHONY: debug 
debug: dirs 	
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJS))
