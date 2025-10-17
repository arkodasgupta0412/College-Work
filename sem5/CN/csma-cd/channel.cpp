#include "channel.h"

Channel::Channel()
    : busy(false),
      // busy_delay(0),
      // finish_delay(0),
      Tp(1),
      bandwidth(100),
      current_station_id()
{
}

Channel::Channel(int bandwidth_bytes_per_slot, int propagation_delay_slots)
    : busy(false),
      // busy_delay(0),
      // finish_delay(0),
      Tp(propagation_delay_slots),
      bandwidth(bandwidth_bytes_per_slot),
      current_station_id()
{
}
