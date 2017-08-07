__Gazebo quick learning__  
# Making a Robot Model in Gazebo  
Description of rupidly making a robot in gazebo with a model plugin and a control softwear.

## 0. Overview

    1. Create a model  
        1-1. About SDF format  
        1-2. Primitive model creation  
        1-3. Polygon model creation  
        1-4. Joint definition  
        1-5. Friction definition  
        1-6. Inertial definition   

    2. Create a plugin  
        2-0. install additional packages  
        2-1. \<plugin\> in SDF  
        2-2. CMakeLists.txt  
        2-3. cpp file and header file  
        2-4. build  
        2-5. velocity control
        2-6. position(angle) conttol

    3. Create a teleoperation controller  
        3-1. CMakeLists.txt  
        3-2. cpp file and header file  
        3-3. build  
        3-4. Using the teleoperation controller   

## 1. Create a model  

### 1-1. About SDF format  
* [Make a mobile robot](http://gazebosim.org/tutorials?tut=build_robot)  
* [Specification SDF](http://sdformat.org/spec?elem=geometry&ver=1.5)  

### 1-2. Primitive model creation  
* [Make a mobile robot](http://gazebosim.org/tutorials?tut=build_robot)  
* SDF VERSION = 1.5 or higher  
* MODEL NAME = FOLDER NAME  
* \<pose\>x y z roll pich yaw\<\/pose\>

### 1-3. Polygon model creation  

### 1-4. Joint definition  

### 1-5. Friction definition  

### 1-6. Inertial definition 

# 2. Create a plugin  
## 2-0. install additional packages  
    $ sudo apt-get install -y cmake g++ protobuf-compiler pavucontrol libgazebo7 libgazebo7-dev ros-kinetic-desktop ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control ros-kinetic-ros-control ros-kinetic-ros-controllers ros-kinetic-image-view2 ros-kinetic-rqt ros-kinetic-rqt-common-plugins ros-kinetic-joy ros-kinetic-teleop-twist-keyboard ros-kinetic-message-to-tf ros-kinetic-tf2-geometry-msgs ros-kinetic-audio-common  
    $ setup_ros  

## 2-1. \<plugin\> in SDF  

## 2-2. CMakeLists.txt  

## 2-3. cpp file and header file  

## 2-4. build  

## 2-5. velocity control

## 2-6. position(angle) conttol

# 3. Create a teleoperation controller  

## 3-1. CMakeLists.txt  

## 3-2. cpp file and header file  

## 3-3. build  

## 3-4. Using the teleoperation controller   
