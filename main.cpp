#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

typedef unsigned int uint;

// https://stackoverflow.com/a/52895729/17921095
void clear_console() {
#if defined _WIN32
  system("cls");
  // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
  // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
  system("clear");
#endif
}

double newton_law_of_universal_gravitation(
    double gravitational_constant, double mass1, double mass2,
    double distance_between_the_two_mass_centers) {
  return gravitational_constant *
         ((mass1 * mass2) / distance_between_the_two_mass_centers);
}

double magnitude(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}

double distance(double x1, double y1, double z1, double x2, double y2,
                double z2) {
  // We get the difference of the two points. Distance is just the magnitude of
  // the difference a point to a other point
  double x = (x1 - x2);
  double y = (y1 - y2);
  double z = (z1 - z2);

  // Get the magnitude of difference
  return magnitude(x, y, z);
}

struct Body {
  double x, y, z;    // position of the mass centers will be the body
  double vx, vy, vz; // velocity
  double mass;

  std::string to_string() const {
    return std::format("position: {}, {}, {} | velocity: {}, {}, {} | mass: {}",
                       x, y, z, vx, vy, vz, mass);
  }
};

// Create a string of a map of the bodies relative to each other.
// Need more than two bodies to be useful
// Comment out z cause only x and y is accounted for now.
template <size_t size>
std::string create_map_of_bodies(const uint height, const uint width,
                                 const std::array<Body, size> &bodies) {
  // Get the bounds of the area that the bodies are in.
  double highest_x, highest_y /* , highest_z */;
  double lowest_x, lowest_y /* , lowest_z */;
  highest_x = highest_y = /* highest_z =  */ std::numeric_limits<double>::min();
  lowest_x = lowest_y = /* lowest_z =  */ std::numeric_limits<double>::max();
  for (Body const &body : bodies) {
    if (body.x > highest_x)
      highest_x = body.x;
    if (body.y > highest_y)
      highest_y = body.y;
    // if (body.z > highest_z)
    //   highest_z = body.z;
    if (body.x < lowest_x)
      lowest_x = body.x;
    if (body.y < lowest_y)
      lowest_y = body.y;
    // if (body.z < lowest_z)
    //   lowest_z = body.z;
  }

  std::vector<std::string> lines{height, std::string(width, ' ')};
  for (Body const &body : bodies) {
    // get map index positon of body by inverse lerp using bounds
    const uint x =
        round((body.x - lowest_x) / (highest_x - lowest_x) * (width - 1));
    const uint y =
        round((body.y - lowest_y) / (highest_y - lowest_y) * (height - 1));
    // const uint z = (body.z - lowest_z) / (highest_z - lowest_z);

    lines[y][x] = '*';
  }

  std::string output = "";
  // append all lines to output
  for (std::string const &line : lines) {
    output += line + '\n';
  }

  return output;
}

