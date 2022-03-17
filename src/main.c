// CANALYZE utility
// output trace statistics
// usage will be explained here
// canalyze <file>
// trace corr xcorr entropy mode min max
// arbid count freq priority z num_bits d u_clz o_clz u_intval 
// IDS model acc prec recall f
// split <file> <dir>
// splice <dir> <file>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<net/if.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>

#include<linux/can.h>
#include<linux/can/raw.h>

#define N 4096
#define ARBID 2048

int main(int argc, char** argv) {

	// create socket
	int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(s == -1) { return -1; }

	// request to manipulate device
	struct ifreq ifr;
	strcpy(ifr.ifr_name, "can0");
	ioctl(s, SIOCGIFINDEX, &ifr);

	// config socket address
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	// bind to socket
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) { return -2; }

	// data to extract
	long count[ARBID] = {0};
	long freq[ARBID] = {0};
	long diff[N] = {0};
	long hamming[N] = {0};
	canid_t prev;
	canid_t min = ARBID;
	canid_t max = 0;

	// read N messages
	for(int i = 0; i < N; i++) {
		struct can_frame frame;
		canid_t mask = 0x7ff;
		size_t nbytes = read(s, &frame, sizeof(struct can_frame));

		if(nbytes > 0) {
			canid_t curr = frame.can_id & mask;
			count[curr] += 1; // count of each ID
			if(i > 0) { diff[i] = curr - prev; } // pairwise distance
			if(curr < min) { min = curr; }
			if(curr > max) { max = curr; }
			printf("%0x\n", curr);
			prev = curr;
		}
	}

	// compute summary statistics
	for(int j = 0; j < N; j++) {
		freq[j] = count[j] / N;	
	}
}
