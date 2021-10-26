#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdio.h>

#include "dragoon_messages/stateCmd.h"

#include "executive_panel.h"

namespace executive_panel {

ExecutivePanel::ExecutivePanel(QWidget *parent) : rviz::Panel(parent) {
  cmd_pub_ = nh_.advertise<dragoon_messages::stateCmd>("/commands", 1);

  QHBoxLayout *button_layout1 = new QHBoxLayout;
  QPushButton *start_btn = new QPushButton("START");
  QPushButton *stop_btn = new QPushButton("STOP");
  button_layout1->addWidget(start_btn);
  button_layout1->addWidget(stop_btn);

  QHBoxLayout *button_layout2 = new QHBoxLayout;
  QPushButton *goal_reached_btn = new QPushButton("GOAL REACHED");
  QPushButton *new_human_btn = new QPushButton("NEW HUMAN");
  button_layout2->addWidget(goal_reached_btn);
  button_layout2->addWidget(new_human_btn);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(button_layout1);
  layout->addLayout(button_layout2);

  setLayout(layout);

  connect(start_btn, SIGNAL(clicked()), this, SLOT(sendStart()));
  connect(stop_btn, SIGNAL(clicked()), this, SLOT(sendStop()));
  connect(goal_reached_btn, SIGNAL(clicked()), this, SLOT(sendGoalReached()));
  connect(new_human_btn, SIGNAL(clicked()), this, SLOT(sendNewHuman()));
}

void ExecutivePanel::sendCmd(const std::string &cmd) {
  if (ros::ok()) {
    dragoon_messages::stateCmd msg;
    msg.event = cmd;
    msg.value = true;
    cmd_pub_.publish(msg);
  }
}

void ExecutivePanel::sendStart() { sendCmd("START"); }
void ExecutivePanel::sendStop() { sendCmd("STOP"); }
void ExecutivePanel::sendGoalReached() { sendCmd("GOAL REACHED"); }
void ExecutivePanel::sendNewHuman() { sendCmd("NEW HUMAN"); }

} // namespace executive_panel

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(executive_panel::ExecutivePanel, rviz::Panel)
