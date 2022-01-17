import argparse
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from PIL import Image
# Argeparse setup, -i, -s and -o are the flags
parser = argparse.ArgumentParser()
parser.add_argument('-i','--data_file',default='theoretical-data.txt')
parser.add_argument('-o','--output_file',default="after-decoding-data.png")
args = parser.parse_args()
inputfile = args.data_file
outputfile = args.output_file

font = {
        'size'   : 4}

matplotlib.rc('font', **font)

panel1.set_xticklabels(["a.txt", "aaa.txt", "alphabet.txt", "random.txt"])



FW = 3.5
FH = 3
fig = plt.figure(figsize=[FW,FH])
PW = 2
PH = 2
rW = PW/FW
rH = PH/FH

panel2 = plt.axes([.2,.2,rW,rH],
                  xlabel='Error Rate',
                  ylabel='Shannon Entropy'
                  )

colors = ['green','red','blue','orange']
heights = [0,0,4.75.999488]
for i in range(4):
  rectangle = mplpatches.Rectangle([i*(pw/6),0],pw/6,heights[i],
                                    facecolor=colors[i],
                                    edgecolor='black',
                                    linewidth=1,
                                    zorder=4)
  panel2.add_patch(rectangle)



panel2.set_title("Entropy Before Encoding",y=1.01)
panel2.tick_params(bottom=True, labelbottom=True,
                   left=True, labelleft=True,
                   right=False, labelright=False,
                   top=False, labeltop=False)


green_patch = mpatches.Patch(color='green', label='a')
red_patch = mpatches.Patch(color='red', label='aaa')
blue_patch = mpatches.Patch(color='blue', label='alphabet')
orange_patch = mpatches.Patch(color='orange', label='random')

l1= panel2.legend(handles=[green_patch],loc='lower left', bbox_to_anchor=(1.1, .92))
l2 = panel2.legend(handles=[red_patch],loc='lower left', bbox_to_anchor=(1.1, .87))
l3 = panel2.legend(handles=[blue_patch],loc='lower left', bbox_to_anchor=(1.1, .82))
l4 = panel2.legend(handles=[orange_patch],loc='lower left', bbox_to_anchor=(1.1, .77))

panel2.add_artist(l1)
panel2.add_artist(l2)
panel2.add_artist(l3)
panel2.add_artist(l4)

plt.savefig(outputfile,dpi=600)
image = Image.open(outputfile)
image.show()