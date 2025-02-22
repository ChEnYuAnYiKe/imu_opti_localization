#pragma once

#include "imu_gps_localizer/base_type.h"
#include "imu_gps_localizer/gps_processor.h"
#include "imu_gps_localizer/imu_processor.h"
#include "imu_gps_localizer/initializer.h"
#include "imu_gps_localizer/uwb_processor.h"
#include <Eigen/Core>

namespace ImuGpsLocalization {

class ImuGpsLocalizer {
public:
	ImuGpsLocalizer(const double acc_noise, const double gyro_noise,
	                const double acc_bias_noise, const double gyro_bias_noise,
	                const Eigen::Vector3d& I_p_Gps,
	                const Eigen::Vector3d& I_p_Uwb);

	bool ProcessImuData(const ImuDataPtr imu_data_ptr, State* fused_state);

	bool ProcessGpsPositionData(const GpsPositionDataPtr gps_data_ptr,
	                            Eigen::Vector3d* gps_enu);

	bool ProcessUwbData(const UwbDataPtr uwb_data_ptr);

private:
	std::unique_ptr<Initializer> initializer_;
	std::unique_ptr<ImuProcessor> imu_processor_;
	std::unique_ptr<GpsProcessor> gps_processor_;
	std::unique_ptr<UwbProcessor> uwb_processor_;

	bool initialized_;
	Eigen::Vector3d init_lla_; // The initial reference gps point.
	Eigen::Vector3d init_uwb_; // 初始化后第一个uwb位置点
	State state_;
};

} // namespace ImuGpsLocalization