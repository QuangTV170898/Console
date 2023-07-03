PROJECT_DIR=$(PWD)
OBJ_DIR=$(PROJECT_DIR)/__build
TARGET=console

# cross compiler
CROSS_COMPILE=
CPP	=$(CROSS_COMPILE)g++
CC	=$(CROSS_COMPILE)gcc

CSRCS += $(wildcard ./*.c)
OBJS  += $(patsubst %.c, $(OBJ_DIR)/%.o, $(CSRCS))

$(OBJ_DIR)/%.o: %.c
	@echo "build object $<"
	@mkdir -p $(shell dirname $@)  
	@$(CC) -c $< -o $@ $(CFLAGS)   

$(OBJ_DIR)/$(TARGET): $(OBJS)
	@echo "---------- build target ----------"
	@$(CC) -o $(OBJ_DIR)/$(TARGET) $^ 

.PHONY : all
all: create $(OBJ_DIR)/$(TARGET) 

.PHONY : clean
clean:
	@echo "clean object project"
	@rm -rf $(OBJ_DIR)

.PHONY : create
create:
	@mkdir -p $(OBJ_DIR)