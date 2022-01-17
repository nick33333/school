# Col 1 Gene name
# Col 2 log2(fold_change) --> x axis
# Col 3 p-values (which you still have to -log10 convert) --> y axis

# Color pts in red i if their fold-change (not log2(fold-change)) is larger than 10 (up or down) 
# and their -log10(p-value) is above 8

# Label points with their gene names if their fold-change (not log2(fold-change)) is larger than 10 (only down) 
# and their -log10(p-value) is greater than 30.


"""
(Step 1) 
xList col 2 values and yList the -log10 of pvalues in col3

(Step 2)
plot these points as black

(Step 3)
With conditional, plot again, but only for points that meet the condition for red

(Step 4)
With conditiona, label points with gene name if their condition is met
"""
import argparse
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
from PIL import Image

# Argeparse setup, -i, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-i','--data_file',default='../data/BME163_Input_Data_2.txt')
parser.add_argument('-o','--output_file',default='Chan_Nicholas_BME163_Assignment_Week3.png')
args = parser.parse_args()
stylesheet = args.style_sheet
inputfile = args.data_file
outputfile = args.output_file

plt.style.use(stylesheet)

data = []
with open(inputfile,"r") as myfile:
    for line in myfile:
        r_entry = line.strip('\n').split('\t')
        entry = [0 if i=='NA' else i for i in r_entry]
        data.append((entry[0],float(entry[1]),float(entry[2])))

FW = 3
FH = 3
fig = plt.figure(figsize=(FW,FH))
PW = 2
PH = 2
rPW = PW/FW
rPH = PH/FH
panel1 = plt.axes([1/6,1/6,rPW,rPH])

xList = [x[1] for x in data]
yList = [0 if y[2]==0 else -np.log10(y[2]) for y in data]
panel1.plot(xList, yList, linewidth=0,marker='o',
           mew=0,mfc='black',ms=1.425)

for i in range(len(xList)):
    if 2**abs(xList[i]) > 10 and yList[i] > 8:
        panel1.plot(xList[i], yList[i], linewidth=0,marker='o',
                    mew=0,mfc='red',ms=1.425)
        if 2**(-xList[i]) > 10 and yList[i] > 30:
            panel1.text(xList[i],yList[i],data[i][0]+' ', va='center',ha='right', fontsize=6)

panel1.set_xlim(-12,12,5)
panel1.set_ylim(0,60)
panel1.set_xlabel(r"log$_{2}$(fold change)")
panel1.set_ylabel(r"-log$_{10}$(p-value)")

plt.savefig(outputfile,dpi=600)
# image = Image.open(outputfile)
# image.show()