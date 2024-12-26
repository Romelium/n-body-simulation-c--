#include <array>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

struct Body {
  double x, y, z;
  double mass;

  std::string to_string() const {
    return std::format("position: {}, {}, {} | mass: {}", x, y, z, mass);
  }
};

typedef unsigned int uint;

int main() {
  const uint number_of_bodies = 2;
  std::array<Body, number_of_bodies> bodies{};

  // Init bodies
  for (Body &body : bodies) {
    body.x = 0;
    body.y = 0;
    body.z = 0;
    body.mass = 1;
  }

  // Print to console
  for (Body const &body : bodies) {
    std::cout << body.to_string() << std::endl;
  }
}