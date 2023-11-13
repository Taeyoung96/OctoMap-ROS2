// Copyright 2021, Daisuke Nishimatsu. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the Willow Garage nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <gtest/gtest.h>

#include <sensor_msgs/point_cloud2_iterator.hpp>

#include <octomap_ros/conversions.hpp>

constexpr double epsilon = 1e-6;

TEST(conversions, pointOctomapToMsg)
{
  using octomap::pointOctomapToMsg;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto octo_p = octomap::point3d(x, y, z);
  const auto geom_p = pointOctomapToMsg(octo_p);

  EXPECT_DOUBLE_EQ(geom_p.x, x);
  EXPECT_DOUBLE_EQ(geom_p.y, y);
  EXPECT_DOUBLE_EQ(geom_p.z, z);
}

TEST(conversions, pointMsgToOctomap)
{
  using octomap::pointMsgToOctomap;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto geom_p = geometry_msgs::build<geometry_msgs::msg::Point>().x(x).y(y).z(z);
  const auto octo_p = pointMsgToOctomap(geom_p);

  EXPECT_DOUBLE_EQ(octo_p.x(), x);
  EXPECT_DOUBLE_EQ(octo_p.y(), y);
  EXPECT_DOUBLE_EQ(octo_p.z(), z);
}

TEST(conversions, pointOctomapToTf)
{
  using octomap::pointOctomapToTf;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto octo_p = octomap::point3d(x, y, z);
  const auto tf_v = pointOctomapToTf(octo_p);

  EXPECT_DOUBLE_EQ(tf_v.x(), x);
  EXPECT_DOUBLE_EQ(tf_v.y(), y);
  EXPECT_DOUBLE_EQ(tf_v.z(), z);
}

TEST(conversions, pointTfToOctomap)
{
  using octomap::pointTfToOctomap;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto tf_v = tf2::Vector3(x, y, z);
  const auto octo_p = pointTfToOctomap(tf_v);

  EXPECT_DOUBLE_EQ(octo_p.x(), x);
  EXPECT_DOUBLE_EQ(octo_p.y(), y);
  EXPECT_DOUBLE_EQ(octo_p.z(), z);
}

TEST(conversions, quaternionOctomapToTf)
{
  using octomap::quaternionOctomapToTf;

  const double u = 1.0;
  const double x = 2.0;
  const double y = 3.0;
  const double z = 4.0;

  const auto octo_q = octomath::Quaternion(u, x, y, z);
  const auto tf_q = quaternionOctomapToTf(octo_q);

  EXPECT_DOUBLE_EQ(tf_q.w(), u);
  EXPECT_DOUBLE_EQ(tf_q.x(), x);
  EXPECT_DOUBLE_EQ(tf_q.y(), y);
  EXPECT_DOUBLE_EQ(tf_q.z(), z);
}

TEST(conversions, quaternionTfToOctomap)
{
  using octomap::quaternionTfToOctomap;

  const double w = 1.0;
  const double x = 2.0;
  const double y = 3.0;
  const double z = 4.0;

  const auto tf_q = tf2::Quaternion(x, y, z, w);
  const auto octo_q = quaternionTfToOctomap(tf_q);

  EXPECT_DOUBLE_EQ(octo_q.u(), w);
  EXPECT_DOUBLE_EQ(octo_q.x(), x);
  EXPECT_DOUBLE_EQ(octo_q.y(), y);
  EXPECT_DOUBLE_EQ(octo_q.z(), z);
}

TEST(conversions, poseOctomapToTf)
{
  using octomap::poseOctomapToTf;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto octo_p = octomap::point3d(x, y, z);

  const double rot_u = 1.0;
  const double rot_x = 2.0;
  const double rot_y = 3.0;
  const double rot_z = 4.0;

  const auto octo_q = octomath::Quaternion(rot_u, rot_x, rot_y, rot_z);

  const auto octo_pose = octomap::pose6d(octo_p, octo_q);
  const auto tf_trans = poseOctomapToTf(octo_pose);
  const auto length = octo_q.norm();

  EXPECT_DOUBLE_EQ(tf_trans.getOrigin().x(), x);
  EXPECT_DOUBLE_EQ(tf_trans.getOrigin().y(), y);
  EXPECT_DOUBLE_EQ(tf_trans.getOrigin().z(), z);
  EXPECT_NEAR(tf_trans.getRotation().w() * length, rot_u, epsilon);
  EXPECT_NEAR(tf_trans.getRotation().x() * length, rot_x, epsilon);
  EXPECT_NEAR(tf_trans.getRotation().y() * length, rot_y, epsilon);
  EXPECT_NEAR(tf_trans.getRotation().z() * length, rot_z, epsilon);
}

