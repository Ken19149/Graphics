import math
import pyperclip

s3 = math.sqrt(3)

transformX = 160
transformY = 125
scale = 100

copy = ""

stars = [[0,0,3/2,3*s3/2],[3/2,3*s3/2,3,0],[3,0,0,0],[0,s3,3,s3],[3,s3,3/2,-s3/2],[3/2,-s3/2,0,s3]]
for i in range(0,len(stars)):
    for j in range(0,4):
        stars[i][j] = round((stars[i][j]+(s3/2))*scale + transformX) if j%2==0 else round((stars[i][j]+(s3/2))*scale + transformY)
    print(f"line {stars[i][0]} {stars[i][1]} {stars[i][2]} {stars[i][3]}")
    copy += (f"line {stars[i][0]} {stars[i][1]} {stars[i][2]} {stars[i][3]}\n")

pyperclip.copy(copy)