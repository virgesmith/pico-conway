#pragma once

#include <cstdint>
#include <limits>
#include <tuple>
#include <vector>

using std::size_t;

class Conway {
public:
  typedef uint8_t state_t;

  static constexpr state_t ALIVE = std::numeric_limits<state_t>::max();
  static constexpr state_t DEAD = 0;

  static const state_t GLIDER[3][3];

  Conway(size_t w, size_t h);

  std::tuple<int, int> coord(size_t idx) const;

  size_t index(int x, int y) const;

  void reset();

  void clear();

  void age();

  void evolve();

  int alive(size_t idx) const;

  int count(size_t idx) const;

  void add_glider();

  const size_t height;
  const size_t width;
  const size_t size;
  std::vector<state_t> states;
  std::vector<state_t> newstates;
};