TEST(conversions, poseTfToOctomap)
{
  using octomap::poseTfToOctomap;

  const double x = 1.0;
  const double y = 2.0;
  const double z = 3.0;

  const auto tf_v = tf2::Vector3(x, y, z);

  const double rot_w = 1.0;
  const double rot_x = 2.0;
  const double rot_y = 3.0;
  const double rot_z = 4.0;

  const auto tf_q = tf2::Quaternion(rot_x, rot_y, rot_z, rot_w);

  const auto tf_trans = tf2::Transform(tf_q, tf_v);
  const auto octo_pose = poseTfToOctomap(tf_trans);
  const auto length = tf_q.length();

  EXPECT_DOUBLE_EQ(octo_pose.trans().x(), x);
  EXPECT_DOUBLE_EQ(octo_pose.trans().y(), y);
  EXPECT_DOUBLE_EQ(octo_pose.trans().z(), z);
  EXPECT_NEAR(octo_pose.rot().u() * length, rot_w, epsilon);
  EXPECT_NEAR(octo_pose.rot().x() * length, rot_x, epsilon);
  EXPECT_NEAR(octo_pose.rot().y() * length, rot_y, epsilon);
  EXPECT_NEAR(octo_pose.rot().z() * length, rot_z, epsilon);
}

TEST(conversions, pointsOctomapToPointCloud2)
{
  using octomap::pointsOctomapToPointCloud2;

  octomap::point3d_list points{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  sensor_msgs::msg::PointCloud2 ros_points{};
  sensor_msgs::PointCloud2Modifier modifier{ros_points};
  modifier.setPointCloud2FieldsByString(1, "xyz");
  pointsOctomapToPointCloud2(points, ros_points);
  sensor_msgs::PointCloud2Iterator<float> iter_x(ros_points, "x");
  sensor_msgs::PointCloud2Iterator<float> iter_y(ros_points, "y");
  sensor_msgs::PointCloud2Iterator<float> iter_z(ros_points, "z");

  EXPECT_EQ(modifier.size(), 3U);
  EXPECT_DOUBLE_EQ(*iter_x, 1.0);
  EXPECT_DOUBLE_EQ(*iter_y, 2.0);
  EXPECT_DOUBLE_EQ(*iter_z, 3.0);
  ++iter_x;
  ++iter_y;
  ++iter_z;
  EXPECT_DOUBLE_EQ(*iter_x, 4.0);
  EXPECT_DOUBLE_EQ(*iter_y, 5.0);
  EXPECT_DOUBLE_EQ(*iter_z, 6.0);
  ++iter_x;
  ++iter_y;
  ++iter_z;
  EXPECT_DOUBLE_EQ(*iter_x, 7.0);
  EXPECT_DOUBLE_EQ(*iter_y, 8.0);
  EXPECT_DOUBLE_EQ(*iter_z, 9.0);
}

TEST(conversions, pointCloud2ToOctomap)
{
  using octomap::pointCloud2ToOctomap;

  sensor_msgs::msg::PointCloud2 ros_points{};
  sensor_msgs::PointCloud2Modifier modifier{ros_points};
  modifier.setPointCloud2FieldsByString(1, "xyz");
  modifier.resize(3);
  sensor_msgs::PointCloud2Iterator<float> iter_x(ros_points, "x");
  sensor_msgs::PointCloud2Iterator<float> iter_y(ros_points, "y");
  sensor_msgs::PointCloud2Iterator<float> iter_z(ros_points, "z");
  int val{0};
  for (size_t i = 0; i < modifier.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
    *iter_x = static_cast<float>(++val);
    *iter_y = static_cast<float>(++val);
    *iter_z = static_cast<float>(++val);
  }

  octomap::Pointcloud octo_points{};
  pointCloud2ToOctomap(ros_points, octo_points);

  EXPECT_EQ(octo_points.size(), 3U);
  EXPECT_DOUBLE_EQ(octo_points[0].x(), 1.0);
  EXPECT_DOUBLE_EQ(octo_points[0].y(), 2.0);
  EXPECT_DOUBLE_EQ(octo_points[0].z(), 3.0);
  EXPECT_DOUBLE_EQ(octo_points[1].x(), 4.0);
  EXPECT_DOUBLE_EQ(octo_points[1].y(), 5.0);
  EXPECT_DOUBLE_EQ(octo_points[1].z(), 6.0);
  EXPECT_DOUBLE_EQ(octo_points[2].x(), 7.0);
  EXPECT_DOUBLE_EQ(octo_points[2].y(), 8.0);
  EXPECT_DOUBLE_EQ(octo_points[2].z(), 9.0);
}
