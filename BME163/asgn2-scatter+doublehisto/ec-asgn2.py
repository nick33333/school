import math
import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import argparse
from PIL import Image

# Argeparse setup, -i, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-i','--data_file',default='BME163_Input_Data_1.txt')
parser.add_argument('-o','--output_file', default = "ectest.png")
args = parser.parse_args()

stylesheet = args.style_sheet
data = args.data_file
output = args.output_file

# Style sheet selection
# plt.style.use(stylesheet)

# Data selection and parsing
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
xList = [np.log2((i+1)) for i in xList]
yList = [np.log2((i+1)) for i in yList]

# xList = []
# yList = []
# inFile = open(data,'r')
# for line in inFile:
#   splitLine = line.strip().split('\t')
#   name = splitLine[0]
#   Rep1 = int(splitLine[1])
#   Rep2 = int(splitLine[2])
#   xList.append(Rep1)
#   yList.append(Rep2)

# xList = np.log2(np.array(xList)+1)
# yList = np.log2(np.array(yList)+1)

# Figure
FH = 2
FW = 5
plt.figure(figsize=(FW,FH))
PW=1
PH=1
relPW = PW/FW
relPH = PH/FH
# ask them to politely leave mwahahhaha dango boom megalo mart

"""
Custom heatmap function
takes:
- xList
- yList
- panelCenter
We need a dictionary to keep track of x and y values
"""
def general_flooring(number, floor):
  return int(number/floor)*floor


def heatmap(xList, yList,panel, xmin, xmax, ymin, ymax, binsize):

  white = (1,1,1)
  black = (0,0,0)

  R = np.linspace(white[0],black[0],21)
  G = np.linspace(white[1],black[0],21)
  B = np.linspace(white[2],black[0],21)

  # Create nested dict to hold counts for our heatmap squares
  dataDict = {}
  for xBin in np.arange(xmin,xmax,binsize): # going from min x to max x in steps of size binsize
    dataDict[xBin] = {}
    for yBin in np.arange(ymin,ymax,binsize):
      dataDict[xBin][yBin] = 0


  # Iterate through x and y data while flooring them
  # Increment each dataDict entry by where the floored x and y values land
  for i in np.arange(0, len(xList), 1):
    x = xList[i]
    y = yList[i]
    xFloored = general_flooring(x,binsize)
    yFloored = general_flooring(y,binsize)
    if xFloored in dataDict:
      if yFloored in dataDict[xFloored]:
        dataDict[xFloored][yFloored] += 1

  # Give each dataDict entry a rectangle and color
  for xBin in np.arange(xmin,xmax,binsize): # going from min x to max x in steps of size binsize
    for yBin in np.arange(ymin,ymax,binsize):
      value = min(dataDict[xBin][yBin],20) # 20 will set the max darkness, if entry>20, default to 20
      color = (R[value], G[value], B[value])
      rectangle = mplpatches.Rectangle((xBin,yBin),binsize,binsize,
                                        linewidth = 0,
                                        facecolor=color,
                                        edgecolor=(0,0,0))
      panel.add_patch(rectangle)




# Scatter plot
panel1 = plt.axes([0.14,0.15,relPW, relPH])
panel1.plot(xList,yList,
           marker = 'o',
           markerfacecolor='black',
           markeredgecolor='black',
           markersize=1.425,
           markeredgewidth=0,
           linewidth=0,
           alpha=0)
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

yHisto,bins = np.histogram(yList,np.linspace(0,14,29))
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

xHisto,bins = np.histogram(xList,np.linspace(0,14,29))
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



heatmap(xList, yList,panel1, 0, 15, 0, 15, 0.25) 


# Save pic
plt.savefig(output,dpi=600)
image = Image.open(output)
image.show()

