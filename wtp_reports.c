/*
 * To run this libev should be installed on the system
 * to install sudo apt-get install libev-dev
 * To compile run
 * gcc wtp_report.c -o wtp -l ev
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/*#include "wpa_ctrl.h"*/
#include <ev.h>

static ev_timer mytimer;
static struct ev_loop *loop;

static int numOfStations=0;

static char ap_ifname[64];

static void timeout_cb(EV_P_ ev_timer *w, int revents) {
        FILE *fp;
        char buf[16], cmd[256];
        int err;

        snprintf(cmd, sizeof(cmd), "iw %s station dump | grep Station -wc", ap_ifname);

        fp = popen(cmd, "r");
        if (!fp) {
                printf("Error executing command %s", strerror(errno));
                //return -1;
        }

        if(fgets(buf, sizeof(buf), fp) == NULL)
                printf("Error in reading power level %s", strerror(errno));
        else {
		numOfStations = atoi(buf);
                printf("Number of clients connected=%d\n", numOfStations);
        }

        if (fp)
                pclose(fp);
	ev_timer_again(loop, w);
        //return 0;
}

/*static struct wpa_ctrl *ctrl_conn;
struct ev_loop *loop = ev_default_init (0);
ev_io wpa_event_io;*/

#define TXPOWERLEVEL "iw wlp3s0 info | grep txpower | cut -d \" \" -f 2 | cut -d \".\" -f 1"
/*#define NUMOFSTATIONS ""*/

/*struct wtpStats {
	int powerlevel;
	int numOfStations;
} wtpreports;*/

/*int wpaControlListenStart(const char *ap_ifname)
{
	char sock_path[256];
	int retry, fd;

	snprintf(sock_path, sizeof(sock_path), "/var/run/hostapd/%s", ap_ifname);
	ctrl_conn = wpa_ctrl_open(sock_path);
	if (!ctrl_conn)
		printf("Error in open control socket to hostapd error is %s", strerror(errno));

	retry=3;
	while(wpa_ctrl_attach(sock_path) && retry--)
		sleep(1);

	if (retry == -1) {
		printf("Failed to attach to control socket %s", sock_path);
		goto close;
	}

	fd = wpa_ctrl_get_fd(ctrl_conn);
	if(fd < 0) {
		printf("Failed to get file descriptor");
		goto detach;
	}

	ev_io_init (&wpa_event_io, wpa_event_cb, fd, EV_READ);
	ev_io_start (loop, &wpa_event);
	ev_run (loop, 0);
detach:
	if (ctrl_conn)
		wpa_ctrl_detach(ctrl_conn);
close:
	if(ctrl_conn)
		wpa_ctrl_close(ctrl_conn);
	return -1;
}*/

/*void wpaControlListenStop(const char *ap_ifname)
{
	char sock_path[256];
	int retry;

	snprintf(sock_path, sizeof(sock_path), "/var/run/hostapd/%s", ap_ifname);
	ctrl_conn = wpa_ctrl_open(sock_path);
	if (!ctrl_conn)
		printf("Error in open control socket to hostapd error is %s", strerror(errno));

	retry=3;
	while(wpa_ctrl_attach(sock_path) && retry--)
		sleep(1);

	if (retry == -1) {
		printf("Failed to attach to control socket %s", sock_path);
		goto close;
	}
close:
	if(ctrl_conn)
		wpa_ctrl_close(ctrl_conn);
}*/

int GetNumOfStationsConnected (const char *ap_ifname) {
	int err;


}

int GetTxPowerLevel (const char *ap_ifname) {
	FILE *fp;
	char buf[16], cmd[256];
	int err;

	snprintf(cmd, sizeof(cmd), "iw %s info | grep txpower | cut -d \" \" -f 2 | cut -d \".\" -f 1", ap_ifname);

	fp = popen(cmd, "r");
	if (!fp) {
		printf("Error executing command %s", strerror(errno));
		return -1;
	}

	if(fgets(buf, sizeof(buf), fp) == NULL)
		printf("Error in reading power level %s", strerror(errno));
	else {
		return atoi(buf);
	}

	if (fp)
		pclose(fp);

	return 0;
}

int main() {
	loop = EV_DEFAULT;
        ev_timer_init (&mytimer, timeout_cb, 0., 5.); /* note, only repeat used */
        ev_timer_again (loop, &mytimer); /* start timer */
        //ev_run (loop, 0);

	//struct *wtpreport;
	strncpy(ap_ifname, "Span_AP", strlen("Span_AP"));
	int power;

	power = GetTxPowerLevel("wlp3s0");
	printf("Curent power_level of AP %ddBm\n", power);

        ev_run (loop, 0);
}	

