# ============================================================================
# TerminArt Makefile
#
#   make            build ./termart
#   make run        render the default example image
#   make clean      remove objects and the binary
#   make help       show this text
#   make check      verify pkg-config can see opencv4
# ============================================================================

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra $(shell pkg-config --cflags opencv4 2>/dev/null)
LDLIBS   ?= $(shell pkg-config --libs opencv4 2>/dev/null)

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
BIN := termart

IMG ?= examples/im.jpg
W   ?= 100

.DEFAULT_GOAL := all

# ---- build ----------------------------------------------------------------
.PHONY: all
all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDLIBS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rebuild everything when a header changes (small project: no .d files needed).
$(OBJ): $(wildcard src/*.hpp)

# ---- targets --------------------------------------------------------------
.PHONY: check
check:
	@if pkg-config --exists opencv4; then \
		echo "opencv4 $$(pkg-config --modversion opencv4) found"; \
	else \
		echo "opencv4 not found via pkg-config - install libopencv-dev" >&2; \
		exit 1; \
	fi

.PHONY: run
run: $(BIN)
	./$(BIN) $(IMG) --width $(W)

.PHONY: clean
clean:
	rm -f $(OBJ) $(BIN)
	rm -rf build

.PHONY: help
help:
	@sed -n '2,11p' $(MAKEFILE_LIST) | sed 's/^# \{0,1\}//'
