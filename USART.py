import serial



FileHex = open(file="Hexa.hex" , mode="r")

Baud = int (input("Enter Baud Rate : "))

UART = serial.Serial(baudrate = Baud , port = "COM8" , parity="N" , stopbits = 1)
if (UART.is_open):
    print ("Successfully")
    Read1 = UART.read()
    while (Read1.hex() == 'ff'):
        Read1 = UART.read()
    Read = Read1.decode()
    print(Read)
    if (Read == 'Q'):
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