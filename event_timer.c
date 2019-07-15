#include <stdio.h>
#include <stdlib.h>
#include <ev.h>

static ev_timer mytimer;
static struct ev_loop *loop;

static void
timeout_cb (EV_P_ ev_timer *w, int revents)
{
	printf("Inside timer\n");
	ev_timer_again(loop, w);
}


int main() {

	 loop = EV_DEFAULT;
	//ev_timer mytimer;
	ev_timer_init (&mytimer, timeout_cb, 0., 10.); /* note, only repeat used */
	//ev_timer_start (loop, &mytimer);
	ev_timer_again (loop, &mytimer); /* start timer */
	ev_run (loop, 0);
// and in some piece of code that gets executed on any "activity":
// reset the timeout to start ticking again at 10 seconds
//ev_timer_again (&mytimer);

return 0;
}
