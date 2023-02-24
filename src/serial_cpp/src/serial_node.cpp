#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <SerialStateMachine/StateMachine.hpp>
#include "rclcpp/rclcpp.hpp"
#include <CppLinuxSerial/SerialPort.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;
using namespace mn::CppLinuxSerial;
using namespace SerialStateMachine;

class SerialNode : public rclcpp::Node
{
SerialPort serialPort;
StateMachine sm;
std::chrono::steady_clock time;

public:
    SerialNode(std::string devname, SerialPort port) : Node("serial_cpp_publisher_node"), count_(0)
    {   
        serialPort = port;
        smInit(&sm);
        publisher_ = this->create_publisher<std_msgs::msg::String>("serial_data_topic",10);

        serialPort.SetTimeout(100);
        serialPort.Open();
        timer_ = this->create_wall_timer(
        1ms, std::bind(&SerialNode::timer_callback,this)
        );
    }
    
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        static int index;
        index++;
        std::string readData;
        if(serialPort.Available()) 
        {
            serialPort.Read(readData);
            append(&sm, readData);

            message.data = readData;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s''%i'", readData.c_str(), index);
            
            index=0;
        }
        publisher_->publish(message);
    }
//    Serial.write("\r\n");
//    Serial.println();
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::string devname = "/dev/ttyACM0";
    auto node = std::make_shared<SerialNode>(devname, SerialPort("/dev/ttyACM0", BaudRate::B_460800));
    rclcpp::spin(node);
    rclcpp::shutdown();
}
