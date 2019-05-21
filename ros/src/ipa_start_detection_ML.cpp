
#include "ipa_start_detection_ML.h"
#include <opencv2/opencv.hpp>
#include <sensor_msgs/CameraInfo.h>
#include <message_filters/subscriber.h>


StartHandleDetectionML::StartHandleDetectionML(ros::NodeHandle nh, sensor_msgs::PointCloud2::Ptr point_cloud_out_msg) :
nh_(nh), point_cloud_out_msg_(point_cloud_out_msg)
{

	initCameraNode(nh,point_cloud_out_msg);	
}

void StartHandleDetectionML::pointcloudCallback(const sensor_msgs::PointCloud2::ConstPtr& point_cloud_msg)
{
		
	pcl::console::setVerbosityLevel(pcl::console::L_ALWAYS);

	//create new point cloud in pcl format: pointcloud_in_pcl_format
	pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud_in_pcl_format(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr published_pc(new pcl::PointCloud<pcl::PointXYZRGB>);

	//transform imported pointcloud point_cloud_msg to pointcloud_in_pcl_format
	pcl::fromROSMsg(*point_cloud_msg, *pointcloud_in_pcl_format);

	std::cout<<"working"<<std::endl;


	


}


void StartHandleDetectionML::initCameraNode(ros::NodeHandle nh, sensor_msgs::PointCloud2::Ptr point_cloud_out_msg)
{
	std::cout << "Initialising StartHandleDetection Constructor." << std::endl;

	// publish template & cluster
	pub1_ = nh_.advertise<sensor_msgs::PointCloud2>(TOPIC_POINT_CLOUD_OUT1,1);

	(pub1_) ? std::cout << "Pub1 is valid." << std::endl : std::cout << "Pub is not valid." << std::endl;
	ros::Subscriber point_cloud_sub1_ = nh_.subscribe<sensor_msgs::PointCloud2>(TOPIC_POINT_CLOUD_IN, 1, &StartHandleDetectionML::pointcloudCallback, this);

	message_filters::Subscriber<CameraInfo> info_sub(nh, "camera_info", 1);

	ros::Duration(1).sleep();

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}

	if (!ros::ok()){
		std::cout << "Quit publishing" << std::endl;
	}
	std::cout << "StartHandleDetection Constructor Initialised." << std::endl;
}
		
