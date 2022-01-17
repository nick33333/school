import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import time
import argparse

# Argeparse setup, -i, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-i','--data_file',default="../data/BME163_Input_Data_4.txt")
parser.add_argument('-o','--output_file', default = "Chan_Nicholas_BME163_Assignment_Week6.png")
args = parser.parse_args()
infile = args.data_file
outfile = args.output_file
stylesheet = args.style_sheet
plt.style.use(stylesheet)

def geneReader(infile):
    """Function that takes infile and parses it to return a list of rows"""
    geneList=[]
    with open(infile, 'r') as myfile:
        for line in myfile:
            entry = line.strip().split('\t')
            if entry[0] != "Gene_symbol":
                geneList.append(np.array(entry[4:14], dtype = float))
    return geneList

# Figure and panel setup
FH=3
FW=5
PW=0.75
PH=2.5
rPW=PW/FW
rPH=PH/FH
plt.figure(figsize=(FW,FH))
panel1=plt.axes([0.1,0.1,rPW,rPH])

# Color gradient setup
blue=(56/255,66/255,157/255)
yellow=(1,225/255,40/255)
step=101
r=np.linspace(yellow[0],blue[0],step)
g=np.linspace(yellow[1],blue[1],step)
b=np.linspace(yellow[2],blue[2],step)


# Call geneReader function to return list of rows from data
GL = geneReader(infile)

# Panel tick and label setup
panel1.set_xlim(0,8) # limit of x axis
panel1.set_ylim(0,len(GL)) # limit of y axis
panel1.set_xticks(np.arange(0.5,8.5,1)) # How I got the xticks to appear between bars
panel1.set_xticklabels(['0','' ,'6','' ,'12','' ,'18', '']) # List of xtick labels to show
panel1.set_yticks(np.linspace(0,1200,7)) # List of ytick labels to show

# Sort rows by Peak_phase(CT) item
GL = sorted(GL, key=lambda x: x[-1], reverse=True)

# Normalization process from lecture
y=0
for row in GL:
    x=0
    trow = row[:8] # Temporary row holding data to be normalized
    normalized=(trow-min(trow))/(max(trow)-min(trow))*100 # linearly transforms/normalizes data between 0 and 100
    for i in normalized.astype(int)[:8]:
        rectangle=mplpatches.Rectangle(
                                    [x,y],1,1,
                                    facecolor=(r[i],g[i],b[i])
                                    )
        panel1.add_patch(rectangle)
        x+=1
    y+=1

panel1.set_xlabel("CT")
panel1.set_ylabel("Number of genes")

plt.savefig(outfile,dpi=600)