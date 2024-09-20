EXEC     := bin/xef
SRC      := $(shell find src/ -type f -name '*.cpp')
OBJ      := $(addsuffix .o,$(basename $(SRC)))

CFLAGS   = -Ofast -Wall -Wextra -Wpedantic -Werror
# -MMD does "free" dependency file generation.
override CFLAGS += -std=c++23 -MMD

bin:
	mkdir bin

$(EXEC): $(OBJ) bin
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: run
run: $(EXEC)
	./$^

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC) bin

.PHONY: distclean
distclean: clean
	rm -f $(shell find -type f -name "*.d")

-include $(OBJ:%.o=%.d)