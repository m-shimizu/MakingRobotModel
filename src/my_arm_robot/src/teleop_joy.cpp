#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class TeleopJoy
{
public:
  TeleopJoy();
  ~TeleopJoy() {} ;
private:
  void JoyCB(const sensor_msgs::Joy::ConstPtr& joy);
//  ros::NodeHandle _nh;
  int             _linear, _angular;
  double          _scale_l, _scale_a, _scale_arm, _scale_hand;
  std::string     _tpc_cmd_vel, _tpc_cmd_arm, _tpc_cmd_hand, _tpc_joy;
  ros::Publisher  vel_pub, arm_pub, hand_pub;
  ros::Subscriber joy_sub;
};


TeleopJoy::TeleopJoy():
  _linear(1), _angular(2), 
  _scale_l(0.7), _scale_a(1.2), _scale_arm(1), _scale_hand(1)
{
  ros::NodeHandle _nh;
  _nh.param("axis_linear", _linear, _linear);
  _nh.param("axis_angular", _angular, _angular);
  _nh.param("scale_angular", _scale_a, _scale_a);
  _nh.param("scale_linear", _scale_l, _scale_l);
  _nh.param("scale_arm", _scale_arm, _scale_arm);
  _nh.param("scale_hand", _scale_hand, _scale_hand);
  _nh.param("cmd_vel", _tpc_cmd_vel, std::string("/cmd_vel"));
  _nh.param("cmd_arm", _tpc_cmd_arm, std::string("/cmd_arm"));
  _nh.param("cmd_hand", _tpc_cmd_hand, std::string("/cmd_hand"));
  _nh.param("joy", _tpc_joy, std::string("/joy"));
  vel_pub = _nh.advertise<geometry_msgs::Twist>(_tpc_cmd_vel.c_str(), 1);
  arm_pub   = _nh.advertise<geometry_msgs::Twist>(_tpc_cmd_arm.c_str(), 1);
  hand_pub  = _nh.advertise<geometry_msgs::Twist>(_tpc_cmd_hand.c_str(), 1);
  joy_sub = _nh.subscribe<sensor_msgs::Joy>(_tpc_joy.c_str(), 10
                                         , &TeleopJoy::JoyCB, this);
}

void TeleopJoy::JoyCB(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist, arm_twist, hand_twist;
  twist.angular.z = _scale_a*joy->axes[_angular];
  twist.linear.x = _scale_l*joy->axes[_linear];
  vel_pub.publish(twist);
  if(!joy->buttons[7])
  {
    arm_twist.linear.x = _scale_arm * joy->axes[0];
    arm_twist.linear.y = _scale_arm * joy->axes[1];
    arm_twist.linear.z = _scale_arm * joy->axes[2];
    arm_twist.angular.x = _scale_arm * joy->axes[3];
    arm_twist.angular.y = _scale_arm * joy->axes[4];
    arm_twist.angular.z = _scale_arm * joy->axes[5];
    arm_pub.publish(arm_twist);
  }
  else
  {
    hand_twist.linear.x = _scale_hand * joy->axes[0];
    hand_twist.linear.y = _scale_hand * joy->axes[1];
    hand_twist.linear.z = _scale_hand * joy->axes[2];
    hand_twist.angular.x = _scale_hand * joy->axes[3];
    hand_twist.angular.y = _scale_hand * joy->axes[4];
    hand_twist.angular.z = _scale_hand * joy->axes[5];
    hand_pub.publish(hand_twist);
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_joy");
  TeleopJoy teleop_joy;
  ros::spin();
}
