#include <SFML/Graphics.hpp>

int main(){

  sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Chess Window");

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (event->is<sf::Event::Resized>())
        window.setView(sf::View(sf::FloatRect({0,0},{(float)window.getSize().x,(float)window.getSize().y})));
    }

    window.clear(sf::Color(26,31,46));

    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;
    int boardSize = std::min(windowWidth,windowHeight) * 0.9;
    int boardStartX = (windowWidth - boardSize) / 2;
    int boardStartY = (windowHeight - boardSize) / 2;

    sf::Color darkColour(43,62,44);
    sf::Color lightColour(179,200,170);

/*  int squareSize = boardSize // 8
 *  for range 8 (rows)
 *  for range 8 (columns)
 *  choose colour based off row and col
 *  draw sqare at start + [columns*size,rows*size]
*/

    float squareSize = boardSize/8.f;
    sf::RectangleShape square({squareSize,squareSize});
    square.setPosition({(float)boardStartX, (float)boardStartY});
    for(int row=0;row<8;row++){
      for (int col=0;col<8;col++){
        square.setFillColor((row+col) % 2 ? darkColour : lightColour);
        square.setPosition({(float)boardStartX+(col*squareSize),(float)boardStartY+(row*squareSize)});
        window.draw(square);
      }
    }

    window.display();
  }

  return 0;
}
