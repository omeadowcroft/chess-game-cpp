CXX = g++
CXXFLAGS = -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

chess: main.cpp board.cpp renderer.cpp
	$(CXX) $(CXXFLAGS) main.cpp board.cpp renderer.cpp -o chess $(LIBS)

clean:
	rm -f chess
