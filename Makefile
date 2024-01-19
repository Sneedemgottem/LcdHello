TTY=/dev/cu.usbmodem1101
FQBN=arduino:avr:uno
SRC=.

compile:
	arduino-cli compile --fqbn $(FQBN) $(SRC)

upload:
	arduino-cli upload -p $(TTY) --fqbn $(FQBN) $(SRC)
