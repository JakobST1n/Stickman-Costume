/* This script is made for a LED-stickman-costume
 * Author(s): JakobST1n
 * These are the currently implemented modes
 *  0 - Static
 *  1 - Slow Strobe
 *  2   Medium Strobe
 *  3   Fast Strobe
 */
#define OUT_PWM 1           // The LED-strip is connected to PB1
#define IN_MODE 4           // Pressing this increments 'mode' by one
#define IN_ADJ  3           // This button adjusts the brightness

int CMode          = 2;     // This is just the current mode
int ExistingModes  = 4;     // This is the number of modes that are implemented
// Used for saving button state
bool IN_ADJ_STATE  = false; //
bool IN_MODE_STATE = false; //
// These are for the general pwm-frequency (not all modes care)
int CBrightness    = 255;    // The brightness of the strip, between '0' and '255'
int CDimDirection  = 0;     // Used to know if the brightness should be increasing or decreasing based on the button press
// These are used by the strobe-effect
int CStrobeRevs    = 0;     // A running counter for the strobe-light
int StrobeState    = 0;     // '0' or '1' for saving the state of the output
int StrobeSlowFreq = 70;
int StrobeMedFreq  = 30;
int StrobeFastFreq = 5;


void setup() {
    pinMode(OUT_PWM, OUTPUT);
    pinMode(IN_ADJ, INPUT);
    pinMode(IN_MODE, INPUT);
}

/* loop
 *
 * it takes aprox. ?ms to run through the loop once, whitout changing pwm freq
 */
void loop() {
    delay(1);

    // If 'mode-button' is pressed, increment mode, reset mode if last mode reaced
    if ( (digitalRead(IN_MODE) == HIGH) && (IN_MODE_STATE == false) ) {
        CMode++;
        if (CMode >= ExistingModes) {
            CMode = 0;
        }
    }
    // If 'Adjust-button' is pressed
    if (digitalRead(IN_ADJ) == HIGH) {
        if (CDimDirection == 1) { CBrightness++; }
        if (CDimDirection == 0) { CBrightness--; }
        if (CBrightness >= 255) { CDimDirection = 0; }
        if (CBrightness <= 0)   { CDimDirection = 1; }
    }

    // Do animation-things
    switch (CMode) {
        case 0:  // Static
            analogWrite(OUT_PWM, CBrightness);
            break;

        case 1:  // Slow Strobe
            CStrobeRevs++;
            if (CStrobeRevs >= StrobeSlowFreq) {
                CStrobeRevs = 0;
                strobe();
            }
            break;

        case 2:  // Slow Strobe
            CStrobeRevs++;
            if (CStrobeRevs >= StrobeMedFreq) {
                CStrobeRevs = 0;
                strobe();
            }
            break;

        case 3:  // Slow Strobe
            CStrobeRevs++;
            if (CStrobeRevs >= StrobeFastFreq) {
                CStrobeRevs = 0;
                strobe();
            }
            break;

        default: // Default to mode zero
            CMode = 0;
            break;
    }

    IN_MODE_STATE = digitalRead(IN_MODE);
}

void setOutPwm(int brightness) {
    analogWrite(OUT_PWM, brightness);
}

void strobe() {
    if (StrobeState == 1) {
        StrobeState = 0;
        setOutPwm(0);
    } else if (StrobeState == 0) {
        StrobeState = 1;
        setOutPwm(CBrightness);
    }
}
