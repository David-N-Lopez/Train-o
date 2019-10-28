from tkinter import *

import serial


root = Tk()

ser = serial.Serial('COM10',9600)


def on_press(key):

    if key == 'up':

        ser.write(b'mov 0 1\n')

    elif key == 'down':

        send_cmd(b'mov 500 -1')

    elif key == 'left':

        send_cmd('turn 20 -1')

    elif key == 'right':

        send_cmd('turn 20 1')

    elif key == 't':

        send_cmd('serve')

    elif key == ' ':

        send_cmd('stop')


def send_cmd(cmd):

    ser.write(bytes(cmd, encoding='utf-8'))

    print(cmd)




def left(event):

    on_press('left')


def right(event):

    on_press('right')


def up(event):

    on_press('up')


def down(event):

    on_press('down')


def space(event):

    on_press(' ')


def dispense(event):

    on_press('t')



frame = Frame(root, width=100, height=100)

frame.bind("<Left>", left)

frame.bind("<Right>", right)

frame.bind("<Up>", up)

frame.bind("<Down>", down)

frame.bind("<space>", space)

frame.bind("<t>", dispense)

frame.focus_set()

frame.pack()


root.mainloop()
