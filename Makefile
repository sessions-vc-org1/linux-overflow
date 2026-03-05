CXX = g++
PYTHON = python3
PYTHON_CONFIG = python3-config

PYBIND11_INCLUDES = $(shell $(PYTHON) -m pybind11 --includes 2>/dev/null)
PYTHON_EMBED_LDFLAGS = $(shell $(PYTHON_CONFIG) --ldflags --embed 2>/dev/null)
PYTHON_LDFLAGS = $(if $(PYTHON_EMBED_LDFLAGS),$(PYTHON_EMBED_LDFLAGS),$(shell $(PYTHON_CONFIG) --ldflags 2>/dev/null))
PYTHON_EXT_SUFFIX = $(shell $(PYTHON_CONFIG) --extension-suffix 2>/dev/null)

CXXFLAGS = -Wall -g -I./include $(PYBIND11_INCLUDES)
PICFLAGS = -fPIC

# -Wl,-rpath,'$$ORIGIN/lib' forces the app to look in ./lib relative to itself
LDFLAGS = -L./lib -lsqlite3 -lz $(PYTHON_LDFLAGS) -Wl,-rpath,'$$ORIGIN/lib'
PYMODULE_LDFLAGS = -shared $(PYTHON_LDFLAGS)

TARGET = linux_app
SRCS = main.cpp paymentProvider.cpp paymentHandler.cpp
OBJS = $(SRCS:.cpp=.o)
PYMODULE = paymentlib$(PYTHON_EXT_SUFFIX)
PYMODULE_SRCS = python_bindings.cpp paymentProvider.cpp
PYMODULE_OBJS = $(PYMODULE_SRCS:.cpp=.pic.o)

.PHONY: all run clean check-pybind11

all: check-pybind11 $(TARGET) $(PYMODULE)

check-pybind11:
	@if [ -z "$(PYBIND11_INCLUDES)" ]; then \
		echo "Error: pybind11 was not found for $(PYTHON)."; \
		echo "Install it with: $(PYTHON) -m pip install pybind11"; \
		exit 1; \
	fi

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(PYMODULE): $(PYMODULE_OBJS)
	$(CXX) $(CXXFLAGS) $(PYMODULE_OBJS) -o $(PYMODULE) $(PYMODULE_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.pic.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PICFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(TARGET) $(PYMODULE_OBJS) $(PYMODULE)