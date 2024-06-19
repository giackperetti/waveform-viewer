#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>

void generateFourierSeries(std::vector<sf::Vector2f> &points, int waveformType,
                           int numPoints) {

  points.clear();

  for (int i = 0; i < numPoints; i++) {
    float t = static_cast<float>(i) / numPoints;
    float y = 0.0f;

    // Fourier series implementation based on the selected waveform
    switch (waveformType) {
    case 0: // Sinusoid(FULLY WORKING)
      y += std::sin(8 * M_PI * t);
      break;

    case 1: // Rectangular(FULLY WORKING)
      y += std::sin(8 * M_PI * t) > 0.0f ? 1.0f : -1.0f;
      break;

    case 2: // Sawtooth(FULLY WORKING)
      y += 2.0f * (5.0f * t - std::floor(5.0f * t + 0.5f));
      break;

    case 3: // Triangular(FULLY WORKING)
      y += 1.0f - 4.0f * std::abs(std::round(t * 5) - t * 5);
      break;
    }

    points.emplace_back(t * 1380, (1 - y) * 200);
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Fourier Series Visualizer",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  std::vector<sf::Vector2f> points;
  // 0: Sinusoid, 1: Rectangular, 2: Sawtooth, 3: Triangular
  int selectedWaveform = 0;
  int numPoints = 18000;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Num1:
          selectedWaveform = 0;
          break;
        case sf::Keyboard::Num2:
          selectedWaveform = 1;
          break;
        case sf::Keyboard::Num3:
          selectedWaveform = 2;
          break;
        case sf::Keyboard::Num4:
          selectedWaveform = 3;
          break;
        case sf::Keyboard::Q:
          window.close();
          break;
        default:
          break;
        }
      }
    }

    generateFourierSeries(points, selectedWaveform, numPoints);

    window.clear(sf::Color{40, 40, 40});

    sf::Font font;
    font.loadFromFile("./Arial.TTF");
    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(20);
    menuText.setFillColor(sf::Color{235, 219, 178});
    menuText.setPosition(10, 10);
    menuText.setString("Press 1-4 to select waveform\n"
                       "1. Sinusoid\n"
                       "2. Rectangular\n"
                       "3. Sawtooth\n"
                       "4. Triangular\n"
                       "Press 'Q' to quit the program");
    window.draw(menuText);

    // Draw your Fourier series points here using SFML
    sf::VertexArray line(sf::LineStrip);
    for (const auto &point : points) {
      line.append(
          sf::Vertex(point + sf::Vector2f(0, 200), sf::Color{69, 133, 136}));
    }

    window.draw(line);
    window.display();
  }
  return 0;
}
