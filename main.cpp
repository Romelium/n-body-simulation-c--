#include <array>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

typedef unsigned int uint;

double newton_law_of_universal_gravitation(
    double gravitational_constant, double mass1, double mass2,
    double distance_between_the_two_mass_centers) {
  return gravitational_constant *
         ((mass1 * mass2) / distance_between_the_two_mass_centers);
}

double distance(double x1, double y1, double z1, double x2, double y2,
                double z2) {
  // We get the difference of the two points. Distance is just the magnitude of
  // the difference a point to a other point
  double x = (x1 - x2);
  double y = (y1 - y2);
  double z = (z1 - z2);

  // Get the magnitude of difference
  return sqrt(x * x + y * y + z * z);
}

struct Body {
  double x, y, z;
  double mass;

  std::string to_string() const {
    return std::format("position: {}, {}, {} | mass: {}", x, y, z, mass);
  }
};

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
  uint index = 0;
  for (Body const &body : bodies) {
    std::cout << index << " | " << body.to_string() << std::endl;
    index++;
  }
}
