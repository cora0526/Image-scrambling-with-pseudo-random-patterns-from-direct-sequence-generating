import numpy as np
import pandas as pd
import cv2
import math
# 大小[1445][1701][3]

def axis_change (num,x):
    if num%(x-1) == 0:
        new_x = 0
    else: 
        new_x = num % x
    new_y = int(num / x)
    return new_x,new_y
path = "22m-seq.csv"
df = pd.read_csv(path)
df_col = df.columns
img_path = "R.jpg"
img = cv2.imread(img_path)
print(img.shape)

img_new = []
img_new_temp = []
img_new_temp.append([int(img[0][0][0]),int(img[0][0][1]),int(img[0][0][2])])
new_x,new_y = axis_change(int(df_col[0]),1701)
img_new_temp.append([int(img[new_y][new_x][0]),int(img[new_y][new_x][1]),int(img[new_y][new_x][2])])


index = 0
pass_num = 0 
while(1):
    if df['1048577'][index]>((1445*1701)-1):
        index+=1
        pass_num += 1
        continue
    new_x,new_y=axis_change(int(df['1048577'][index]),1701)
    img_new_temp.append([int(img[new_y][new_x][0]),int(img[new_y][new_x][1]),int(img[new_y][new_x][2])])
    index+=1
    if len(img_new_temp)==1701:
        break
img_new.append(img_new_temp)

for i in range(1,1445,1):
    img_new_temp = []
    # print(i)
    # print(len(img_new[i-1]))
    # print("-----------------------------")
    while(1):
        if index == 4194301:
            break
        if df['1048577'][index]>((1445*1701)-1):
            index +=1
            continue
        else:
            new_x,new_y=axis_change(int(df['1048577'][index]),1701)
            img_new_temp.append([int(img[new_y][new_x][0]),int(img[new_y][new_x][1]),int(img[new_y][new_x][2])])
            index+=1
            if len(img_new_temp)==1701:
                break
    
    img_new.append(img_new_temp)

img_new = np.array(img_new)
print(type(img_new))
print(img_new)
# print(np.array(img_new).shape)

cv2.imwrite("new.jpg",img_new)
