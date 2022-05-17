# Arduino-Projects

Useful scripts for quick referece

## Radio Transmitter/Receiver using NRF24L01 for both Ardunio Uno and Nano
Note: Both radio modules require greater power supply than the 3V3 pin; otherwise (!radio.available()).

## Automated Timer Relay with Display of Current Date



# Important Notes:
When using arrays to publish to ROS, you must specify the length of the array. <br>
ex) <std_msgs::Int16MultiArray.h> <br>
std_msgs::Int16MultiArray array; <br>
array.data = values; <br>
array.data_length = size; <br>

I used a custom message that used int16[] 'name' therefore, the length component is 'name'_length (See [line](https://github.com/DreVinciCode/Arduino-Projects/blob/185e4d3f077a6208feb96d9a88b89362341413d1/ROS/customMessageROS/customMessageROS.ino#L34))
