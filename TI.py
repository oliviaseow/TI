# watches folder TI and connected to Arduino via serial

import serial
import sys
import time
import logging
from watchdog.observers import Observer
from watchdog.events import LoggingEventHandler
import os

# open serial port

arduino = serial.Serial(
		port='/dev/cu.usbserial-AH0103EA',
		baudrate=9600,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS
)

def on_created(event):
	print(f"{event.src_path} has been created with size {os.path.getsize(event.src_path)}!")
	arduino.write(os.path.getsize(event.src_path))

while True:
	#if arduino.readline() == 'READY':
	logging.basicConfig(level=logging.INFO,
						format='%(asctime)s - %(message)s',
						datefmt='%Y-%m-%d %H:%M:%S')
	path = "/Users/osw/Desktop/TI/flower"
	event_handler = LoggingEventHandler()
	event_handler.on_created = on_created
	observer = Observer()
	observer.schedule(event_handler, path, recursive=True)
	observer.start()
	try:
		while True:
			time.sleep(1)
	except KeyboardInterrupt:
		observer.stop()
	observer.join()

arduino.close()

# send handshake byte to arduino

# enter loop watching TI folder

# when file appears in folder, python looks for filesize (and total directory size)

# python sends rotation amount to arduino

# arduino rotates

# on receiving delete byte

# delete contents of folder

# send byte to arduino to retract