#include "modes/extra/HollowKnight.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

HollowKnight::HollowKnight(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::mod_x  },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };
}

void HollowKnight::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {

    outputs.x = inputs.a || inputs.c_up || inputs.c_left || inputs.c_right || inputs.c_down; // Attack
    outputs.b = inputs.b; // Cancel
    outputs.a = inputs.x; // Jump
    outputs.y = inputs.mod_y; // Spell
    
    outputs.triggerLDigital = inputs.lightshield; // Focus/cast
    outputs.triggerRDigital = inputs.mod_x;

    //outputs.buttonR = inputs.up; // Dream nail // This is not Dream nail
    outputs.buttonR = inputs.z; // Dash

    outputs.buttonL = inputs.r; // Map
    outputs.select = inputs.midshield; // Inventory
    outputs.start = inputs.start; // Pause
}

void HollowKnight::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        (inputs.left || inputs.c_left) && !inputs.c_right,
        (inputs.right || inputs.c_right) && !inputs.c_left,
        (inputs.down || inputs.c_down) && !inputs.c_up,
        (inputs.up || inputs.c_up) && !inputs.c_down,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