int main() {
  const uint number_of_bodies = 2;
  const double gravitational_constant = 1;
  const uint updates_per_second = 10;
  std::array<Body, number_of_bodies> bodies{};

  // Init bodies
  for (Body &body : bodies) {
    const auto rand01double = []() { return (double)(rand()) / RAND_MAX; };

    body.x = rand01double();
    body.y = rand01double();
    body.z = rand01double();
    body.vx = rand01double();
    body.vy = rand01double();
    body.vz = rand01double();
    body.mass = rand01double();
  }

  // Update loop
  std::chrono::time_point last_time = std::chrono::high_resolution_clock::now();
  while (true) {
    std::chrono::time_point now_time =
        std::chrono::high_resolution_clock::now();
    // Calculate time difference from the last update and now in seconds
    std::chrono::duration<double> time_delta = now_time - last_time;

    // Set how many of seconds is needed to pass to update. As 'seconds', it means a fraction of a section.
    const double seconds_to_update = 1/(double)updates_per_second;
    // Skip loop iteration if the seconds from the last update is below the seconds needed to pass
    if (time_delta.count() < seconds_to_update)
      continue;
    last_time = now_time; // Set this as the last update

    // Print to console. Do this first to confirm the initial state before
    // calculations
    clear_console();
    uint index = 0;
    for (Body const &body : bodies) {
      std::cout << index << " | " << body.to_string() << std::endl;
      index++;
    }
    std::cout << create_map_of_bodies(32, 32, bodies);

    // Update the position of the bodies by their velocity.
    for (Body &body : bodies) {
      body.x += body.vx;
      body.y += body.vy;
      body.z += body.vz;
    }

    // Update the velocity of the bodies by acceleration using newton's law of
    // universal gravitation.
    {
      // copy bodies to use their unmodified positions to not have acceleration
      // calculations depend on the order of bodies in the array
      const std::array<Body, number_of_bodies> bodies_old = bodies;

      // Avoid bodies that already have calculations for each other by looping
      // all combinations. Each calculation will update both bodies at the same
      // time to not repeat the same calculations twice.
      for (uint i1 = 0, n = bodies.size(); i1 < n - 1; i1++) {
        for (uint i2 = i1 + 1; i2 < n; i2++) {

          // the mass centers will be the bodies' x, y, z members
          const double distance_between_the_two_mass_centers =
              distance(bodies_old[i1].x, bodies_old[i1].y, bodies_old[i1].z,
                       bodies_old[i2].x, bodies_old[i2].y, bodies_old[i2].z);

          const double force = newton_law_of_universal_gravitation(
              gravitational_constant, bodies_old[i1].mass, bodies_old[i2].mass,
              distance_between_the_two_mass_centers);

          // Get the direction of the force for the first body
          const double x1 = (bodies_old[i2].x - bodies_old[i1].x);
          const double y1 = (bodies_old[i2].y - bodies_old[i1].y);
          const double z1 = (bodies_old[i2].z - bodies_old[i1].z);

          // Normalize the first force direction. The magnitude will be the
          // force calculated by newton's law of universal gravitation
          const double magnitude1 = magnitude(x1, y1, z1);
          const double x1_normalized = x1 / magnitude1;
          const double y1_normalized = y1 / magnitude1;
          const double z1_normalized = z1 / magnitude1;

          // Multiply by force to set the magnitude of the first force
          // direction. Account for mass for final expression
          const double x1_force = x1_normalized * force;
          const double y1_force = y1_normalized * force;
          const double z1_force = z1_normalized * force;

          // The second force direction for the second body is just the opposite
          // of the first
          const double x2_force = -x1_force;
          const double y2_force = -y1_force;
          const double z2_force = -z1_force;

          // Calculate and apply the acceleration to the velocity of the first
          // body
          bodies[i1].vx += x1_force / bodies[i1].mass;
          bodies[i1].vy += y1_force / bodies[i1].mass;
          bodies[i1].vz += z1_force / bodies[i1].mass;

          // Do do the same for the second body
          bodies[i2].vx += x2_force / bodies[i2].mass;
          bodies[i2].vy += y2_force / bodies[i2].mass;
          bodies[i2].vz += z2_force / bodies[i2].mass;
        }
      }
    }

    // Center all bodies around point (0, 0, 0). Prevents overflow or
    // imprecision if bodies travel too far from point (0, 0, 0).
    // Doesn't help if bodies are far from each other.
    {
      // Sum all the position of the bodies
      double xsum = 0;
      double ysum = 0;
      double zsum = 0;
      for (Body const &body : bodies) {
        xsum += body.x;
        ysum += body.y;
        zsum += body.z;
      }

      // Average the sum all the position of the bodies which also the center
      // point of all bodies
      const double cx = xsum / number_of_bodies;
      const double cy = ysum / number_of_bodies;
      const double cz = zsum / number_of_bodies;

      // Offset all bodies by the center point to make point (0, 0, 0) be the
      // center of all bodies
      for (Body &body : bodies) {
        body.x -= cx;
        body.y -= cy;
        body.z -= cz;
      }
    }
  }
}
