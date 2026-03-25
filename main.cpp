#include <SFML/Graphics.hpp>

int main(){

  sf::RenderWindow window(sf::VideoMode({800u, 600u}), "Chess Window");

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();
    window.display();
  }

  return 0;
}
