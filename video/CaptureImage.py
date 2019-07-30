# 本脚本是用于获取指定分辨率的摄像头的图像，并且可以记录拍摄的照片
# 版权所有者：LiQi
# 联系方式： lickeymouses@163.com

# 使用 pyinstaller 对程序打包时，发现生成的 .exe 比较大，以为可能是导入了一下不必要的库
# 所在在本程序中不是简单的 import cv2 而是只将必要的函数 import 进来，但还是发现打包生成的 exe 体积庞大，原因未知

from cv2 import VideoCapture,resize,imshow,waitKey,destroyAllWindows,initUndistortRectifyMap,imwrite
import numpy as np

cap = VideoCapture(0) # 打开默认摄像头
cap.set(3, 1920) # 宽度
cap.set(4, 1080) # 高度
print('Enter ESC/q/Q to quit. Enter space/s/S to save current pictures.')
# A = [[1466.5,0,954.22],[0,1467.8,597.36],[0,0,1]]
# D = [0.0905,-0.1682,-0.0014,-4.56e-4]
size = [1920,1080]
# [mapx,mapy] = initUndistortRectifyMap(A,D,None,A_new,size,5)
count = 0
while(1):
    ret,frame = cap.read() # 读取图像
    if not ret: # 如果没读到图像，则跳过该帧继续读取图像
        continue
    reFrame = resize(frame,(960,540)) # 如果图像太大则将读到的图像scale到一个小的size再显示出来
    imshow("capture",reFrame)
    # imshow("capture",frame) # 将读到的图像显示出来
    key = waitKey(30)   # 响应键盘事件
    if key & 0xFF == ord('q') or key & 0xFF == 27 or key & 0xFF == ord('Q'): # 如果按下了 ESC/q/Q 则退出程序
        break
    elif key & 0xFF == ord('s') or key & 0xFF == 32 or key & 0xFF == ord('S'): # 如果按下了 space/s/S 则保存当前图片
        imwrite(str(count)+".png",frame)
        print('====================='+str(count)+'.png======================')
        count += 1
cap.release()
destroyAllWindows()
