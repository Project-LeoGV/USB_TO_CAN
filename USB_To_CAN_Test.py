import serial

def sendCan():
    # Take input topic name and data,
    # and convert it to CAN message

    # Send it via USB
    # ser.write(value.encode('ascii'))
    print("Enter ID consists of three bits\n")
    ID   = input("ID: 0x")
    RTR  = input("RTR: ")
    DLC  = input("DLC: ")
    DATA =""
    for i in range(1,int(DLC)+1,1):
        Data = input("Data[{}]: ".format(i))
        DATA += Data

    msg = ID +RTR +DLC +DATA 
    msg = msg.ljust(13,'0') + '\n'
    print(msg)
    ser.write(msg.encode('ascii'))
    

def receiveCan():
    # Take can Message comes from USB,
    # and convert it to topic name and data

    # print it in the terminal
    # ser.readline().decode()
    msg = ser.readline().decode()
    print("********* Received CAN Message *********")
    print("ID = 0x" + msg[0:3])
    print("RTR = " + msg[3])
    print("DLC = " + msg[4])
    print("Data[8] = {" + msg[5], end="")
    for i in range(6, 13, 1):
        print(", " + msg[i], end="")
    print("}")

if __name__ == "__main__":
    print("Welcome To USB")
    print("Enter The number of The port")
    
    com = "/dev/ttyACM0"     # Linux
    #com = "com" + input()               # Windows

    ser = serial.Serial(port=com, baudrate=115200)

    while True:
        ##################### Send CAN Message (DownStream) #####################
        sendCan()
        
        ############# Receive Ack and message if required (UpStream) ############
        Ack = ser.readline().decode()
        if Ack == "1":
            continue
        elif Ack == "2":
            receiveCan()
