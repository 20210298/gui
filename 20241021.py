# https://www.youtube.com/watch?v=LrdRLxMIz_E
# 시험 범위는 위의 동영상 까지 class로 gui 

from PyQt6 import QtWidgets
from PyQt6 import QtGui
from PyQt6 import QtCore
from PyQt6.QtCore import Qt

def btnLoad_clicked():
    pixmap=QtGui.QPixmap("./cat.png")
    lbImg.setPixmap(pixmap)

app = QtWidgets.QApplication([])

window = QtWidgets.QWidget()
window.resize(1280,800)
window.setWindowTitle('MyFirstQt')
window.show()

btnLoad = QtWidgets.QPushButton('Load',window)
btnLoad.setGeometry(10,10,100,50)
btnLoad.show()
btnLoad.clicked.connect(btnLoad_clicked)

lbImg = QtWidgets.QLabel('image',window)
lbImg.setGeometry(120,10,1280-120-10,800-10-10)
lbImg.show()

app.exec()
