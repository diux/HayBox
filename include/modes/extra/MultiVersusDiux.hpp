#ifndef _MODES_MULTIVERSUSDIUX_HPP
#define _MODES_MULTIVERSUSDIUX_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class MultiVersusDiux : public ControllerMode {
  public:
    MultiVersusDiux(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
