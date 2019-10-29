# watches folder TI and connected to Arduino via serial

import serial
import sys
import time
from watchdog.observers import Observer
from watchdog.events import LoggingEventHandler
import os
import platform
import glob


class Flower:
    arduino = serial.Serial()
    observer = Observer()

    # constructor
    def __init__(self):
        self.arduino = self.serial_init()
        self.handler_init()


    def serial_init(self):
        # Set OS dependant variables
        PLATFORM = platform.system()
        if "Darwin" in PLATFORM:
            PORT_PATTERN = "/dev/cu.usb*"
        elif "Linux" in PLATFORM:
            PORT_PATTERN = "/dev/ttyUSB*"
        else:
            print("Error: platform not yet supported")
            sys.exit(-1)

        # Open serial port
        devices = glob.glob(PORT_PATTERN)
        print("devices: ", devices)
        self.arduino = serial.Serial(devices[0], 115200)
        while not self.arduino.isOpen():
            print("Arduino not connected? devices[0]: " + devices[0])
            time.sleep(0.5)
        return self.arduino


    # Handler to check for new files
    def on_created(self, event):
        message = bytes([int(os.path.getsize(event.src_path) / 1024)])
        print(f"{event.src_path} has been created with size {os.path.getsize(event.src_path)/1024} KB")
        self.arduino.write(message)
        # write(b'123456');

    # Sets functin to call when new files are created
    def handler_init(self):
        path = "./flower/"
        event_handler = LoggingEventHandler()
        event_handler.on_created = self.on_created
        self.observer.schedule(event_handler, path, recursive=True)
        self.observer.start()


    # Wait for event, or keyboard interrupt
    def loop(self):
        while True:
            time.sleep(0.1)
            received = ""
            try:
                received = self.arduino.readline()
                print(received)
                if (b'!' in received):
                    os.system("rm ./flower/*.jpg")
                    print("DATA DELETED")
            except:
                print("error: ", received)



    # desctuctor
    def __del__(self):
        self.arduino.close()
        self.observer.stop()


###############################################################################
if __name__ == "__main__":
    flower = Flower()
    flower.loop()

# send handshake byte to arduino

# enter loop watching TI folder

# when file appears in folder, python looks for filesize (and total directory size)

# python sends rotation amount to arduino

# arduino rotates

# on receiving delete byte

# delete contents of folder

# send byte to arduino to retract

