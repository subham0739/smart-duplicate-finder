CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = duplicate_finder

SOURCE = src/main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET) test_files
