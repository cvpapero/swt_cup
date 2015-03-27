#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "f4_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.header.frame_id = "map";
  //âããÂ®ããÄŽãÄµãÂ idãmapãÂ«å€æŽããããÂšãÂ§ãÃ¥°å³åº§æšè±»ãÂ«ãÂªã
  //"base_link"ãÂ ãÂšãÂ­ããã×º§æšè±»

  int i=0;
  double goal_x,goal_y;
  double goal_z,goal_w;

  while(ros::ok()){

    if ((i%6)==0){

      goal_x=4.87;
      goal_y=10.4;
      goal_z=0.710261039133;
      goal_w= 0.703938389556;

    }else if(i%6==1){
      goal_x=3.07;
      goal_y=46.8;
      goal_z=-0.999393052521;
      goal_w=0.0348357083019;
    }else if(i%6==2){

      goal_x=-17.7;
      goal_y=45.3;
      goal_z=-0.678078005643;
      goal_w=0.734989944328;

    }else if(i%6==3){
      goal_x=-15.3;
      goal_y=7.9;
      goal_z= -0.00787276890063;
      goal_w= 0.999969009275;
    }else if(i%6==4){
      goal_x=4.71;
      goal_y=9.71;
      goal_z=-0.710581078171;
      goal_w=0.703615329101;
    }else if(i%6==5){
      goal_x=5.22;
      goal_y=-6.51;
      goal_z=-0.710581078171;
      goal_w=0.703615329101;
    }

    ++i;

    goal.target_pose.pose.position.x = goal_x;
    goal.target_pose.pose.position.y = goal_y;
    goal.target_pose.pose.orientation.z = goal_z;
    goal.target_pose.pose.orientation.w = goal_w;

    ROS_INFO("Sending goal %d",i%4);
    ac.sendGoalAndWait(goal);
    ac.waitForResult();
   
    
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray");
    else
      ROS_INFO("Failed");
  }
  return 0;
}
