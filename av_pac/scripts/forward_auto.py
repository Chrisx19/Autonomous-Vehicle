#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class Rpi(object):
    def __init__(self):
        rospy.loginfo("Starting Raspberry Pi node...")

        self.cmd_vel_pub = rospy.Publisher("/cmd_vel_AV", Twist, queue_size = 1)
#         self.joy_sub = rospy.Subscriber("/joy", Joy, self.joy_cb)

    def forward(self):
        vel = Twist()

        vel.linear.x = 63
        vel.angular.z = 0
        
        self.cmd_vel_pub.publish(vel)

if __name__ == "__main__":
    rospy.init_node("Rpi_node", anonymous = False)
    rpi_node = Rpi()
    rospy.spin()
