#ifndef _ROS_sensar_ros_SingleColorLED_h
#define _ROS_sensar_ros_SingleColorLED_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/ColorRGBA.h"

namespace sensar_ros
{

  class SingleColorLED : public ros::Msg
  {
    public:
      typedef std_msgs::ColorRGBA _color_type;
      _color_type color;
      typedef float _duration_type;
      _duration_type duration;
      uint32_t leds_length;
      typedef int16_t _leds_type;
      _leds_type st_leds;
      _leds_type * leds;
      typedef bool _repeating_type;
      _repeating_type repeating;

    SingleColorLED():
      color(),
      duration(0),
      leds_length(0), st_leds(), leds(nullptr),
      repeating(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->color.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->duration);
      *(outbuffer + offset + 0) = (this->leds_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->leds_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->leds_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->leds_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->leds_length);
      for( uint32_t i = 0; i < leds_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_ledsi;
      u_ledsi.real = this->leds[i];
      *(outbuffer + offset + 0) = (u_ledsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ledsi.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->leds[i]);
      }
      union {
        bool real;
        uint8_t base;
      } u_repeating;
      u_repeating.real = this->repeating;
      *(outbuffer + offset + 0) = (u_repeating.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->repeating);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->color.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->duration));
      uint32_t leds_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      leds_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      leds_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      leds_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->leds_length);
      if(leds_lengthT > leds_length)
        this->leds = (int16_t*)realloc(this->leds, leds_lengthT * sizeof(int16_t));
      leds_length = leds_lengthT;
      for( uint32_t i = 0; i < leds_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_st_leds;
      u_st_leds.base = 0;
      u_st_leds.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_leds.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_leds = u_st_leds.real;
      offset += sizeof(this->st_leds);
        memcpy( &(this->leds[i]), &(this->st_leds), sizeof(int16_t));
      }
      union {
        bool real;
        uint8_t base;
      } u_repeating;
      u_repeating.base = 0;
      u_repeating.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->repeating = u_repeating.real;
      offset += sizeof(this->repeating);
     return offset;
    }

    virtual const char * getType() override { return "sensar_ros/SingleColorLED"; };
    virtual const char * getMD5() override { return "f74bbd685df67536dfc23035828fb700"; };

  };

}
#endif
