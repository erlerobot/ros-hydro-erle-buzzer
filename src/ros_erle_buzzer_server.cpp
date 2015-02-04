#include "ros/ros.h"
#include "ros_erle_buzzer/buzzer.h"

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>

#include "ToneAlarmDriver.h"

ToneAlarm buz;
int state = -1;
int tune = 0;
pthread_t tid;

void* doSomeThing(void *arg)
{
	struct timeval a, b;
    long totalb, totala;
    long diff;

    int cycle_control = 20;

   while(1){

        gettimeofday(&a, NULL);
        totala = a.tv_sec * 1000000 + a.tv_usec;

        if(state == 0){
            state = state + buz.init_tune();
        }else if(state == 1){
            state = state + buz.set_note();
        }
        if(state == 2){
            state = state + buz.play();
        }else if(state == 3){
            state = 1;
        }
        if(buz.is_tune_comp()){
            state = -1;
        }

        gettimeofday(&b, NULL);
        totalb = b.tv_sec * 1000000 + b.tv_usec;
        diff = (totalb - totala) / 1000;

        if (diff < 0 || diff > cycle_control)
            diff = cycle_control;
        else
            diff = cycle_control - diff;

        usleep(diff * 1000);
    }
}

void buzzerCallback(const ros_erle_buzzer::buzzer::ConstPtr& msg)
{
  ROS_INFO("I heard: Tune:[%d]", msg->tune);

  if(state==-1){
  	buz.set_tune(msg->tune);
  	state = 0;
  }


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "buzzer");

  ros::NodeHandle n;

  buz.init();

  ros::Subscriber sub = n.subscribe("buzzer", 1000, buzzerCallback);

  int err;
  err = pthread_create(&(tid), NULL, &doSomeThing, NULL);
  if (err != 0){
    printf("\ncan't create thread ");
    return -1;
  }
  ros::spin();

  return 0;
}

