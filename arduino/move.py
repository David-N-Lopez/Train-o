import serial

ser = serial.Serial('/dev/cu.usbmodem141201')

line = input()
while line:
  ser.write(bytes(line, encoding='utf-8'))
  line = input()
