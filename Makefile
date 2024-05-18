CXX = g++
CXXFLAGS = -std=c++17 -Wall
INCLUDE_PATH = C:/SDL2/include
LIBRARY_PATH = C:/SDL2/lib

INCLUDES = -I$(INCLUDE_PATH)
LIBS = -L$(LIBRARY_PATH) -lmingw32 -lSDL2main -lSDL2

TARGET = NES_Emulator
SRCS = main.cpp CPU.cpp Memory.cpp PPU.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
