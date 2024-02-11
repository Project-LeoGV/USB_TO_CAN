import serial

def sendCan():
    # Take input topic name and data,
    # and convert it to CAN message

    # Send it via USB
    # ser.write(value.encode('ascii'))
    pass

def receiveCan():
    # Take can Message comes from USB,
    # and convert it to topic name and data

    # print it in the terminal
    # ser.readline().decode()
    pass

if __name__ == "__main__":
    print("Welcome To USB")
    print("Enter The number of The port")
    
    # com = "/dev/ttyUSB" + input()     # Linux
    com = "com" + input()               # Windows

    ser = serial.Serial(port=com, baudrate=115200)

    while True:
        ##################### Send CAN Message (DownStream) #####################
        value = input()
        sendCan()
        
        ############# Receive Ack and message if required (UpStream) ############
        Ack = ser.readline().decode()
        if Ack == "2":
            receiveCan()
