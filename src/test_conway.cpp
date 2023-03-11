
#include "conway.h"

#include <iostream>

namespace test {

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
    {
      switch(conway.states[i])
      {
        case Conway::ALIVE:
          buffer[i] = 'O';
          break;
        case Conway::DEAD:
          buffer[i] = '.';
          break;
        default:
          buffer[i] = 'o';
      }
    }
    for (size_t i = 0; i < conway.states.size(); i += conway.width)
      std::cout << std::string(buffer.data() + i, buffer.data() + i + conway.width) << std::endl;
      std::getchar();
  }

  const Conway& conway;
  std::vector<char> buffer;

};

}

int main()
{
  Conway conway(80, 60);
  test::Renderer renderer(conway);

  for (;;)
  {
    conway.evolve();
    renderer.render();
  }
}