
from matplotlib import pyplot as plt
import numpy as np


digit_positions=[[(0,1),(0,2)],[(0,2),(1,2)],[(1,2),(1,1)],[(1,1),(0,1)],[(0,1),(0,0)],[(0,0),(1,0)],[(1,0),(1,1)]]

digitArray=[
    [1,1,1,0,1,1,1],
    [0,0,1,0,0,0,1],
    [0,1,1,1,1,1,0],
    [0,1,1,1,0,1,1],
    [1,0,1,1,0,0,1],
    [1,1,0,1,0,1,1],
    [1,1,0,1,1,1,1],
    [0,1,1,0,0,0,1],
    [1,1,1,1,1,1,1],
    [1,1,1,1,0,1,1],
    [1,1,1,1,1,0,1],
    [1,0,0,1,1,1,1],
    [1,1,0,0,1,1,0],
    [0,0,1,1,1,1,1],
    [1,1,0,1,1,1,0],
    [1,1,0,1,1,0,0]
]

digitMap={
    '0':0,
    '1':1,
    '2':2,
    '3':3,
    '4':4,
    '5':5,
    '6':6,
    '7':7,
    '8':8,
    '9':9,
    'A':10,
    'B':11,
    'C':12,
    'D':13,
    'E':14,
    'F':15
}




def draw_digit(digit,offset):
    for i,(s,e) in enumerate(digit_positions):
        print(s,e)
        if(digitArray[digitMap[digit]][i]):
            plt.plot((s[0]+offset[0],e[0]+offset[0]),(s[1]+offset[1],e[1]+offset[1]),"r")


def formatSegmentMap():
    str="int segments[]={"
    for d in digitArray:
        for s in d:
            str+="1" if s else "0"
            str+=','
        str+="               \n"
    str+="};"
    return str
seg_size=4
digitOffset=[
    0,7*seg_size,14*seg_size+2,21*seg_size+2
]
dotsOffset=[14*seg_size,14*seg_size+1]
def formatDigitMap():
    segmentMapString="int segmentMap[]={"
    digitMapString="int digitMap[]={"
    segmentMap=np.zeros(114)
    digitMap=np.zeros(114)
    for d,offset in enumerate(digitOffset):
        for i in range(0,7):
            for n in range(seg_size):
                segmentMap[offset+i*seg_size+n]=i
                digitMap[offset+i*seg_size+n]=d
    segmentMap[dotsOffset[0]]=7
    segmentMap[dotsOffset[1]]=7

    digitMap[dotsOffset[0]]=5
    digitMap[dotsOffset[1]]=5
    for i,s in enumerate(segmentMap):
        segmentMapString+="%d"%s
        segmentMapString+=","
        if(i%7==0):
            segmentMapString+="\n"

    for i,s in enumerate(digitMap):
        digitMapString+="%d"%s
        digitMapString+=","
        if(i%7==0):
            digitMapString+="\n"

    segmentMapString+="};"
    digitMapString+="};"
    return segmentMapString,digitMapString


plt.gca().set_aspect("equal")

for i,d in enumerate(digitMap.keys()):
    draw_digit(d,(i*1.5,0))

plt.show()
print(formatSegmentMap())
for s in formatDigitMap():
    print(s)