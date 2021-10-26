#pragma once

#include <ros/ros.h>
#include <rviz/panel.h>

namespace executive_panel{

class ExecutivePanel : public rviz::Panel {
  Q_OBJECT
public:
  ExecutivePanel(QWidget *parent = 0);
protected Q_SLOTS:
  void sendCmd(const std::string &cmd);
  void sendStart();
  void sendStop();
  void sendGoalReached();
  void sendNewHuman();
protected:
  ros::Publisher cmd_pub_;
  ros::NodeHandle nh_;
};

}
