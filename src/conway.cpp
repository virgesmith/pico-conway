#include "conway.h"

#include "pico/rand.h"

#include <limits>

#include <cstdlib>

namespace {
// workaround: % doesn't work correctly for -ve numbers
inline int mod(int x, int n) { return (x % n + n) % n; }
} // namespace

union SplitU32 {
  SplitU32(uint32_t n): n(n) { }
  struct _bits {
    bool bit0: 1;
    bool bit1: 1;
    uint16_t bit2_15: 14;
    uint16_t bit16_31;
  } bits;
  uint32_t n;
};


const Conway::state_t Conway::GLIDER[3][3] = {{Conway::ALIVE, Conway::ALIVE, Conway::DEAD},
                                              {Conway::ALIVE, Conway::DEAD, Conway::ALIVE},
                                              {Conway::ALIVE, Conway::DEAD, Conway::DEAD}};

Conway::Conway(size_t w, size_t h) : height(h), width(w), size(h * w), states(h * w), newstates(h * w) { reset(); }

void Conway::reset() {
  for (size_t i = 0; i < size; ++i)
    states[i] = (i % 2 == 0 || i % 7 == 0) ? Conway::ALIVE : Conway::DEAD;
}

void Conway::clear() { std::fill(states.begin(), states.end(), Conway::DEAD); }

std::tuple<int, int> Conway::coord(size_t idx) const { return {idx % width, idx / width}; }

size_t Conway::index(int x, int y) const { return mod(x, width) + mod(y, height) * width; }

void Conway::age() {
  for (size_t i = 0; i < size; ++i) {
    newstates[i] = (states[i] != Conway::DEAD) ? states[i] - 1 : Conway::DEAD;
  }
}

void Conway::evolve() {
  age();
  for (size_t i = 0; i < size; ++i) {
    int c = count(i);
    if (c < 2 || c > 3)
      newstates[i] = Conway::DEAD;
    else if (c == 3 && newstates[i] == 0)
      newstates[i] = Conway::ALIVE;
  }
  states.swap(newstates);
  // occasionally add a random glider to keep it going
  if (get_rand_32() % 64 == 0)
    add_glider();
}

int Conway::alive(size_t idx) const { return states[idx] != Conway::DEAD; }

int Conway::count(size_t idx) const {
  auto [x, y] = coord(idx);

  return alive(index(x - 1, y - 1)) + alive(index(x, y - 1)) + alive(index(x + 1, y - 1)) + alive(index(x - 1, y)) +
         alive(index(x + 1, y)) + alive(index(x - 1, y + 1)) + alive(index(x, y + 1)) + alive(index(x + 1, y + 1));
}

void Conway::add_glider() {
  SplitU32 n(get_rand_32());
  size_t pos = n.bits.bit2_15 % size;
  size_t orient_x = n.bits.bit0 ? 1 : -1;
  size_t orient_y = n.bits.bit0 ? 1 : -1;

  for (size_t y = 0; y < 3; ++y)
    for (size_t x = 0; x < 3; ++x)
      states[mod(pos + y * orient_y * width + x * orient_x, size)] = GLIDER[y][x];
}