#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>

// Function to generate Fourier series for the selected waveform
void generateFourierSeries(std::vector<sf::Vector2f> &points, int waveformType,
                           int numPoints) {
  const float PI = 3.14159265359;

  points.clear();

  for (int i = 0; i < numPoints; i++) {
    float t = static_cast<float>(i) / numPoints;
    float y = 0.0f;

    // Fourier series implementation based on the selected waveform
    switch (waveformType) {
    case 0: // Sinusoid(FULLY WORKING)
      y += std::sin(8 * PI * t);
      break;

    case 1: // Rectangular(FULLY WORKING)
      y += std::sin(8 * PI * t) > 0.0f ? 1.0f : -1.0f;
      break;

    case 2: // Sawtooth(NOT REPEATING)
      y += 2.0f * (t - std::floor(t + 0.5f));
      break;

    case 3: // Triangular(FULLY WORKING)
      y += 1.0f - 4.0f * std::abs(std::round(t * 5) - t * 5);
      break;
    }

    points.emplace_back(t * 1380,
                        (1 - y) * 200); // Adjust scale and offset as needed
  }
}

int main() {
  // Create SFML window
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Fourier Series Visualizer",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(90);

  // Variables
  std::vector<sf::Vector2f> points; // Points to be plotted
  int selectedWaveform =
      0; // 0: Sinusoid, 1: Rectangular, 2: Sawtooth, 3: Triangular
  int numPoints = 3000; // Increase the number of points for a larger portion of
                        // the waveform

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      // Handle menu selection
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

    // Generate Fourier series for the selected waveform
    generateFourierSeries(points, selectedWaveform, numPoints);

    // Drawing
    window.clear();

    // Draw menu text
    sf::Font font;
    font.loadFromFile("./Arial.TTF"); // Replace with the path to your font file
    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(20);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(10, 10);
    menuText.setString("Press 1-4 to select waveform\n1. Sinusoid\n2. "
                       "Rectangular\n3. Sawtooth\n4. Triangular\nPress 'Q' to "
                       "quit the program");
    window.draw(menuText);

    // Draw your Fourier series points here using SFML
    sf::VertexArray line(sf::LineStrip);
    for (const auto &point : points) {
      line.append(sf::Vertex(point + sf::Vector2f(0, 200),
                             sf::Color::Blue)); // Adjust offset
    }

    window.draw(line);
    window.display();
  }
  return 0;
}
