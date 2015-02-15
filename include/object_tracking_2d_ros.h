#include "include/object_tracking_2D/tracker_irls.h"
#include "include/object_tracking_2D/tracker_pf_texture.h"
#include "include/object_tracking_2D/tracker_pf_textureless.h"

#include "ObjectDetection.h"

const std::string DEFAULT_IMAGE_TOPIC = "image";
const std::string DEFAULT_CAMERA_INFO_TOPIC = "camera_info";
const std::string DEFAULT_MARKER_TOPIC = "marker_array";
const std::string DEFAULT_DETECTIONS_TOPIC = "detections";

// ROS parts
ros::NodeHandlePtr node_;
boost::shared_ptr<image_transport::ImageTransport> image_;
sensor_msgs::CameraInfo camera_info_;

ros::Publisher marker_publisher_;
ros::Publisher ebt_publisher_;
ros::Subscriber info_subscriber;
image_transport::Subscriber image_subscriber;

// EBT parts
std::string ebt_tracker_type_;
std::string ebt_mesh_resource_;
int ebt_num_particle_;
int ebt_min_keypoint_;
double ebt_th_cm_;
std::string ebt_obj_path_;
std::string ebt_mesh_path_;
std::vector<float> ebt_init_pose_;
bool ebt_dull_edge_;
int ebt_width_;
int ebt_height_;
double ebt_sample_step_;
std::string ebt_intrinsic_;
std::string ebt_distortion_;
bool ebt_display_;
int ebt_th_canny_l_;
int ebt_th_canny_h_;

CvMat* pose_init_ = cvCreateMat(4, 4, CV_32F);
CvMat* pose_cv_;
Eigen::Matrix4d pose_;

TrackerBase* tracker_;

// Settings and local information
bool viewer_;
bool running_;
bool has_camera_info_;
std::string display_type_;

Eigen::Matrix4d GetDetectionTransform(ObjectDetection detection);
void InfoCallback(const sensor_msgs::CameraInfoConstPtr& camera_info);
void InfoCallback(const sensor_msgs::CameraInfoConstPtr& camera_info);
void ConnectCallback(const ros::SingleSubscriberPublisher& info);
void DisconnectCallback(const ros::SingleSubscriberPublisher& info);
void DisconnectHandler();
void GetParameterValues();
void SetupPublisher();
void InitializeTracker();
void InitializeROSNode();
