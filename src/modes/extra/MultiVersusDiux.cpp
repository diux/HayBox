#include "modes/extra/MultiVersusDiux.hpp"

#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

#define DPAD_BUTTON_ON(x) inputs.nunchuk_c ? x : false
#define DPAD_BUTTON_OFF(x) inputs.nunchuk_c ? false : x

// My modification of Multiversus for LBX controller with a dpad toggle button
MultiVersusDiux::MultiVersusDiux(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };
}

void MultiVersusDiux::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {

    // Attack
    outputs.a = inputs.a;

    // Special
    outputs.b = inputs.b;

    // Bind X and Y to "jump" in-game.
    outputs.x = inputs.x;
    outputs.y = inputs.y;

    outputs.start = DPAD_BUTTON_OFF(inputs.start);
    outputs.select = DPAD_BUTTON_ON(inputs.start);

    // Home not supported by GameCube adapter.
    outputs.home = inputs.home;

    outputs.triggerLDigital = inputs.l;
    outputs.triggerRDigital = inputs.r;

    // Bind A to "attack" in-game.
    outputs.a = inputs.a;

    // Bind B to "special" in-game.
    outputs.b = inputs.b;

    // Z = RB. Bind to "dodge" in-game.
    outputs.buttonR = inputs.z;

    // LS = LB. Not supported by GameCube adapter.
    outputs.buttonL = inputs.lightshield;


    // MX activates a layer for "neutral" binds. Uses D-Pad buttons.
#ifdef USE_DPAD_TOGGLE
    if (inputs.nunchuk_c && !inputs.mod_y) {
#else
    if (inputs.mod_x && !inputs.mod_y) {
#endif
        // MX + A = D-Pad Left. Bind to "neutral attack" in-game.
        outputs.dpadLeft = inputs.a;

        // MX + B = D-Pad Right. Bind to "neutral special" in-game.
        outputs.dpadRight = inputs.b;

        // MX + Z = D-Pad Down. Bind to "neutral evade" in-game.
        outputs.dpadDown = inputs.z;

        // MX + LS = D-Pad Up. Bind to "taunt 1" in-game.
        outputs.dpadUp = inputs.lightshield;
    }

    // MY activates C-Stick to D-Pad conversion.
    if (inputs.mod_y && !inputs.mod_x) {
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadUp = inputs.c_up;
    }
}

void MultiVersusDiux::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
#ifdef USE_DPAD_TOGGLE
        inputs.up || inputs.mod_x,
#else
        inputs.up,
#endif
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

#ifdef USE_DPAD_TOGGLE
        if (inputs.mod_y && !inputs.nunchuk_c) {
#else
        if (inputs.mod_y && !inputs.mod_x) {
#endif
        // MY slows down the cursor for easier menu navigation.
        // Menu cursor speed can also be turned down in-game under "Interface" settings.
        // 128 ± 76 results in the slowest cursor that still actuates directional inputs in-game.
        outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * 76;
        outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 76;

        if (directions.diagonal) {
            // Maintain a consistent cursor velocity when MY is held.
            // ⌊76 × √2/2⌋ = 53
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * 53;
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 53;
        }

        // Also shut off C-Stick for D-Pad conversion.
        outputs.rightStickX = ANALOG_STICK_NEUTRAL;
        outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
