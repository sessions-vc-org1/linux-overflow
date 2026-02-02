CXX = g++
CXXFLAGS = -Wall -g -I./include

# -Wl,-rpath,'$$ORIGIN/lib' forces the app to look in ./lib relative to itself
LDFLAGS = -L./lib -lsqlite3 -lz -Wl,-rpath,'$$ORIGIN/lib' 

TARGET = linux_app
SRCS = main.cpp paymentProvider.cpp paymentHandler.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(TARGET)