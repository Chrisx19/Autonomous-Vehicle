#include <mainpp.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <roboclaw.h>
#include <std_msgs/Int32.h>

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

ros::NodeHandle nh;
RoboClaw roboclaw = RoboClaw(&huart1, 100);

//std_msgs::Int32 encoder_val;
//ros::Publisher enc_pub("Motor_enc", &encoder_val);

void AV_vel_cb(const geometry_msgs::Twist& AV_vel_msg);

ros::Subscriber<geometry_msgs::Twist> AV_vel_sub("cmd_vel_AV", &AV_vel_cb);	//subscribing a topic from rpi's topic

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  nh.initNode();
  nh.subscribe(AV_vel_sub);
//  nh.advertise(enc_pub);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void loop(void)
{
//  HAL_Delay(1);								//rate of 1hz
  nh.spinOnce();
}

void AV_vel_cb(const geometry_msgs::Twist& AV_vel_msg)	//callback function from subscribe
{
	int drive_duty_cycle = AV_vel_msg.linear.x;//val: -63 <-> 63
	int servo = AV_vel_msg.angular.z;			//val: -50 <-> 50

	htim2.Instance -> CCR1 = 75 + servo;

	if (drive_duty_cycle < 64)
	{
		roboclaw.ForwardBackwardM1(0x80, (drive_duty_cycle + 64 ) - 1);		//Backwards
	}
	else
	{
		roboclaw.ForwardBackwardM1(0x80, drive_duty_cycle + 64);			//Forward
	}
//	encoder_val.data = roboclaw.ReadEncM1(0x80);
//	enc_pub.publish(&encoder_val);

}
