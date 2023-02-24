import rclpy
from rclpy.node import Node
from serial import Serial
from std_msgs.msg import String

class NodeTest(Node):
    def __init__(self, name:str, dev:str):
        super().__init__(name)
        self.dev = dev
        self.setup()
    
    def setup(self):
        self.ser = Serial(self.dev, baudrate=115200)
        self.ser.flush()
        self.ser.last_string = ""
        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.publisher_ = self.create_publisher(String, 'imu_topic', 10)

    def timer_callback(self):
        msg = String()
        if(self.ser.in_waiting):
            raw =self.ser.readline()
            self.last_string = raw.decode('utf-8')
        msg.data = self.last_string
        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = NodeTest(name='imu_serial_converter_node', dev='/dev/ttyACM0')
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()