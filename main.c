#include <stdio.h>
#include <time.h>

time_t t;
typedef struct event_t event_t;

struct event_t {
  int type;
  union {
    time_t time;
  };
};

event_t event_loop(void)
{
  static time_t prev_time = 0;
  time_t now = time(NULL);

  if (now != prev_time)
  {
    prev_time = now;

    return (event_t){
      .type = 6,
      .time = now,
    };
  }

  return (event_t){
    .type = 0,
  };
}

void local_time(void)
{
  printf("\x1B[%d;%dH\x1B[?25h", 1, 1);

  struct tm *tm = localtime(&t);
  char buffer[100];

  strftime(buffer, 100, " %d %b %Y, %H:%M:%S ", tm);
  printf("%s", buffer);
  fflush(stdout);
}

int main()
{
  int time_loop = 1;
  int stop = 0;

  while (!stop)
  {
    event_t event;

    if ((event = event_loop()).type)
    {
      if (event.type == 6) {
        t = event.time;

        time_loop = 1;
      }
    }

    if (time_loop) {
      local_time();
      time_loop = 0;
    }
  }

  return 0;
}
