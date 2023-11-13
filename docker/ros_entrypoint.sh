#!/bin/bash
 
set -e

# Ros build
source "/opt/ros/humble/setup.bash"

echo "==============Octomap server ROS2 Docker Env Ready================"

cd /root/ros2_ws

exec "$@"
