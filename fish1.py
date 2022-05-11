from tkinter import *
from time import *

progs = {'example': [3, 2, [['v', ';'],
                    ['0', 'n'],
                    ['\\', '/']
                    ]], 
         'Fibonacci': [4, 9, [['0', 'n', '"', ' ', '"', 'c', '1', '\\', ' '], 
                    ['/', '0', 'c', '"', ' ', '"', 'n', '/', ' '],
                    ['\\', '1', '>', ':', '@', '@', '+', ':', '\\'],
                    [' ', ' ', '\\', 'c', '"', ' ', '"', 'n', '/']
                    ]]
         }
#h, w, grid[h][w]
errormsg = 'something smells fishy...'

def run(progname, delay=0.2, inpt=""):
    if not progname in progs:
        print('Invalid key')
        return 0
    inp = inpt
    prog = progs[progname]
    h = prog[0]
    w = prog[1]
    grid = prog[2].copy()
    window = Tk()
    canvas = Canvas(window, height = h*12+6, width = w*12+6)
    window.title('><>++')
    canvas.pack()
    (ipx, ipy, dirx, diry) = (0, 0, 0, 1)
    (snum, curn, sstr) = (0, 0, 0)
    stacks = [[]]
    while True:
        canvas.delete(ALL)
        canvas.create_rectangle(3,3,w*12+8, h*12+8)
        for i in range (0, h):
            for j in range (0, w):
                canvas.create_text(12*j+12, 12*i+12, text=grid[i][j])
        canvas.create_rectangle(12*ipy+6, 12*ipx+6, 12*ipy+18, 12*ipx+18)
        window.update()
        sleep(delay)
        moved = 0
        if snum == 1:
            if grid[ipx][ipy] in '0123456789':
                curn = 10*curn + int(grid[ipx][ipy])
                ipx = (ipx+dirx) % h
                ipy = (ipy+diry) % w
                moved = 1
            else:
                stacks[-1].append(curn)
                snum = 0
        if sstr == 1:
            if grid[ipx][ipy] == '"':
                sstr = 0
            else:
                stacks[-1].append(ord(grid[ipx][ipy]))
            ipx = (ipx+dirx) % h
            ipy = (ipy+diry) % w
            moved = 1
        if moved == 1:
            continue
        #execute current character
        c = grid[ipx][ipy]
        if c == '>':
            (dirx, diry) = (0, 1)
        elif c == '<':
            (dirx, diry) = (0, -1)
        elif c == '^':
            (dirx, diry) = (-1, 0)
        elif c == 'v':
            (dirx, diry) = (1, 0)
        elif c == '\\':
            (dirx, diry) = (diry, dirx)
        elif c == '/':
            (dirx, diry) = (-diry, -dirx)
        elif c == '!':
            ipx = (ipx+dirx)%h
            ipy = (ipy+diry)%w
        elif c == '?':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            t = stacks[-1].pop()
            if t != 0:
                ipx = (ipx+dirx)%h
                ipy = (ipy+diry)%w
        elif c in '0123456789':
            stacks[-1].append(int(c))
        elif c == "'":
            snum = 1
        elif c == '"':
            sstr = 1
        elif c in '+-*,%=)(':
            if len(stacks[-1]) <= 1:
                print(errormsg)
                return
            if c == '+':
                stacks[-1][-1] = stacks[-1][-2] + stacks[-1].pop()
            elif c == '-':
                stacks[-1][-1] = stacks[-1][-2] - stacks[-1].pop()
            elif c == '*':
                stacks[-1][-1] = stacks[-1][-2] * stacks[-1].pop()
            elif c == ',':
                stacks[-1][-1] = stacks[-1][-2] // stacks[-1].pop()
            elif c == '%':
                stacks[-1][-1] = stacks[-1][-2] % stacks[-1].pop()
            elif c == '=':
                stacks[-1][-1] = int(stacks[-1][-2] == stacks[-1].pop())
            elif c == ')':
                stacks[-1][-1] = int(stacks[-1][-2] > stacks[-1].pop())
            elif c == '(':
                stacks[-1][-1] = int(stacks[-1][-2] < stacks[-1].pop())
        elif c == ':':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            stacks[-1].append(stacks[-1][-1])
        elif c == '~':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            stacks[-1].pop()
        elif c == '$':
            if len(stacks[-1]) <= 1:
                print(errormsg)
                return
            t = stacks[-1][-2]
            stacks[-1][-2] = stacks[-1][-1]
            stacks[-1][-1] = t
        elif c == '@':
            if len(stacks[-1]) <= 2:
                print(errormsg)
                return
            t = stacks[-1][-1] 
            stacks[-1][-1] = stacks[-1][-2]
            stacks[-1][-2] = stacks[-1][-3]
            stacks[-1][-3] = t
        elif c == 'r':
            stacks[-1].reverse()
        elif c == 'l':
            stacks[-1].append(len(stacks[-1]))
        elif c == '[':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            if len(stacks[-1]) <= stacks[-1][-1]:
                print(errormsg)
                return
            nstacksize = stacks[-1].pop()
            nstack = []
            for i in range(nstacksize):
                nstack.append(stacks[-1].pop())
            nstack.reverse()
            stacks.append(nstack)
        elif c == ']':
            if len(stacks) == 1:
                stacks[0] = []
            else:
                stacks[-1] = stacks[-2] + stacks.pop()
        elif c == 'c':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            print(chr(stacks[-1].pop()), end='')
        elif c == 'n':
            if len(stacks[-1]) == 0:
                print(errormsg)
                return
            print(stacks[-1].pop(), end='')
        elif c == 'i':
            if len(inp) == 0:
                stacks[-1].append(-1)
            else:
                stacks[-1].append(ord(inp[0]))
                inp = inp[1:]
        elif c == ';':
            return
        ipx = (ipx+dirx)%h
        ipy = (ipy+diry)%w

def new_prog(h, w, delay=0.2):
    grid = []
    for i in range (h):
        grid.append([])
        for j in range (w):
            grid[i].append(' ')
    (curx, cury) = (0,0)
    window = Tk()
    canvas = Canvas(window, height = h*12+6, width = w*12+6)
    window.title('><>++')
    canvas.pack()
    def f(event):
        nonlocal curx, cury, grid
        k = event.keysym
        if k == 't':
            g = []
            for i in range (h):
                s = ''
                for j in range (w):
                    s += grid[i][j]
                g.append(s)
            print([h, w, g])
        elif k == 'Up':
            curx -= 1
        elif k == 'Left':
            cury -= 1
        elif k == 'Down':
            curx += 1
        elif k == 'Right':
            cury += 1
        elif k == 'x':
            print('Edit to: ', end='')
            grid[curx][cury] = input()
        curx = curx % h
        cury = cury % w
    canvas.bind_all("<Key>", f)
    canvas.pack()
    while True:
        canvas.delete(ALL)
        canvas.create_rectangle(3,3,w*12+8, h*12+8)
        for i in range (0, h):
            for j in range (0, w):
                canvas.create_text(12*j+12, 12*i+12, text=grid[i][j])
        canvas.create_rectangle(12*cury+6, 12*curx+6, 12*cury+18, 12*curx+18)
        window.update()
        sleep(delay)
