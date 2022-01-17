import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import argparse

# Argeparse setup, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-s', '--style_sheet', default='BME163')
parser.add_argument('-o', '--output_file')
args = parser.parse_args()

stylesheet = args.style_sheet
outputfile = args.output_file

# Style sheet selection
plt.style.use(stylesheet)

# Figure set up
figureHeight=2
figureWidth=3.42
plt.figure(figsize=(figureWidth,figureHeight))

# linspace is inclusive on both ends, use it
# Panel 1 code
panelWidth=1
panelHeight=1
relativePanelWidth=panelWidth/figureWidth
relativePanelHeight=panelHeight/figureHeight
panel1=plt.axes([0.1,0.2,relativePanelWidth,relativePanelHeight])
xList = np.linspace(0,1,25)
for value in xList:
    xvalue = np.cos((np.pi/2)*value)
    yvalue = np.sin((np.pi/2)*value)
    panel1.plot(xvalue,yvalue,
                marker='o',
                markerfacecolor=(xvalue,xvalue,xvalue),
                markeredgecolor='black',
                markersize=2.0,
                markeredgewidth=0,
                linewidth=0)
panel1.set_xticks(range(0,1))
panel1.tick_params(bottom=False, labelbottom=False,
                   left=False, labelleft=False,
                   right=False, labelright=False,
                   top=False, labeltop=False)

# Panel 2 Code
panel2 = plt.axes([0.55,0.2,relativePanelWidth,relativePanelHeight])
boxDict=dict()
keyList = []
for i in range(10):
    for j in range(10):
        keyList.append('('+str(i)+','+str(j)+')')
for z in range(len(keyList)):
    k = eval(keyList[z])
    x = .1*k[0]
    y = .1*k[1]
    r = x
    g = y
    b = 1
    boxDict[keyList[z]] = 'panel2.add_patch(mplpatches.Rectangle([' + str(x) + ',' + str(y) + '],0.1,0.1,facecolor=('+str(r)+','+str(g)+','+str (b)+'),edgecolor=\'black\'))'
for i in keyList:
    eval(boxDict.get(i))
panel2.tick_params(bottom=False, labelbottom=False,
                   left=False, labelleft=False,
                   right=False, labelright=False,
                   top=False, labeltop=False)

# Save pic
plt.savefig(outputfile, dpi=600)
