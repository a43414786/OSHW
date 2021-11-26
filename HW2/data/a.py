'''with open("key.txt","r") as f:
    keys = f.readlines()
with open("value.txt","r") as f:
    values = f.readlines()

for i in keys:
    print(i)'''

import numpy as np

keys = []

for j in range(30):
    length = np.random.randint(0,100)
    string = ""
    for i in range(length):
        a = np.random.randint(0,62)
        if a == 0:
            string = string+"a"  
        elif a == 1:
            string = string+"b"
        elif a == 2:
            string = string+"c"
        elif a == 3:
            string = string+"d"
        elif a == 4:
            string = string+"e"
        elif a == 5:
            string = string+"f"
        elif a == 6:
            string = string+"g"
        elif a == 7:
            string = string+"h"
        elif a == 8:
            string = string+"i"
        elif a == 9:
            string = string+"j"
        elif a == 10:
            string = string+"k"
        elif a == 11:
            string = string+"l"  
        elif a == 12:
            string = string+"m"
        elif a == 13:
            string = string+"n"
        elif a == 14:
            string = string+"o"
        elif a == 15:
            string = string+"p"
        elif a == 16:
            string = string+"q"
        elif a == 17:
            string = string+"r"
        elif a == 18:
            string = string+"s"
        elif a == 19:
            string = string+"t"
        elif a == 20:
            string = string+"u"
        elif a == 21:
            string = string+"v"
        elif a == 22:
            string = string+"w"  
        elif a == 23:
            string = string+"x"
        elif a == 24:
            string = string+"y"
        elif a == 25:
            string = string+"z"
        elif a == 26:
            string = string+"A"  
        elif a == 27:
            string = string+"B"
        elif a == 28:
            string = string+"C"
        elif a == 29:
            string = string+"D"
        elif a == 30:
            string = string+"E"
        elif a == 31:
            string = string+"F"
        elif a == 32:
            string = string+"G"
        elif a == 33:
            string = string+"H"
        elif a == 34:
            string = string+"I"
        elif a == 35:
            string = string+"J"
        elif a == 36:
            string = string+"K"
        elif a == 37:
            string = string+"L"  
        elif a == 38:
            string = string+"M"
        elif a == 39:
            string = string+"N"
        elif a == 40:
            string = string+"O"
        elif a == 41:
            string = string+"P"
        elif a == 42:
            string = string+"Q"
        elif a == 43:
            string = string+"R"
        elif a == 44:
            string = string+"S"
        elif a == 45:
            string = string+"T"
        elif a == 46:
            string = string+"U"
        elif a == 47:
            string = string+"V"
        elif a == 48:
            string = string+"W"  
        elif a == 49:
            string = string+"X"
        elif a == 50:
            string = string+"Y"
        elif a == 51:
            string = string+"Z"
        elif a == 52:
            string = string+"0"
        elif a == 53:
            string = string+"1"
        elif a == 54:
            string = string+"2"
        elif a == 55:
            string = string+"3"
        elif a == 56:
            string = string+"4"
        elif a == 57:
            string = string+"5"
        elif a == 58:
            string = string+"6"
        elif a == 59:
            string = string+"7"
        elif a == 60:
            string = string+"8"
        elif a == 61:
            string = string+"9"
    keys.append(string+"\n")

print(keys)

with open("value.txt",'w') as f:
    f.writelines(keys)
