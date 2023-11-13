^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package octomap_msgs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.0.0 (2020-07-01)
------------------
* Change version to 2.0.0 for ROS2; update maintainer
* Porting to ROS2, based on ROS version 0.3.3 `#13 <https://github.com/OctoMap/octomap_msgs/pull/13>`_
* Contributors: Yan Yu, Ibai Apellaniz, Henning Kayser, Wolfgang Merkt

0.3.3 (2016-06-11)
------------------
* Fix for binary ColorOcTrees messages
* Removed check for "OcTree" id in binary deserialization, see Issue `#4 <https://github.com/OctoMap/octomap_msgs/issues/4>`_ and `#5 <https://github.com/OctoMap/octomap_msgs/issues/5>`_
* Contributors: Armin Hornung, Felix Endres

0.3.2 (2014-11-07)
------------------
* Fixing issue octomap_rviz_plugins/#10: Allow deserializing an empty octree
* Contributors: Armin Hornung

0.3.1 (2013-07-15)
------------------
* Removed [binary|full]MsgDataToMap, created only incomplete OctoMap objects
  Replacement: use [binary|full]MsgToMap or msgToMap()

0.3.0 (2013-04-02)
------------------
* Removed deprecated conversions

0.2.9 (2013-01-17)
------------------
* Fix: octree resolution is double, not float

0.2.8 (2013-01-08)
------------------
* Fixed msg resolution field, binaryMsgToMap

0.2.7 (2013-01-03)
------------------
* fixed package.xml depends / build_depend

0.2.6 (2012-12-17)
------------------
* adjusted message generation to recent catkin changes & switched version to 0.2.6

0.2.5 (2012-12-08)
------------------
* more catkin fixing
* copyright is not supported for package.xml
* moving catkin_package() after generate_messages() per latest changes to catkin

0.2.3 (2012-10-12)
------------------
* comply to the new catkin API
* add function to convert a message to map
* changed message format to contain only data, meta information stored in new message fields (untested for Groovy)
* documentation, fixes
* remove id from message and bump stack version
* New octomap_msg (de-) serialization / conversion functions from and to messages; old ones are now deprecated


0.1.1 (2012-04-20 14:16)
------------------------
* missing includes added

0.1.0 (2012-04-20 10:22)
------------------------
* Turned octomap_msgs and octomap_ros into unary stacks, code in octomap_mapping adjusted
