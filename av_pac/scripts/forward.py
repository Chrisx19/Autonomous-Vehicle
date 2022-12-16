#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class Rpi(object):
    def __init__(self):
        rospy.loginfo("Starting Raspberry Pi node...")

        self.cmd_vel_pub = rospy.Publisher("/cmd_vel_AV", Twist, queue_size = 1)
        self.joy_sub = rospy.Subscriber("/joy", Joy, self.joy_cb)

    def joy_cb(self, joy_msg):
        vel = Twist()

        joy_val_drive = joy_msg.axes[1]
        joy_val_turn = joy_msg.axes[3]
        
        if (joy.buttons[0]):
            vel.linear.x = 63
            vel.angular.z = 0
        if (joy.buttons[1]):
            vel.angular.z = 0
        
#         servo = 0
        self.cmd_vel_pub.publish(vel)

if __name__ == "__main__":
    rospy.init_node("Rpi_node", anonymous = False)
    rpi_node = Rpi()
    rospy.spin()
