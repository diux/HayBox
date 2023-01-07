#ifndef _MODES_STEAMSETUP_HPP
#define _MODES_STEAMSETUP_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class SteamSetup : public ControllerMode {
  public:
    SteamSetup(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
