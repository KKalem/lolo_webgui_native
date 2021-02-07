#ifndef ROSWASM_SAM_H
#define ROSWASM_SAM_H

#include <roswasm_webgui/roswasm_widget.h>

#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/BatteryState.h>
#include <nav_msgs/Odometry.h>

#include <lolo_msgs/PercentStamped.h>
//#include <lolo_msgs/ThrusterRPMs.h>
#include <lolo_msgs/ThrusterAngles.h>
#include <lolo_msgs/BallastAngles.h>
//#include <lolo_msgs/Leak.h>
#include <smarc_msgs/Leak.h>
#include <smarc_msgs/ThrusterRPM.h>

namespace roswasm_webgui {

bool draw_ballast_angles(lolo_msgs::BallastAngles& msg, roswasm::Publisher& pub);
bool draw_percent(lolo_msgs::PercentStamped& msg, roswasm::Publisher& pub);
//bool draw_thruster_rpms(lolo_msgs::ThrusterRPMs& msg, roswasm::Publisher& pub);
bool draw_thruster_rpm(smarc_msgs::ThrusterRPM& msg, roswasm::Publisher& pub);
bool draw_thruster_angles(lolo_msgs::ThrusterAngles& msg, roswasm::Publisher& pub);

class SamActuatorWidget {
private:
    TopicWidget<lolo_msgs::ThrusterAngles>* thruster_angles;
    TopicWidget<smarc_msgs::ThrusterRPM>* thruster1_rpm;
    TopicWidget<smarc_msgs::ThrusterRPM>* thruster2_rpm;
    roswasm::Publisher rpm1_pub;
    roswasm::Publisher rpm2_pub;
    roswasm::Timer pub_timer;
    bool rpm_pub_enabled;
    TopicWidget<lolo_msgs::PercentStamped>* lcg_actuator;
    TopicWidget<std_msgs::Bool>* lcg_control_enable;
    TopicWidget<std_msgs::Float64>* lcg_control_setpoint;
    TopicWidget<lolo_msgs::PercentStamped>* vbs_actuator;
    TopicWidget<std_msgs::Bool>* vbs_control_enable;
    TopicWidget<std_msgs::Float64>* vbs_control_setpoint;
    TopicWidget<lolo_msgs::BallastAngles>* tcg_actuator;
    TopicWidget<std_msgs::Bool>* tcg_control_enable;
    TopicWidget<std_msgs::Float64>* tcg_control_setpoint;

public:
    void pub_callback(const ros::TimerEvent& e);
    void show_window(bool& show_actuator_window);
    SamActuatorWidget(roswasm::NodeHandle& nh);
};

class SamDashboardWidget {
private:
    bool was_leak;
    TopicBuffer<smarc_msgs::Leak>* leak;
    TopicBuffer<sensor_msgs::NavSatFix>* gps;
    TopicBuffer<sensor_msgs::BatteryState>* battery;
    TopicBuffer<nav_msgs::Odometry>* odom;
    TopicBuffer<lolo_msgs::PercentStamped>* vbs;
    TopicBuffer<lolo_msgs::PercentStamped>* lcg;
    //TopicBuffer<lolo_msgs::ThrusterRPMs>* rpms;
    TopicBuffer<smarc_msgs::ThrusterRPM>* rpm1;
    TopicBuffer<smarc_msgs::ThrusterRPM>* rpm2;
    TopicBuffer<std_msgs::Float64>* depth;
    TopicBuffer<std_msgs::Float64>* pitch;
    TopicBuffer<std_msgs::Float64>* roll;
    TopicBuffer<std_msgs::Float64>* yaw;
public:
    bool is_emergency() { return was_leak; }
    void show_window(bool& show_dashboard_window);
    SamDashboardWidget(roswasm::NodeHandle& nh);
};

class SamTeleopWidget {
private:
    bool enabled;
    lolo_msgs::ThrusterAngles angles_msg;
    smarc_msgs::ThrusterRPM rpm1_msg;
    smarc_msgs::ThrusterRPM rpm2_msg;
    roswasm::Publisher rpm1_pub;
    roswasm::Publisher rpm2_pub;
    roswasm::Publisher angle_pub;
    roswasm::Timer pub_timer;
public:
    void pub_callback(const ros::TimerEvent& e);
    void show_window(bool& show_teleop_window);
    SamTeleopWidget(roswasm::NodeHandle& nh);
};

} // namespace roswasm_webgui

#endif // ROSWASM_EXAMPLES_H
