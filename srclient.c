#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#define port 1234

int main()
{
    int csock;
    struct sockaddr_in addr;
    socklen_t addrsize;
    int base=0, next=0, ack, sent[8] = {0};

    csock = socket(AF_INET, SOCK_STREAM, 0);
    if(csock < 0) {
        printf("Error in creating client socket!\n");
        return 0;
    }
    printf("Client socket created successfully!\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(csock, (struct sockaddr*)&addr, sizeof(addr));

    while(base < 10)
    {
        // Send all frames in window
        while(next < base + 4 && next < 10)
        {
            if(sent[next % 8] == 0) {
                printf("Sending frame:%d\n", next);
                send(csock, &next, sizeof(next), 0);
                sent[next % 8] = 1;
            }
            next++;
        }

        fd_set readfds;
        struct timeval tv;
        FD_ZERO(&readfds);
        FD_SET(csock, &readfds);
        tv.tv_sec = 3;
        tv.tv_usec = 0;

        int activity = select(csock + 1, &readfds, NULL, NULL, &tv);

        if(activity > 0)
        {
            recv(csock, &ack, sizeof(ack), 0);

            if(ack >= 0) {
                // Positive ACK
                printf("Received ACK %d\n", ack);
                sent[ack % 8] = 0;

                while(sent[base % 8] == 0 && base < next)
                    base++;
            } else {
                // NAK received
                int lost_frame = -ack;
                printf("Received NAK for frame %d\n", lost_frame);
                printf("Resending frame %d due to NAK\n", lost_frame);
                send(csock, &lost_frame, sizeof(lost_frame), 0);
            }
        }
        else
        {
            printf("Timeout...Resending frames in window\n");
            for(int i = base; i < next; i++)
            {
                if(sent[i % 8] == 1)
                {
                    printf("Resending frame %d\n", i);
                    send(csock, &i, sizeof(i), 0);
                }
            }
        }

        sleep(1);
    }

    int end = -1;
    send(csock, &end, sizeof(end), 0);
    close(csock);
    return 0;
}
