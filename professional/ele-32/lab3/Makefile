CC       := g++
CFLAGS   := -Werror -Wall -Wextra -pedantic -std=c++17
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)

RANDOM_SRC         := random/random.cpp
BSC_SRC         := binary/binary.cpp binary/bsc_canal.cpp
AWGN_SRC           := binary/awgn_canal.cpp
CONVOLUTIONAL_SRC  := convolutional/convolutional.cpp convolutional/trellis.cpp

COMMON_SRC         := $(RANDOM_SRC) $(BSC_SRC) $(CONVOLUTIONAL_SRC)
ERRORS_SRC         := main.cpp $(COMMON_SRC)
LOGPROB_SRC        := logprob.cpp $(COMMON_SRC)
EUCLIDIAN_SRC      := euclidian.cpp $(COMMON_SRC) $(AWGN_SRC)
ESTIMATE_TIMES_SRC := estimate_times.cpp $(COMMON_SRC)
TEST_ENCODE_SRC    := test_encode.cpp $(COMMON_SRC)
TEST_DECODE_SRC    := test_decode.cpp $(COMMON_SRC)

ERRORS      := errors
ERRORS_OBJS := $(ERRORS_SRC:%.cpp=$(OBJ_DIR)/%.o)
ERRORS_DEPS := $(ERRORS_OBJS:.o=.d)

LOGPROB      := logprob
LOGPROB_OBJS := $(LOGPROB_SRC:%.cpp=$(OBJ_DIR)/%.o)
LOGPROB_DEPS := $(LOGPROB_OBJS:.o=.d)

EUCLIDIAN      := euclidian
EUCLIDIAN_OBJS := $(EUCLIDIAN_SRC:%.cpp=$(OBJ_DIR)/%.o)
EUCLIDIAN_DEPS := $(EUCLIDIAN_OBJS:.o=.d)

ESTIMATE_TIMES      := estimate-times
ESTIMATE_TIMES_OBJS := $(ESTIMATE_TIMES_SRC:%.cpp=$(OBJ_DIR)/%.o)
ESTIMATE_TIMES_DEPS := $(ESTIMATE_TIMES_OBJS:.o=.d)

TEST_ENCODE      := test-encode
TEST_ENCODE_OBJS := $(TEST_ENCODE_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_ENCODE_DEPS := $(TEST_ENCODE_OBJS:.o=.d)

TEST_DECODE      := test-decode
TEST_DECODE_OBJS := $(TEST_DECODE_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_DECODE_DEPS := $(TEST_DECODE_OBJS:.o=.d)

SRC          := main.cpp estimate_times.cpp test_encode.cpp test_decode.cpp euclidian.cpp logprob.cpp $(COMMON_SRC) $(AWGN_SRC)
OBJECTS      := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS):.o=.d)

all: build $(APP_DIR)/$(ERRORS) $(APP_DIR)/$(LOGPROB) $(APP_DIR)/$(EUCLIDIAN) $(APP_DIR)/$(ESTIMATE_TIMES) $(APP_DIR)/$(TEST_ENCODE) $(APP_DIR)/$(TEST_DECODE)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(ERRORS): $(ERRORS_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(ERRORS) $^

$(APP_DIR)/$(LOGPROB): $(LOGPROB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(LOGPROB) $^

$(APP_DIR)/$(EUCLIDIAN): $(EUCLIDIAN_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(EUCLIDIAN) $^

$(APP_DIR)/$(ESTIMATE_TIMES): $(ESTIMATE_TIMES_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(ESTIMATE_TIMES) $^

$(APP_DIR)/$(TEST_ENCODE): $(TEST_ENCODE_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_ENCODE) $^

$(APP_DIR)/$(TEST_DECODE): $(TEST_DECODE_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TEST_DECODE) $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

-include $(ERRORS_DEPS) $(LOGPROB_DEPS) $(EUCLIDIAN_DEPS) $(ESTIMATE_TIMES_DEPS) $(TEST_ENCODE_DEPS) $(TEST_DECODE_DEPS)

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

