# Compiler Makefile
# Author: John L. Carveth <jlcarveth@gmail.com>
SRC_DIR := src# Source Code Location
OBJ_DIR := obj# Object Output Location
BIN_DIR := out# Binary Output location
DOC_DIR := docs#Document location
CC := gcc
# Output file named ZiroCompiler
TARGET := $(BIN_DIR)/ZiroCompiler
# Include directory
IDIR := include
# All source files to compile
SRC := $(wildcard $(SRC_DIR)/*.c)
# Object files linked to the .c files
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# All Document files to be rendered (all files w/ .md extension)
DOC := $(wildcard $(DOC_DIR)/*.md)

# Compiler flags
CFLAGS := -Wall -D DEBUG -g
CPPFLAGS := -I$(IDIR) -MMD -MP
LDFLAGS := -Llib
LDLIBS := -lm

# PHONY targets so they can still be executed
.PHONY: all clean docs

all : $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(TARGET) $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)/out
# I am using an NPM package (https://www.npmjs.com/package/markdown-to-document)
# to convert markdown documents into webpages with a common format.
docs: 
	mkdir -p $(DOC_DIR)/out
	mdtodoc $(DOC) --dest "docs/out" --layout "page" --theme "github" --highlight-style "atom-one-light"

test:
	./test.sh

-include $(OBJ:.o=.d)