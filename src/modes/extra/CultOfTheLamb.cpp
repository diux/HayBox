#include "modes/extra/CultOfTheLamb.hpp"

#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255
#define DPAD_BUTTON_ON(x) (inputs.nunchuk_c ? x : false)
#define DPAD_BUTTON_OFF(x) (inputs.nunchuk_c ? false : x)

CultOfTheLamb::CultOfTheLamb(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };
}

void CultOfTheLamb::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    
    outputs.start = DPAD_BUTTON_OFF(inputs.start);
    outputs.select = DPAD_BUTTON_ON(inputs.start);
    //outputs.home = inputs.z;

    outputs.a = inputs.y;
    outputs.b = inputs.z;
    outputs.x = inputs.a;
    outputs.y = inputs.b;

    outputs.triggerRDigital = inputs.lightshield; //LB
    outputs.triggerLDigital = inputs.midshield; //RB
    outputs.buttonL = inputs.l;
    outputs.buttonR = inputs.r;

    outputs.leftStickClick = DPAD_BUTTON_ON(inputs.mod_x);
    outputs.rightStickClick = DPAD_BUTTON_ON(inputs.mod_y);

    outputs.dpadUp = DPAD_BUTTON_ON(inputs.up);
    outputs.dpadDown = DPAD_BUTTON_ON(inputs.down);
    outputs.dpadLeft = DPAD_BUTTON_ON(inputs.left);
    outputs.dpadRight = DPAD_BUTTON_ON(inputs.right);
}

void CultOfTheLamb::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        DPAD_BUTTON_OFF(inputs.left), //left
        DPAD_BUTTON_OFF(inputs.right), //right
        DPAD_BUTTON_OFF(inputs.down), //down
        DPAD_BUTTON_OFF(inputs.up || inputs.mod_x), //up
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
