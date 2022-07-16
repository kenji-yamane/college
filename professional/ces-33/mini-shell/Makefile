CC       := gcc
CFLAGS   := -Werror -Wall -Wextra -pedantic -D_POSIX_C_SOURCE -std=c11
LDFLAGS  := -lrt
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)

STRINGS_SRC   := strings/strings.c
IO_SRC        := io/input.c io/output.c
PROCESSES_SRC := processes/child.c processes/job.c
PARSER_SRC    := parser.c
SRC           := $(STRINGS_SRC) $(IO_SRC) $(PROCESSES_SRC) $(PARSER_SRC) main.c

MINISHELL    := minishell
OBJECTS      := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(MINISHELL)

$(APP_DIR)/$(MINISHELL): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(MINISHELL) $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

-include $(DEPENDENCIES)

.PHONY: all build clear clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

clear: clean

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"

