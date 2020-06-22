
// sleep
#include <unistd.h>
// printf
#include <cstdio>
// uintxx_t
#include <cstdint>
#include <SocketCAN.h>
#include <iostream>
#include <csignal>

bool stop = false;

void rx_handler(can_frame_t* frame)
{
    // TODO: Do something here with the received frame
    std::cout << frame->can_id << std::endl;
}

void sigHandle(int sig) {
    stop = true;
}

void test_socketcan()
{
    printf("\nTesting SocketCAN adapter\n");
    printf("#############################\n");

    auto* adapter = new SocketCAN();
    adapter->open((char*)"can0");

    adapter->reception_handler = &rx_handler;

    sleep(3);

    can_frame_t frame;
    frame.can_id = 0x150;
    frame.can_dlc = 2;
    frame.data[0] = 0x50;
    frame.data[1] = 0x01;

    adapter->transmit(&frame);

    while (!stop);

    delete adapter;
    sleep(1);
}


int main()
{
    signal(SIGINT, &sigHandle);
    test_socketcan();

    return 0;
}
