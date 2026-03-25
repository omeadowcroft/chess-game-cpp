CXX = g++
CXXFLAGS = -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

chess: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o chess $(LIBS)

clean:
	rm -f chess
