#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include "butterworth_filter.h"

class ImuFilterNode {
public:
    ImuFilterNode() 
        : filter_x_(5.0, 400.0, 3),  // 2 Hz cutoff, 400 Hz sampling rate
          filter_y_(5.0, 400.0, 3),
          filter_z_(5.0, 400.0, 3),
          filter_x_ang_(7.0, 400.0, 3),
          filter_y_ang_(7.0, 400.0, 3),
          filter_z_ang_(7.0, 400.0, 3){
        ros::NodeHandle nh;
        imu_sub_ = nh.subscribe("/imu", 100, &ImuFilterNode::imuCallback, this);
        filtered_imu_pub_ = nh.advertise<sensor_msgs::Imu>("/imu_filtered", 100);
    }

    void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
        // Apply Butterworth filter to accelerometer data
        double filtered_x = filter_x_.apply(msg->linear_acceleration.x);
        double filtered_y = filter_y_.apply(msg->linear_acceleration.y);
        double filtered_z = filter_z_.apply(msg->linear_acceleration.z);
        // double filtered_x_ang = filter_x_ang_.apply(msg->angular_velocity.x);
        // double filtered_y_ang = filter_y_ang_.apply(msg->angular_velocity.y);
        // double filtered_z_ang = filter_z_ang_.apply(msg->angular_velocity.z);

        // Create a new IMU message with filtered accelerometer data
        sensor_msgs::Imu filtered_msg = *msg;
        filtered_msg.linear_acceleration.x = filtered_x;
        filtered_msg.linear_acceleration.y = filtered_y;
        filtered_msg.linear_acceleration.z = filtered_z;
        // filtered_msg.angular_velocity.x = filtered_x_ang;
        // filtered_msg.angular_velocity.y = filtered_y_ang;
        // filtered_msg.angular_velocity.z = filtered_z_ang;

        // Publish the filtered IMU message
        filtered_imu_pub_.publish(filtered_msg);
    }

private:
    ros::Subscriber imu_sub_;
    ros::Publisher filtered_imu_pub_;
    ButterworthFilter filter_x_;
    ButterworthFilter filter_y_;
    ButterworthFilter filter_z_;
    ButterworthFilter filter_x_ang_;
    ButterworthFilter filter_y_ang_;
    ButterworthFilter filter_z_ang_;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "imu_filter_node");
    ImuFilterNode imu_filter_node;
    ros::spin();
    return 0;
}
