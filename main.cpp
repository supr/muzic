#include <iostream>
#include <cstdlib>

#include <unistd.h>
#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024*2
using namespace std;

int main(int argc, char** argv)
{
  pa_sample_spec ss = {
    .format = PA_SAMPLE_S16LE,
    .rate = 44100,
    .channels = 2
  };

  pa_simple *s = nullptr;
  int error;

  s = ::pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error);

  int count = 0;
  for(;;)
    {
      uint8_t buf[BUFSIZE];
      ssize_t r;

      if((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0)
        {
          if (r==0)
            break;

          goto finish;
        }

      //std::cout << "Read: " << r << " Idx: " << count << std::endl;

      for(int i=0; i < r; i++)
        {
          std::cout << (int)buf[i];
        }

      //std::cout << std::endl;

      if(pa_simple_write(s, buf, (size_t)r, &error) < 0)
        {
          goto finish;
        }

      count++;
    }

  std::cout << "Count: " << count << std::endl;

  if(pa_simple_drain(s, &error) < 0)
    {
    goto finish;
    }

finish:
  if(s)
    pa_simple_free(s);

  return 0;
}

