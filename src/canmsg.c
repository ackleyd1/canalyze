#include<stdlib.h>
#include<stdio.h>
#include<arm_neon.h>
#include<linux/can.h>

// arb_id and dlc layout
// 0b0aaaaaaaaaaa0ddd
// s.t arb_id = header >> 4 
// and dlc = header & 0x7
// how to clear up ununsed space on stack?
typedef struct can_msg {
    uint16_t hdr;
    uint8_t data[8];
} can_msg;

static inline uint16_t arbid(const struct can_msg* m) { return m->hdr >> 4; }
static inline uint16_t dlc(const struct can_msg* m) { return m->hdr & 0x7; }

int main(int argc, char* argv[]) {
    can_msg m = { 0x7ff4, { 0xab, 0xff, 0xfe, 0xee }};
    printf("arb id: %0x\ndlc: %d\n", arbid(&m), dlc(&m));
}
