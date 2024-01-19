// all outputs
uint8_t RS = 13; // H: Data Signal, L: Instruction Signal
uint8_t RW = 12; // H: Read Mode, L: Write Mode
uint8_t E = 11; // Clock latch signal input

uint8_t dataPins[] = {9,8,7,6,5,4,3,2}; // From db0 to db7

#define FUNCTION_SET    0b00110000
#define DISPLAY_CONTROL 0b00001110
#define ENTRY_MODE      0b00000110
#define RETURN_HOME     0b00000010

// The LCD understand ascii characters. This function loops through every character and puts the ascii in binary on the data bus.
void printToLCD(char sentence[]) {
    digitalWrite(RS, HIGH);

    for (int i = 0; i < 8; i++) {
        writeData(sentence[i]);
    }

    digitalWrite(RS, LOW);
}

// puts data on the data bus
void writeData(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(dataPins[i], (data >> i) & 0x01); // Selects db0-7 and also shifts the bits and ands first bit so that only pin[i] is read
    }

    pulseClockLatch();
}

// When data is already on the db0-7 lines, as well as RS and RW, pulse the latch so the so the LCD processes the command
void pulseClockLatch() {
    // make sure the E latch is low
    digitalWrite(E, LOW);
    delayMicroseconds(1);

    digitalWrite(E, HIGH);
    delayMicroseconds(1); // TPW (E Pulse Width) has to be at least 450 ns.
    digitalWrite(E, LOW);

    delayMicroseconds(100); // Wait after command to settle so another one isn't written while busy
}

void setup() {
    delay(1000);

    pinMode(RS, OUTPUT);
    pinMode(RW, OUTPUT);
    pinMode(E, OUTPUT);
    digitalWrite(RW, LOW); // For writing hello world, RW will always be low

    for (int i = 0; i < 8; i++) {
        pinMode(dataPins[i], OUTPUT);
    }

}

void loop() {
    digitalWrite(RS, LOW);
    writeData(FUNCTION_SET); // 8 bit operation, 1 line display
    writeData(DISPLAY_CONTROL); // Display on, cursor appear
    writeData(ENTRY_MODE); // Increase address by one. Display has no shift
    printToLCD("Hello, World!");
    writeData(RETURN_HOME); // Display and cursor return to original position
}
