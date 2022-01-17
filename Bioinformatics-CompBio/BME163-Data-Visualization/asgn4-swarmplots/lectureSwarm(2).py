"""
I had to go with the boxplots for this assignment

Program will take in data for coverage and % identity
Arguments:
-s      : stylesheet
-i      : input file
-o      : outputfile
Optional arguments I've added are:
-ms     : maximum subread coverage
-ymin   : min y value to display
-ymax   : max y value to display
-ss     : Number of items to subsample, turned off by default but will subsample data when given an integer
-show   : Will open image after program is finished

"""
import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import argparse
import scipy.stats as stats
import random
from PIL import Image
import matplotlib as mpl

# Argeparse setup, -i, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-i','--data_file',default='BME163_Input_Data_3.txt')
parser.add_argument('-o','--output_file', default = "Chan_Nicholas_BME163_Assignment_Week4.png")
# optional arguments
parser.add_argument('-ms','--msrc', default = 11, type=int)
parser.add_argument('-ymin','--ymin', default = 75, type=int)
parser.add_argument('-ymax','--ymax', default = 100, type=int)
parser.add_argument('-ss','--subsample', default = False, type = int)
parser.add_argument('-show','--show', default = False)
args = parser.parse_args()
inputfile = args.data_file
stylesheet = args.style_sheet
output = args.output_file
maxSubReadCoverage = args.msrc
ymin = args.ymin
ymax = args.ymax
subsample = args.subsample
show = args.show
font = {'size':7}
mpl.rc('font', **font)


# Plug this into the psuedo given
def xdist(x1,x2,xmax,xmin,pw):
    numDiff = abs(x1-x2)
    denDiff = abs(xmax-xmin)
    return pw*(numDiff/denDiff)
def ydist(y1,y2,ymax,ymin,ph):
    return xdist(y1,y2,ymin,ymax,ph)
def dist(xdist,ydist):
    return sqrt((xdist**2)+(ydist**2))




def new_boxplot(y,position,width,panel):
    """
    Boxplot made in lecture, 
    graphs box from 25th to 75th percentiles
    graphs whiskers from 5th to 95th percentiles
    """
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

def boxSwarm(inputfile,stylesheet,output,maxSubReadCoverage=11,ymin=75,ymax=100,subsample=False,show=False):
    # there are 5 tab separated items in this data sheet
    # need to split the data[0] element with _
    # need to take in data[0][3] item as the subread column
    # data [1] is the % identity read, use this as y value
    xList = []
    yList = []
    dataDict = {}
    for num in np.arange(1,maxSubReadCoverage+1):
        dataDict[num] = []
    
    with open(inputfile) as myfile:
        for line in myfile:
            data = line.strip().split("\t")
            coverage = data[0].split("_")[3]
            identity = data[1]
            xList.append(coverage)
            yList.append(identity)
    
    
    
    for num in np.arange(len(xList)):
        if int(xList[num]) < maxSubReadCoverage:
            dataDict[int(xList[num])].append(float(yList[num]))
        else:
            dataDict[maxSubReadCoverage].append(float(yList[num]))
        
            
    # print(xList[0])
    # print(type(xList[0]))
    
    # print(yList[0])
    
    
    
    # figure is 7" wide by 3" high
    # panel is 5" wide by 2"" high
    
    plt.style.use(stylesheet)
    FH = 3
    FW = 7
    fig = plt.figure(figsize=(FW,FH))
    PW=5
    PH=2
    relPW = PW/FW
    relPH = PH/FH
    panel1 = plt.axes([.100,.2,relPW,relPH])
    xmin = 0
    xmax = maxSubReadCoverage+1
    panel1.set_xlim(xmin,xmax)
    panel1.set_ylim(ymin,ymax)
    
    
    panel1.set_xticks([i for i in range(1,maxSubReadCoverage+1)])
    panel1.set_xticklabels([str(i) for i in range(1,maxSubReadCoverage)]+[">{0}".format(maxSubReadCoverage-1)])
    # panel1.set_xticklabels(['1','2','3','4','5','6','7','8','9','10','>maxSubReadCoverage'])
    panel1.set_xlabel("Subread Coverage")
    panel1.set_ylabel("Identity %")
    
    # Boxplot function called here
    for coverage in dataDict.keys():
        if subsample:    
            subsample_yList=[]
            indices=np.random.choice(range(0,len(dataDict[coverage]),1),subsample)
            for index in indices:
                subsample_yList.append(dataDict[coverage][index])
            new_boxplot(subsample_yList,coverage,0.5,panel1)
        else:
            new_boxplot(dataDict[coverage],coverage,0.5,panel1)

    plt.savefig(output,dpi = 600)
    if show:
        image = Image.open(output)
        image.show()


boxSwarm(inputfile,stylesheet,output,maxSubReadCoverage,ymin,ymax,subsample,show)

