import numpy as np
import pandas as pd
import cv2

path = "22m-seq.csv"
df = pd.read_csv(path)
df_col = df.columns
print(df_col)
i=0
for x in df['1048577']:
    print(x)
    i+=1
    if i == 20:
        break

img_path = "R.jpg"
img = cv2.imread(img_path)
print(img[0][1])