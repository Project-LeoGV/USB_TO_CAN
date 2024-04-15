import serial


com = "/dev/ttyACM0"  # Linux
# com = "com" + input()               # Windows
ser = serial.Serial(port=com, baudrate=115200)

"""
Function calling sequence for configuration:
1- Get_Axis_id()
2- Motor_Calibration(axis_id) -> u should hear a beeb sound
2.1 - Get_Error(axis_id) - u should get 0 errors
3- Encoder_offset_calibration(axis_id) -> motor should rotate in both directions
3.1 -Get_Error(axis_id) - u should get 0 errors
4- Save_conficuration(axis_id)
5- Reboot(axis_id)
6- Closed_loop_control(axis_id) -> try to rotate the motor -> motor will try to stay at its original position
--------------------------------------
Controlling position:
Control_input_position(axis_id) -> motor should move 1 rotation

--------------------------------------
Controlling velocity:
Control_input_velocity(axis_id) -> 1 rotation per second

--------------------------------------
Set the motor idle:
Motor_Idle(axis_id) ->  motor will move freely

"""


def Get_Axis_id():
    """
    By default, an unconfigured ODrive starts with node_id = 0x3f, which represents an unaddressed state.
    In this state the ODrive does not send any cyclic messages (heartbeats, feedback, …).
    Send (node_id = 0x3f, cmd_id = 0x06, RTR=1).
    All ODrives that are already addressed (node_id != 0x3f) will respond immediately with their serial number and node_id
    """
    can_id = (0x3F << 5) | 0x06
    msg = str(hex(can_id))[2:] + "1000000000\n"
    ser.write(msg.encode("ascii"))


def Motor_Calibration(axis_id):
    can_id = (axis_id << 5) | 0x007
    # msg_id-> 3bit + rtr = 0 + dlc = 4 + data -> byte 1 = 4
    msg = str(hex(can_id))[2:] + "0440000000\n"
    ser.write(msg.encode("ascii"))


def Encoder_offset_calibration(axis_id):
    can_id = (axis_id << 5) | 0x007
    # msg_id-> 3bit + rtr = 0 + dlc = 4 + data -> byte 1 = 7
    msg = str(hex(can_id))[2:] + "0470000000\n"
    ser.write(msg.encode("ascii"))


def Closed_loop_control(axis_id):
    can_id = (axis_id << 5) | 0x007
    # msg_id-> 3bit + rtr = 0 + dlc = 4 + data -> byte 1 = 8
    msg = str(hex(can_id))[2:] + "0480000000\n"
    ser.write(msg.encode("ascii"))


def Reboot(axis_id):
    can_id = (axis_id << 5) | 0x016
    msg = str(hex(can_id))[2:] + "0000000000\n"
    ser.write(msg.encode("ascii"))


# not sure whether this function will behave as expected or not
def Save_conficuration(axis_id):
    can_id = (axis_id << 5) | 0x016
    msg = str(hex(can_id))[2:] + "0100000000\n"
    ser.write(msg.encode("ascii"))


# not sure whether this function will behave as expected or not
def Erase_conficuration(axis_id):
    can_id = (axis_id << 5) | 0x016
    msg = str(hex(can_id))[2:] + "0200000000\n"
    ser.write(msg.encode("ascii"))


def Get_Error(axis_id):
    can_id = (axis_id << 5) | 0x003
    msg = str(hex(can_id))[2:] + "1000000000\n"
    ser.write(msg.encode("ascii"))


def Control_input_position(axis_id):
    can_id = (axis_id << 5) | 0x00C
    msg = str(hex(can_id))[2:] + "0810000000\n"
    ser.write(msg.encode("ascii"))


def Control_input_velocity(axis_id):
    can_id = (axis_id << 5) | 0x00D
    msg = str(hex(can_id))[2:] + "0810000000\n"
    ser.write(msg.encode("ascii"))


def Motor_Idle(axis_id):
    can_id = (axis_id << 5) | 0x007
    msg = str(hex(can_id))[2:] + "0410000000\n"
    ser.write(msg.encode("ascii"))
