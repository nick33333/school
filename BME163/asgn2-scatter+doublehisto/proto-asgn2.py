import math
import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import argparse
import time 

parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-i','--data_file',default='BME163_Input_Data_1.txt')
parser.add_argument('-o','--output_file')
args = parser.parse_args()

stylesheet = args.style_sheet
data = args.data_file
output = args.output_file

plt.style.use(stylesheet)
with open(data,"r") as myfile:
    data = []
    xList = []
    yList = []
    for line in myfile:
        if line.startswith("_"):
            continue
        else:
            xList.append(int(line.strip().split('\t')[1]))
            yList.append(int(line.strip().split('\t')[2]))
logxList = [np.log2((i+1)) for i in xList]
logyList = [np.log2((i+1)) for i in yList]

# Figure
FH = 2
FW = 5
plt.figure(figsize=(FW,FH))
PW=1
PH=1
relPW = PW/FW
relPH = PH/FH

# Scatter plot
panel1 = plt.axes([0.14,0.15,relPW, relPH])
panel1.plot(logxList,logyList,
           marker = 'o',
           markerfacecolor='black',
           markeredgecolor='black',
           markersize=1.425,
           markeredgewidth=0,
           linewidth=0,
           alpha=.1)
panel1.set_xticks(np.linspace(0,15,4))
panel1.set_yticks(np.linspace(0,15,4))
panel1.set_xlim(0,15,1)
panel1.set_ylim(0,15,1)
panel1.tick_params(bottom=True, labelbottom=True,
                   left=False, labelleft=False,
                   right=False, labelright=False,
                   top=False, labeltop=False)

# Histogram 2 Vertical long
panel2 = plt.axes([0.076,0.15,relPW/4, relPH])
panel2.set_xlim(0,15,1)
panel2.set_ylim(0,15,1)
panel2.set_xticks(np.linspace(0,20,2))
panel2.set_yticks(np.linspace(0,15,4))

yHisto,bins = np.histogram(logyList,np.linspace(0,14,29))
for i in range(0,len(yHisto),1):
    bottom = bins[i]
    left = 0
    width = np.log2((yHisto[i]+1))
    height = bins[i+1]-bottom
    rectangle = mplpatches.Rectangle([left,bottom],width,height,
                                     facecolor='grey',
                                     edgecolor='black',
                                     linewidth = 0.1)
    panel2.add_patch(rectangle)
panel2.invert_xaxis()
panel2.tick_params(bottom=True, labelbottom=True,
                   left=True, labelleft=True,
                   right=False, labelright=False,
                   top=False, labeltop=False)

# Histogram 3 Horizontal long
panel3 = plt.axes([.14,.685,relPW, relPH/4])
panel3.set_xticks(np.linspace(0,15,2))
panel3.set_yticks(np.linspace(0,20,2))

xHisto,bins = np.histogram(logxList,np.linspace(0,14,29))
for i in range(0,len(xHisto),1):
    bottom = 0
    left = bins[i]
    width = bins[i+1]-left
    height = np.log2((xHisto[i]+1))
    rectangle = mplpatches.Rectangle([left,bottom],width,height,
                                     facecolor='grey',
                                     edgecolor='black',
                                     linewidth = 0.1)
    panel3.add_patch(rectangle)
panel3.tick_params(bottom=False, labelbottom=False,
                   left=True, labelleft=True,
                   right=False, labelright=False,
                   top=False, labeltop=False)

plt.savefig(output,dpi=600)

