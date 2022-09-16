#ifndef _MODES_CULTOFTHELAMB_HPP
#define _MODES_CULTOFTHELAMB_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class CultOfTheLamb : public ControllerMode {
  public:
    CultOfTheLamb(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
