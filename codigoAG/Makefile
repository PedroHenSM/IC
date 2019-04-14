# Compiler command line.
CXX = gcc

# Compiler flags.
CXX_FLAGS = -Wall \
			-std=c11 \
			-g3

# Used libraries.
CXX_LIBS = -lm

# Final binary file name.
BIN = cntco-exec

# Directory for compiled and temporary files.
BUILD_DIR = build

# Process the list of all files to be compiled.
SRCS = $(wildcard *.c)

# All object files should go to the build directory.
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
# Compute dependencies for source files.
DEPS = $(OBJS:%.o=%.d)

# Default target named after the binary.
$(BIN): $(BUILD_DIR)/$(BIN)

# Actual target of the binary, using all object files as dependencies.
$(BUILD_DIR)/$(BIN): $(OBJS)
    # Just link all the object files.
	$(CXX) $(CXX_FLAGS) $(CXX_LIBS) $^ -o $@

# Include all dependencies.
-include $(DEP)

# Build target for every single object file.
$(BUILD_DIR)/%.o: %.c
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

# This should remove all generated files.
.PHONY: clean
clean:
	-rm $(BUILD_DIR)/$(BIN) $(OBJS) $(DEPS)
