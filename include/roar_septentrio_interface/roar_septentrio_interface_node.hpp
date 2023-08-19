#ifndef SEPTENTRIO_INTERFACE_NODE_HPP
#define SEPTENTRIO_INTERFACE_NODE_HPP
#include "GeographicLib/Geocentric.hpp"
#include "GeographicLib/LocalCartesian.hpp"
#include "rclcpp/rclcpp.hpp"
#include "gps_msgs/msg/gps_fix.hpp"
#include "nav_msgs/msg/odometry.hpp"

namespace ROAR
{
    namespace SeptentrioInterface
    {
        struct GeodeticPosition
        {
            double latitude;
            double longitude;
            double altitude;
        };
        struct CartesianPosition
        {
            double x;
            double y;
            double z;
        };
        class SeptentrioInterfaceNode : public rclcpp::Node
        {
        public:
            SeptentrioInterfaceNode();
            ~SeptentrioInterfaceNode();

        private:
            void parse_datum();
            void gps_callback(const gps_msgs::msg::GPSFix::SharedPtr msg);
            void convert_gnss_to_local_cartesian(GeodeticPosition inputGeoPosition, CartesianPosition &outputCartesianPosition);

            GeodeticPosition map_origin_;
            GeographicLib::LocalCartesian proj;

            // subscribers
            rclcpp::Subscription<gps_msgs::msg::GPSFix>::SharedPtr gps_subscriber_;

            // publishers
            rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher_;
        };
    } // namespace SeptentrioInterface
}

#endif // SEPTENTRIO_INTERFACE_NODE_HPP