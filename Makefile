# === Config ===
CC = gcc
CFLAGS = -Wall -Wextra -g -MMD
TARGET = shelll

SRC_DIRS = src src/parser
BUILD_DIR = build

# === Sources ===
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# === Make Output Dir If Needed ===
$(shell mkdir -p $(BUILD_DIR)/src $(BUILD_DIR)/src/parser)

# === Default Target ===
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# === Compile .c to build/.o with header tracking ===
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Clean Build Files ===
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# === Include auto-generated header deps ===
-include $(DEPS)

