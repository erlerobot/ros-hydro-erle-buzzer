#!/usr/bin/python
import rospy
import sys
from ros_erle_buzzer.msg import *

tune = 0

def talker():
    pub = rospy.Publisher("buzzer", buzzer, queue_size=10)
    rospy.init_node("buzzer", anonymous=True)
    msg = buzzer()
    msg.tune = tune
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        pub.publish(msg)
        rate.sleep()

def usage():
    return "%s [tune]"%sys.argv[0]

if __name__ == "__main__":

    if len(sys.argv) == 2:
        tune = int(sys.argv[1])
    else:
        print usage()
        sys.exit(1)
    talker();