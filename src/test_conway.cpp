
#include "conway.h"

#include <iostream>

class Renderer
{
public:
  Renderer(const Conway& conway) : conway(conway), buffer(conway.width * conway.height)
  {
    render();
  }

  void render()
  {
    for (size_t i = 0; i < conway.states.size(); ++i)
      buffer[i] = (conway.states[i] == Conway::ALIVE) ? 'O' : '.';
      //buffer[i] = '0' + conway.states[i];

    for (size_t i = 0; i < conway.states.size(); i += conway.width)
      std::cout << std::string(buffer.data() + i, buffer.data() + i + conway.width) << std::endl;
      std::getchar();
  }

  const Conway& conway;
  std::vector<char> buffer;

};


int main()
{
  Conway conway(80, 60);
  Renderer renderer(conway);

  // for (size_t i = 0; i < conway.states.size(); ++i)
  // {
  //   auto[x, y] = conway.coord(i);
  //   if (i != conway.index(x, y))
  //     std::cout << i << std::endl;
  // }

  for (;;)
  {
    conway.evolve();
    renderer.render();
  }
}