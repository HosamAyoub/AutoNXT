import urllib.request
import os
import serial

APP_URL = "https://raw.githubusercontent.com/HosamAyoub/AutoNXT/Hesham/APP/Hexa.hex"
VER_URL = "https://raw.githubusercontent.com/HosamAyoub/AutoNXT/Hesham/APP/VER.txt"

NEW_APP_Name = "Hexa_New.hex"
NEW_VER_Name = "Version_New.txt"

CUR_VER_NAME = "Version.txt"
CUR_APP_NAME = "Hexa.hex"



Baud = 115200
UART = serial.Serial(baudrate = Baud , port = "/dev/serial0" , parity="N" , stopbits = 1)

if (UART.is_open):
    print ("Successfully")
    Read1 = UART.read()
    while (Read1.hex() == 'ff'):
        Read1 = UART.read()
    Read = Read1.decode()
    print(Read)
    if (Read == 'Q'):
        if (os.path.isfile(CUR_APP_NAME) and os.path.isfile(CUR_APP_NAME)):
            urllib.request.urlretrieve(APP_URL , NEW_APP_Name)
            urllib.request.urlretrieve(VER_URL , NEW_VER_Name)



            NEW_VER = open(NEW_VER_Name , mode='r')
            CUR_VER = open(CUR_VER_NAME , mode='r')

            NEW_VER_No = NEW_VER.readline()
            CUR_VER_No = CUR_VER.readline()


            NEW_VER.close()
            CUR_VER.close()


            if (NEW_VER_No == CUR_VER_No):
                os.remove(NEW_VER_Name)
                os.remove(NEW_APP_Name)
                UART.write("N".encode())
                print("No Newer Version")
            else:
                os.remove(CUR_VER_NAME)
                os.remove(CUR_APP_NAME)
                os.rename(src=NEW_VER_Name , dst=CUR_VER_NAME)
                os.rename(src=NEW_APP_Name , dst=CUR_APP_NAME)
                UART.write('R'.encode())
                FileHex = open(file="Hexa.hex" , mode="r")
                print(UART.read())
                for Line in FileHex:
                    for letter in Line:
                        UART.write(letter.encode())
                    Read = UART.read().decode()
                    print(Read)
                UART.close()
        else:
            urllib.request.urlretrieve(APP_URL , CUR_APP_NAME)
            urllib.request.urlretrieve(VER_URL , CUR_VER_NAME)
            FileHex = open(file="Hexa.hex" , mode="r")
            UART.write('R'.encode())
            print(UART.read())
            for Line in FileHex:
                for letter in Line:
                    UART.write(letter.encode())
                Read = UART.read().decode()
                print(Read)
            UART.close()

else:
    print ("NOK")