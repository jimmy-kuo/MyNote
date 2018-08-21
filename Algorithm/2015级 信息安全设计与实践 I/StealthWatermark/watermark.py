#!/usr/bin/env python
# encoding:utf-8

"""
数字水印技术
哈尔滨工业大学(威海) 2018
信息安全设计与实践 I

author    :   @`13
time      :   2018.8.21
"""

# GUI
import tkFileDialog as dialog
import tkMessageBox
import ttk
from Tkinter import *

# PIC
import PIL
from PIL import Image
import cv2

# 通用
import numpy as np
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

np.seterr(divide='ignore', invalid='ignore')


class WaterMark(object):
    """不可见水印"""

    def __init__(self, parent):
        self.parent = parent  # GUI主体
        self.size = 256  # 图片大小 256*256
        self.N = 32  # 水印大小 32*32
        self.K = 8
        self.Key1 = np.array([1, 2, 3, 4, 5, 6, 7, 8])
        self.Key2 = np.array([8, 7, 6, 5, 4, 3, 2, 1])

        self.state = 0
        # 绘制GUI
        fig = Figure()
        self.orign = fig.add_subplot(221)
        self.orign.set_title("origin")
        self.watermark = fig.add_subplot(222)
        self.watermark.set_title("watermark")
        self.pic_with_watermark = fig.add_subplot(223)
        self.pic_with_watermark.set_title("pic with watermark")
        self.watermark_from_pic = fig.add_subplot(224)
        self.watermark_from_pic.set_title("watermark from pic")

        self.canvas = FigureCanvasTkAgg(fig, self.parent)
        self.canvas._tkcanvas.config(bg='gainsboro', highlightthickness=0)  #
        self.canvas._tkcanvas.pack(side=TOP, fill=BOTH, expand=YES, padx=0)
        self.canvas.draw()

        frame = Frame(self.parent)
        frame.pack(fill=X)
        # button
        label = Label(frame, text='水印图片保存为')
        label.pack(side=LEFT)
        self.filename = StringVar()
        entry = Entry(frame, textvariable=self.filename)
        entry.pack(side=LEFT)
        button2 = Button(frame, text='添加水印', command=self.insert_mark)
        button2.pack(side=LEFT)
        frame2 = Frame(frame)
        frame2.pack(side=RIGHT)
        button1 = Button(frame2, text='提取水印', command=self.seperate_mark)
        button1.pack(side=LEFT, padx=20)
        button3 = Button(frame2, text='测试', command=self.noise_test)
        button3.pack(side=LEFT)

        # Toolbar
        variable = [u'添加白噪声', u'高斯低通滤波']
        self.comboBox = ttk.Combobox(frame2, value=variable, width=10)
        self.comboBox.set(u'添加白噪声')
        self.comboBox.pack(side=LEFT)

        # menu
        menubar = Menu(self.parent)
        filemenu = Menu(menubar)
        filemenu.add_command(label='打开源图片', command=self.open_image)
        filemenu.add_command(label='打开水印', command=self.open_mark)
        filemenu.add_command(label='打开带水印图片', command=self.open_picture)
        menubar.add_cascade(label='图片', menu=filemenu)
        self.parent.config(menu=menubar)

    def change_channals(self, image):
        """分离和合并通道"""
        image = image
        image = PIL.Image.fromarray(np.uint8(image))  # 将图片转为数组
        r, g, b = image.split()  # 按照RGB分离
        image = PIL.Image.merge('RGB', (b, g, r))  # 合并图片
        return image

    def open_image(self):
        """打开原图片"""
        self.image = dialog.askopenfilename(parent=self.parent, filetypes=[('*', '*.*')], title='Open ')
        if self.image:
            self.image = cv2.imread(self.image.encode('gbk'))  # 打开图片
            self.image = cv2.resize(self.image, (self.size, self.size))  # 图片缩放
            image = self.change_channals(self.image)  # 通道合并
            self.orign.imshow(image)
            self.canvas.draw()

    def open_mark(self):
        """打开水印"""
        self.mark = dialog.askopenfilename(parent=self.parent, filetypes=[('*', '*.*')], title='Open ')
        if self.mark:
            self.mark = cv2.imread(self.mark.encode('gbk'))  # 打开
            self.mark = cv2.resize(self.mark, (self.N, self.N))  # 缩放
            self.watermark.imshow(self.mark)  # 展示
            self.canvas.draw()

    def open_picture(self):
        """打开带水印的图片"""
        self.picture = dialog.askopenfilename(parent=self.parent, filetypes=[('*', '*.*')], title='Open ')
        if self.picture:
            self.picture = cv2.imread(self.picture.encode('gbk'))  # 打开
            self.picture = cv2.resize(self.picture, (self.size, self.size))  # 缩放
            picture = self.change_channals(self.picture)  # 合并通道
            self.pic_with_watermark.imshow(picture)  # 展示
            self.canvas.draw()

    def insert_mark(self):
        """插入水印"""
        if self.filename.get() == '':  # 获取图片名称
            tkMessageBox.showwarning(message='输入不能为空')
        else:
            self.image = cv2.resize(self.image, (self.size, self.size))
            D = self.image.copy()  # 复制原图片

            # DCT变换代码
            alfa = 10
            for p in range(self.size / self.K):
                for q in range(self.size / self.K):
                    x = p * self.K
                    y = q * self.K
                    img_B = np.float32(D[x:x + self.K, y:y + self.K, 0])
                    I_dct1 = cv2.dct(img_B)

                    if self.mark[p, q, 0] < 100:
                        Key = self.Key1
                    else:
                        Key = self.Key2

                    I_dct_A = I_dct1.copy()
                    I_dct_A[0, 7] = I_dct1[0, 7] + alfa * Key[0]
                    I_dct_A[1, 6] = I_dct1[1, 6] + alfa * Key[1]
                    I_dct_A[2, 5] = I_dct1[2, 5] + alfa * Key[2]
                    I_dct_A[3, 4] = I_dct1[3, 4] + alfa * Key[3]
                    I_dct_A[4, 3] = I_dct1[4, 3] + alfa * Key[4]
                    I_dct_A[5, 2] = I_dct1[5, 2] + alfa * Key[5]
                    I_dct_A[6, 1] = I_dct1[6, 1] + alfa * Key[6]
                    I_dct_A[7, 0] = I_dct1[7, 0] + alfa * Key[7]

                    I_dct_A = np.array(I_dct_A)
                    I_dct_a = cv2.idct(I_dct_A)

                    max_point = np.max(I_dct_a)
                    min_point = np.min(I_dct_a)

                    D[x:x + self.K, y:y + self.K, 0] = I_dct_a

            self.picture = D
            E = D.copy()
            filename = self.filename.get()
            cv2.imwrite(filename, E)
            E = self.change_channals(E)
            E = np.uint8(E)
            cv2.imwrite(filename, E)
            self.pic_with_watermark.imshow(E)
            self.canvas.draw()

    def seperate_mark(self):
        """分离水印"""
        self.Pmark = np.zeros((32, 32, 3))

        pp = np.zeros(8)
        for p in range(self.size / self.K):
            for q in range(self.size / self.K):
                x = p * self.K
                y = q * self.K
                # 取相应元素保存到img_b中
                img_B = np.float32(self.picture[x:x + self.K, y:y + self.K, 0])
                I_dct1 = cv2.dct(img_B)

                pp[0] = I_dct1[0, 7]
                pp[1] = I_dct1[1, 6]
                pp[2] = I_dct1[2, 5]
                pp[3] = I_dct1[3, 4]
                pp[4] = I_dct1[4, 3]
                pp[5] = I_dct1[5, 2]
                pp[6] = I_dct1[6, 1]
                pp[7] = I_dct1[7, 0]

                if np.corrcoef(pp, self.Key1)[0][1] <= np.corrcoef(pp, self.Key2)[0][1]:
                    self.Pmark[p, q, 0] = 1
                    self.Pmark[p, q, 1] = 1
                    self.Pmark[p, q, 2] = 1

        if self.state == 0:
            self.watermark_from_pic.imshow(self.Pmark)
            self.canvas.draw()

    def whitenoise(self, image):
        """白噪声"""
        image = image
        noise = 10 * np.random.randn(self.size, self.size, 3)
        self.WImage = image + noise

    def gaussian(self, image):
        """高斯低通滤波"""
        self.WImage = cv2.GaussianBlur(image, (5, 5), 1.5)

    def noise_test(self):
        """噪声测试"""
        self.state = 1

        filter_name = self.comboBox.get()
        if filter_name == u'添加白噪声':
            self.whitenoise(self.picture)
        elif filter_name == u'高斯低通滤波':
            self.gaussian(self.picture)

        figure = Toplevel(self.parent)
        fig = Figure()
        self.seperate_mark()
        canvas = FigureCanvasTkAgg(fig, figure)
        canvas._tkcanvas.config(bg='gainsboro', highlightthickness=0)
        canvas._tkcanvas.pack(side=TOP, fill=BOTH, expand=YES, padx=0)
        axe1 = fig.add_subplot(211)
        axe1.set_title("pic")
        WImage = self.change_channals(self.WImage)
        axe1.imshow(WImage)
        axe2 = fig.add_subplot(212)
        axe2.imshow(self.Pmark)
        self.state = 0
        canvas.draw()


if __name__ == '__main__':
    root = Tk()
    watermark = WaterMark(root)
    root.mainloop()
