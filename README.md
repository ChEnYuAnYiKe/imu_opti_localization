## imu_opti_localization 定位包使用说明
### 1. 安装
将本文件夹中的三个package放到你的工作空间中，执行catkin_make

### 2. 配置

#### fdilink_ahrs Package
在使用该驱动包之前，sudo运行`/fdilink_ahrs/wheeltec_udev.sh`文件，更改imu端口号

在/fdilink_ahrs/launch/ahrs_data.launch中，确保：
```shell
<param name="device_type"  value="0"/>
```
如果想要读取imu提供的各类数据，其输出话题为/imu
#### imu_gps_localization Package
确定无人机在Optitrack系统下的位置话题，并在`imu_gps_localization/ros_wrapper/src/localization_wrapper.cpp`文件中第47行修改:
```shell
uwb_sub_ = nh.subscribe("/vrpn_client_node/yourMavNodeName/pose", 200, &LocalizationWrapper::UwbCallback, this);
```
中修改为对应的话题

### 3. 使用
#### 启动外置imu驱动：
```shell
roslaunch fdilink_ahrs ahrs_data.launch
```

#### 启动imu低通滤波：
```shell
roslaunch imu_filter imu_filter.launch
```
#### 启动optitrack节点：
```shell
roslaunch vrpn_client_ros sample.launch server:=192.168.31.67
```
#### 启动定位节点：
```shell
roslaunch imu_gps_localization imu_gps_localization.launch
```

### 4. 说明
* 在上电时，需将飞机放置在飞场中的起飞点并保持静止，同时机头朝向应为正前方，否则姿态输出将会有固定偏差
* 如果使用外置imu提供的欧拉角或者四元数，为了和optitrack处于同一坐标系中，读数时需要将yaw(欧拉角中)取负值 / w、x(四元数中)取负值
[建议自行手飞测试，以确定是否需要取负值]