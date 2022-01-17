import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import time
import math
import scipy.stats as stats
import random
from PIL import Image
import matplotlib as mpl

font = {'size':7}
mpl.rc('font', **font)

xList = []
yList = []

# there are 5 tab separated items in this data sheet
# need to split the data[0] element with _
# need to take in data[0][3] item as the subread column
# data [1] is the % identity read, use this as y value
dataDict = {}
for num in np.arange(1,12):
    dataDict[num] = []

with open("../data/BME163_Input_Data_3.txt") as myfile:
    for line in myfile:
        data = line.strip().split("\t")
        coverage = data[0].split("_")[3]
        identity = data[1]
        xList.append(coverage)
        yList.append(identity)

for num in np.arange(len(xList)):
    if int(xList[num]) < 11:
        dataDict[int(xList[num])].append(float(yList[num]))
    else:
        dataDict[11].append(float(yList[num]))
    
        
print(xList[0])
print(type(xList[0]))

print(yList[0])


# figure is 7" wide by 3" high
# panel is 5" wide by 2"" high

plt.style.use('BME163')
FH = 3
FW = 7
fig = plt.figure(figsize=(FW,FH))
PW=5
PH=2
relPW = PW/FW
relPH = PH/FH
panel1 = plt.axes([.100,.2,relPW,relPH])
xmin = 0
xmax = 12
ymin = 75
ymax = 100
panel1.set_xlim(xmin,xmax)
panel1.set_ylim(ymin,ymax)


panel1.set_xticks([1,2,3,4,5,6,7,8,9,10,11])
panel1.set_xticklabels(['1','2','3','4','5','6','7','8','9','10','>11'])
panel1.set_xlabel("Subread Coverage")
panel1.set_ylabel("Identity %")

def new_boxplot(y,position,width,panel):
    """Homemade boxplot"""
    median=np.median(y)
    percentile25 = np.percentile(y,25)
    percentile75 = np.percentile(y,75)
    percentile5 = np.percentile(y,5)
    percentile95 = np.percentile(y,95)
    # Box
    rectangle = mplpatches.Rectangle([position-(width/2),percentile25],width,percentile75-percentile25,
                                    facecolor=(1,1,1),
                                    edgecolor='black',
                                    linewidth=1,
                                    zorder=4)
    panel.add_patch(rectangle)
    # Median line
    panel.plot([position-width/2,position+width/2],[median,median],
               linewidth=1, color='red',zorder=5)
    # 
    panel.plot([position-width/2,position+width/2],[median,median],
               linewidth=1, color='red')
    
    panel.plot([position,position],[percentile5,percentile95],
               linewidth=1,color='black')
    panel.plot([position-width/4,position+width/4],[percentile5,percentile5],
               linewidth=1,color='black',zorder=5)
    panel.plot([position-width/4,position+width/4],[percentile95,percentile95],
               linewidth=1,color='black',zorder=5)
    # outliers = []
    # for point in y:
    #     if point > percentile95 or point < percentile5:
    #         outliers.append(point)
            
    # panel.plot([4]*len(outliers),outliers,marker='o',markersize=1,markerfacecolor='black',markeredgewidth=0,
    #            linewidth=1,color='black',zorder=4,alpha=0.1)


for coverage in dataDict.keys():    
    subsample_yList=[]
    indices=np.random.choice(range(0,len(dataDict[coverage]),1),1000)
    for index in indices:
        subsample_yList.append(dataDict[coverage][index])
    new_boxplot(subsample_yList,coverage,0.5,panel1)

# for coverage in dataDict.keys():  
#     panel1.plot([coverage-.4, coverage+.4],[np.median(dataDict[coverage]),np.median(dataDict[coverage])], 
#                 linewidth=1, color = "red")


plt.savefig("boxswarm.png",dpi = 600)
image = Image.open("boxswarm.png")
image.show()
