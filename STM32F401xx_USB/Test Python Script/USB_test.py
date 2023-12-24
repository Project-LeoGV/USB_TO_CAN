import serial

if __name__ == "__main__":
    print("Welcome To USB")
    print("Enter The number of The port")
    #com = "/dev/ttyUSB" + input()
    com = "com" + input()

    ser = serial.Serial(port=com, baudrate=115200)

    while True:
        ################ Send Example ################
        #value = input()
        #ser.write(value.encode('ascii'))
        
        ############## Receive Example ###############
        print(ser.readline().decode())