#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sysmonitor_interfaces/msg/sysmon.hpp"
#include "fault_detection/magiclib.h"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber"), count_(0)
    {
      subscription_ = this->create_subscription<sysmonitor_interfaces::msg::Sysmon>(
      "Orin_telemetry", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sysmonitor_interfaces::msg::Sysmon & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard Orin Telemetry");
      try
      {
        magic_function(msg.cpu_usage,msg.cpu_temp,msg.ram_usage,msg.gpu_usage,msg.gpu_temp /*,msg.gpuram_usage*/);  
      }
      catch (const std::exception & e)
      {
          //stampa del messaggio di eccezione 
          RCLCPP_ERROR(this->get_logger(),
            "Exception of type %s: %s",
            typeid(e).name(),   
            e.what());    
            
          //stampa del messaggio che ha generato l'eccezione
          RCLCPP_WARN(this->get_logger(),
            "Telemetry value that caused fault: cpu_usage=%f, cpu_temp=%f, ram_usage=%f, gpu_usage=%f, gpu_temp=%f",
            msg.cpu_usage, msg.cpu_temp, msg.ram_usage, msg.gpu_usage, msg.gpu_temp); 
      }

    }
    rclcpp::Subscription<sysmonitor_interfaces::msg::Sysmon>::SharedPtr subscription_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
