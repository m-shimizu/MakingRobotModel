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

## 2-2. CMakeLists.txt  

## 2-3. cpp file and header file  
* [Plugins101](http://gazebosim.org/tutorials/?tut=plugins_hello_world)  


## 2-4. build  

## 2-5. velocity control

## 2-6. position(angle) conttol

# 3. Create a teleoperation controller  

## 3-1. CMakeLists.txt  

## 3-2. cpp file and header file  

## 3-3. build  

## 3-4. Using the teleoperation controller   
