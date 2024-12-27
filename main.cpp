#include <array>
#include <cstdlib>
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
    auto rand01double = []() { return (double)(rand()) / RAND_MAX; };

    body.x = rand01double();
    body.y = rand01double();
    body.z = rand01double();
    body.mass = rand01double();
  }

  // Print to console
  for (Body const &body : bodies) {
    std::cout << body.to_string() << std::endl;
  }
}