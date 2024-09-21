EXEC     := bin/xef
SRC      := $(shell find src/ -type f -name '*.cpp')
OBJ      := $(addsuffix .o,$(basename $(SRC)))

CFLAGS   = -Ofast -Wall -Wextra -Wpedantic -Werror -g
# -MMD does "free" dependency file generation.
override CFLAGS += -std=c++23 -MMD


# obj/%.o: src/%.cpp src/%.hpp obj
# 	$(CXX) $(CFLAGS) $(CXXFLAGS) src/$*.cpp src/$*.hpp -o $@

$(EXEC): $(OBJ) bin # $(patsubst src/%,obj/%,$(OBJ)) bin
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $@
	
# $(patsubst src/%,obj/%,$(OBJ)) -o $@

bin:
	mkdir bin

# obj:
# 	mkdir obj

.PHONY: run
run: $(EXEC)
	./$^

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)
	rmdir bin
	# rmdir obj

.PHONY: distclean
distclean: clean
	rm -f $(shell find -type f -name "*.d")

-include $(OBJ:%.o=%.d)