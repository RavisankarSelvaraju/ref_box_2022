#include <atwork_commander_gen/TaskGenerator.h>

#include <ros/ros.h>
#include <ros/console.h>

#include <exception>
#include <thread>
#include <chrono>

using namespace atwork_commander;
using namespace std;
using namespace chrono;

static void activateDebug() {
  if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
    ros::console::notifyLoggerLevelsChanged();
    this_thread::sleep_for(seconds(1)); // Necessary to allow rosconsole to react to logger level change
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "example_task_generator");
  ros::NodeHandle nh("~");
  activateDebug();

  try {
    TaskGenerator gen("arena", "tasks", "plugin");
    ROS_INFO_STREAM("[EXAMPLE-GEN] Arena Description:" << endl << gen.config().arena() );
    ROS_INFO_STREAM("[EXAMPLE-GEN] Task Definitions:" << endl << gen.config().tasks() );
    auto task = gen(string("example"));
    ROS_DEBUG_STREAM("[EXAMPLE-GEN] Tasks:\n" << task);
  }
  catch(exception& e) {
    ROS_ERROR_STREAM_NAMED("example", "[REFBOX-GEN] Exception occured: \n" << e.what());
  }

  while(ros::ok())
    ros::spin();
  return 0;
}
