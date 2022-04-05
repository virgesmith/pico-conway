#include "conway.h"
#include <limits>

namespace
{
  // workaround: % doesn't work correctly for -ve numbers
  inline int mod(int x, int n)
  {
    return (x % n + n) % n;
  }
}

const Conway::state_t Conway::GLIDER[3][3] = {{Conway::ALIVE, Conway::ALIVE, Conway::DEAD},
                                              {Conway::ALIVE, Conway::DEAD, Conway::ALIVE},
                                              {Conway::ALIVE, Conway::DEAD, Conway::DEAD}};

Conway::Conway(size_t w, size_t h) : height(h), width(w), size(h * w), states(h * w), newstates(h * w)
{
  reset();
}

void Conway::reset()
{
  for (size_t i = 0; i < size; ++i)
    states[i] = (i % 2 == 0 || i % 7 == 0) ? Conway::ALIVE : Conway::DEAD;
}

void Conway::clear()
{
  for (size_t i = 0; i < size; ++i)
    states[i] = Conway::DEAD;
}

std::tuple<int, int> Conway::coord(size_t idx) const
{
  return {idx % width, idx / width};
}

size_t Conway::index(int x, int y) const
{
  return mod(x, width) + mod(y, height) * width;
}

void Conway::age()
{
  for (size_t i = 0; i < size; ++i)
  {
    newstates[i] = (states[i] != Conway::DEAD) ? states[i] - 1 : Conway::DEAD;
  }
}

void Conway::evolve()
{
  age();
  for (size_t i = 0; i < size; ++i)
  {
    int c = count(i);
    if (c < 2 || c > 3)
      newstates[i] = Conway::DEAD;
    else if (c == 3 && newstates[i] == 0)
      newstates[i] = Conway::ALIVE;
  }
  states.swap(newstates);
  // occasionally add a random glider to keep it going
  if (rand() % 64 == 0)
    add_glider();
}

int Conway::alive(size_t idx) const
{
  return states[idx] != Conway::DEAD;
}

int Conway::count(size_t idx) const
{
  auto [x, y] = coord(idx);

  return alive(index(x - 1, y - 1)) + alive(index(x, y - 1)) + alive(index(x + 1, y - 1)) + alive(index(x - 1, y)) + alive(index(x + 1, y)) + alive(index(x - 1, y + 1)) + alive(index(x, y + 1)) + alive(index(x + 1, y + 1));
}

void Conway::add_glider()
{
  size_t pos = rand() % size;
  size_t orient_x = rand() % 2 ? 1 : -1;
  size_t orient_y = rand() % 2 ? 1 : -1;

  for (size_t y = 0; y < 3; ++y)
    for (size_t x = 0; x < 3; ++x)
      states[mod(pos + y * orient_y * width + x * orient_x, size)] = GLIDER[y][x];
}