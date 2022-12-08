#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int8

rospy.init_node("debug_rosserial")
pub_num = rospy.Publisher("/number", Int8, queue_size=10)


num = 15

while not rospy.is_shutdown():
	pub_num.publish(num)
	rospy.sleep(0.1)
 