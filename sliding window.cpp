#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

typedef struct { 
  int frame_no;
  int is_acknowledged;
} Frame;

void send_frames(Frame frames[], int start, int window_size) 
{ 
  printf("Sending frames: ");
  for (int i = start; i < start + window_size && i < TOTAL_FRAMES; i++) 
  {
    printf("%d ", frames[i].frame_no);
  }
  printf("\n");
}

void receive_ack(Frame frames[], int start, int window_size) 
{
  for (int i = start; i < start + window_size && i < TOTAL_FRAMES; i++) 
  { 
    if (rand() % 5 != 0) 
    {
      frames[i].is_acknowledged = 1;
      printf("Acknowledgment received for frame %d\n", frames[i].frame_no);
    } 
    else 
    {
      printf("Frame %d lost, needs retransmission\n", frames[i].frame_no);
    }
  }
}

int main() 
{
  Frame frames[TOTAL_FRAMES];
  srand(time(0));
  for (int i = 0; i < TOTAL_FRAMES; i++) 
  {
    frames[i].frame_no = i;
    frames[i].is_acknowledged = 0;
  }
  int base = 0;
  while (base < TOTAL_FRAMES) 
  {
    send_frames(frames, base, WINDOW_SIZE);
    receive_ack(frames, base, WINDOW_SIZE);
    while (base < TOTAL_FRAMES && frames[base].is_acknowledged) 
    {
      base++;
    }
  }
  printf("All frames successfully transmitted!\n");
  return 0;
}

OUTPUT:
Sending frames: 0 1 2 3 
Acknowledgment received for frame 0
Acknowledgment received for frame 1
Frame 2 lost, needs retransmission
Acknowledgment received for frame 3

Sending frames: 2 3 4 5 
Acknowledgment received for frame 2
Frame 3 lost, needs retransmission
Acknowledgment received for frame 4
Frame 5 lost, needs retransmission

Sending frames: 5 6 7 8 
Acknowledgment received for frame 5
Acknowledgment received for frame 6
Frame 7 lost, needs retransmission
Acknowledgment received for frame 8

Sending frames: 7 8 9 
Acknowledgment received for frame 7
Acknowledgment received for frame 8
Acknowledgment received for frame 9
All frames successfully transmitted!
