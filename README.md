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
        2-1. <plugin> in SDF  
        2-2. CMakeLists.txt  
        2-3. cpp file and header file  
        2-4. build  
        2-5. velocity control
        2-6. position(angle) control

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
* name should be unique
* \<pose\> under \<link\> moves whole objects in the link
* \<pose\> under \<visual\> and \<collision\> moves a object in the visual and the collision
* In \<joint\>, joint posision and joint vector should be defined in a child model coordinate without \<pose\> under child model's \<link\>

### 1-3. Polygon model creation  
* [Using a polygon](http://gazebosim.org/tutorials/?tut=attach_meshes)  

```xml
        <mesh>
          <uri>model://pioneer2dx/meshes/chassis.dae</uri>
          <scale>0.9 0.5 0.5</scale>
        </mesh>
```

### 1-4. Joint definition  

### 1-5. Friction definition  
* In \<collision\> element, you can add following lines.  

```xml
          <surface>
            <friction>
              <ode>
                <mu>0</mu>
                <mu2>0</mu2>
                <slip1>1.0</slip1>
                <slip2>1.0</slip2>
              </ode>
            </friction>
          </surface>
```

### 1-6. Inertial definition 
* [Inertial parameters of triangle meshes](http://gazebosim.org/tutorials?tut=inertia)

```xml
    <inertial>
      <pose>0.1259255 0.250 0.0012545 0 0 0</pose>
      <mass>10</mass>
      <inertia>
        <ixx>5.798e-6</ixx>
        <ixy>-1.577e5</ixy>
        <ixz>-5.188e4</ixz>
        <iyy>3.72e-6</iyy>
        <iyz>-1946203007.5e-6</iyz>
        <izz>6.26978e-6</izz>
      </inertia>
    </inertial>
```

# 2. Create a plugin  
## 2-0. install additional packages  
    $ sudo apt-get install -y cmake g++ protobuf-compiler pavucontrol libgazebo7 libgazebo7-dev ros-kinetic-desktop ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control ros-kinetic-ros-control ros-kinetic-ros-controllers ros-kinetic-image-view2 ros-kinetic-rqt ros-kinetic-rqt-common-plugins ros-kinetic-joy ros-kinetic-teleop-twist-keyboard ros-kinetic-message-to-tf ros-kinetic-tf2-geometry-msgs ros-kinetic-audio-common  
    $ setup_ros  

## 2-1. \<plugin\> in SDF  

```xml  
  <plugin name="robotmoving" filename="libMyDiffDrivePlugin.so">
    <left_joint>left_wheel_hinge</left_joint>
    <right_joint>right_wheel_hinge</right_joint>
    <sholder_joint>sholder_hinge</sholder_joint>
  </plugin>
```  

## 2-2. CMakeLists.txt  

```cmake
    add_library(PLUGINAME SHARED src/SOURCEFILENAME.cc)
    target_link_libraries(PLUGINAME ${GAZEBO_LIBRARIES})
```

## 2-3. cpp file and header file  
* [Plugins101](http://gazebosim.org/tutorials/?tut=plugins_hello_world)  

## 2-4. build  
Just do following commands.  

    $ cd ~/MakingRobotModel
    $ catkin_make

## 2-5. velocity control

```c
		this->leftJoint->SetVelocity(0, left_v);
		this->rightJoint->SetVelocity(0, right_v);
```

## 2-6. position(angle) control
See also [JointController](http://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1physics_1_1JointController.html).  
Torques fitted power and direction calculated by each moment should be set.  
Seting nice torque is very effective to stop vibration of motion.  

__PREPARE A ARM MODEL USING following codes__  

```c
    float leftTargetAngle = 0, rightTargetAngle = 0;
    float leftP = leftTargetAngle - this->leftJoint->GetAngle(0).Radian(),
          rightP = rightTargetAngle - this->rightJoint->GetAngle(0).Radian();
    leftP *= 10;
    rightP *= 10;
    // Set nice torque.  
    this->leftJoint->SetForce(0, leftP);
    this->rightJoint->SetForce(0, rightP);
    // Set PID parameters.  
    this->model->GetJointController()->SetPositionPID(this->leftJoint->GetScopedName(), common::PID(1, 0, 0));
    this->model->GetJointController()->SetPositionPID(this->rightJoint->GetScopedName(), common::PID(1, 0, 0));
    // Set distination angle
    this->model->GetJointController()->SetPositionTarget(this->leftJoint->GetScopedName(), leftTargetAngle); 
    this->model->GetJointController()->SetPositionTarget(this->rightJoint->GetScopedName(), rightTargetAngle); 
    // Flush them.
    this->model->GetJointController()->Update();

```

# 3. Create a teleoperation controller  

## 3-1. CMakeLists.txt  
Maybe you want a robot controller to be an executable file.  
Then you should add following 2 lines at the end of CMakeLists.txt.  

```
add_executable(teleop_joy src/teleop_joy.cpp)
target_link_libraries(teleop_joy ${catkin_LIBRARIES})
```

## 3-2. cpp file and header file  
In this study, the robot controller program is,  

    ~/MakingRobotModel/src/my_arm_robot/src/teleop_joy.cpp  

This source file includes an interface to use a joystick.  
For getting joystick information, another package named 'joy' is required.  
The package joy reads a joystick status and outputs a topic named '/joy'.  
This robot controller program is a translator between topic '/joy' and topic '/my_arm_robot/cmd_arm' and topic '/my_arm_robot/cmd_hand'.   
A plugin included by my_arm_robot reads topic '/my_arm_robot/cmd_arm' and '/my_arm_robot/cmd_hand' to get his joint's target angle.  

## 3-3. build  
To build the robot controller, only you have to do is catkin_make.  

## 3-4. Using the teleoperation controller   
Your robot controller was made as a part of a ROS package.  
Then you can execute it by using following ros command.  

    __TERMINAL1__  
    $ cd ~/MakingRobotModel  
    $ source setup.bash  
    $ roslaunch my_arm_robot empty.launch  

    __TERMINAL2__  
    $ cd ~/MakingRobotModel  
    $ source setup.bash  
    $ roslaunch my_arm_robot teleop_joy.launch  

