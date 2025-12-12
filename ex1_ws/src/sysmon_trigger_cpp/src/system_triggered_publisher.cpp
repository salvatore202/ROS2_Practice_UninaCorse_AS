#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <sysmonitor_interfaces/msg/sysmon.hpp>
#include <memory> 
#include <functional> 

class SystemTriggeredPublisher : public rclcpp::Node
{
public:
    SystemTriggeredPublisher() : rclcpp::Node("system_triggered_publisher")
    {
     
        message_to_send_ = std::make_shared<std_msgs::msg::Float64>();
        message_to_send_->data = 1.0; // Impostiamo il valore fisso di trigger
        
        // Crea Publisher
        publisher_ = this->create_publisher<std_msgs::msg::Float64>("/test", 10);
        
        // Crea Subscriber
        subscription_ = this->create_subscription<sysmonitor_interfaces::msg::Sysmon>(
            "/system_info",
            10, 
            std::bind(&SystemTriggeredPublisher::sysmon_callback, this, std::placeholders::_1)); 
    }

private:
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    rclcpp::Subscription<sysmonitor_interfaces::msg::Sysmon>::SharedPtr subscription_;
    
    //Messaggio da inviare su /test
    std_msgs::msg::Float64::SharedPtr message_to_send_;
    
    // Funzione di Callback
    void sysmon_callback(const sysmonitor_interfaces::msg::Sysmon::SharedPtr msg)
    {
        (void)msg; 
        
        publisher_->publish(*message_to_send_); 

        RCLCPP_INFO(this->get_logger(), "TRIGGER: Pubblicato: 1.0 su /test");
    }
};

// Funzione Main (resta invariata)
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SystemTriggeredPublisher>()); 
    rclcpp::shutdown();
    return 0;
}