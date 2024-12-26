#include <array>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

struct Body {
  double x, y, z;
  double mass;

  std::string to_string() {
    return std::format("position: {}, {}, {} | mass: {}", x, y, z, mass);
  }
};

typedef unsigned int uint;

int main() {
  const uint number_of_bodies = 2;
  const std::array<Body, number_of_bodies> bodies{};

  // Print to console
  for (Body const &body : bodies) {
    std::cout << body.to_string() << std::endl;
  }
}