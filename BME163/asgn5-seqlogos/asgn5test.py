import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mplpatches
import matplotlib.image as mpimg
from PIL import Image
import sys
import time
import argparse

# Argparse command line options
# Note: The bases -p option should be a path to a directory containing nucleotide pngs
parser = argparse.ArgumentParser()
parser.add_argument('-s','--style_sheet',default='BME163')
parser.add_argument('-p','--bases',default='bases/')
parser.add_argument('-i','--data_file',default='../data/Splice_Sequences.fasta')
parser.add_argument('-o','--output_file', default = "Chan_Nicholas_BME163_Assignment_Week5.png")
args = parser.parse_args()
bases=args.bases
inputfile = args.data_file
stylesheet = args.style_sheet
output = args.output_file

plt.style.use(stylesheet)


# Fasta parser from class
fastaFile=inputfile
fastaDict={}
first=False
for line in open(fastaFile):
	line = line.rstrip()
	if line[0]=='>':
		if first:
			fastaDict[name]=('').join(fastaDict[name])
		name=line[1:]
		fastaDict[name]=[]
		first=True
	else:
		sequence=line
		fastaDict[name].append(sequence)
fastaDict[name]=('').join(fastaDict[name])

# Initialization of dicts to hold 3' and 5' seqs
prime3 = {}
prime5 = {}
for name,sequence in fastaDict.items():
	if name[0]=='3':
		prime3[name]=sequence
	elif name[0]=='5':
		prime5[name]=sequence


# Initialize two dicts, 1 to hold 3' nuc freqs and 1 to hold 5' nuc freqs

# Compute rel freqs of 3' seqs
freqDict3={}
for i in range(1,21):
    # A,T,G,C counts
    freqDict3[i]=np.array([0,0,0,0])
for seq in prime3.values():
    for idx in range(len(seq)):
        nuc = seq[idx]
        if nuc=="A":
            freqDict3[idx+1][0]+=1
        elif nuc =="T":
            freqDict3[idx+1][1]+=1
        elif nuc =="G":
            freqDict3[idx+1][2]+=1
        elif nuc =="C":
            freqDict3[idx+1][3]+=1
for i in range(1,21):
    freqDict3[i]=freqDict3[i]/sum(freqDict3[i])

# Compute rel freqs of 5' seqs
freqDict5={}
for i in range(1,21):
    # A,T,G,C counts
    freqDict5[i]=np.array([0,0,0,0])
for seq in prime5.values():
    for idx in range(len(seq)):
        nuc = seq[idx]
        if nuc=="A":
            freqDict5[idx+1][0]+=1
        elif nuc =="T":
            freqDict5[idx+1][1]+=1
        elif nuc =="G":
            freqDict5[idx+1][2]+=1
        elif nuc =="C":
            freqDict5[idx+1][3]+=1
for i in range(1,21):
    freqDict5[i]=freqDict5[i]/sum(freqDict5[i])

# Dictionaries hold Shannon entropies for nuc positions for 3' and 5' seqs
entropyDict3 = {}
entropyDict5 = {}
for i in range(1,21):
    entropyDict3[i]=-1*sum([i*np.log2(i) for i in freqDict3[i]])
    entropyDict5[i]=-1*sum([i*np.log2(i) for i in freqDict5[i]])

# Compute small-sample correction e_n values
e3 = (1/np.log(2)) * ((4-1)/(2*len(prime3.keys())))
e5 = (1/np.log(2)) * ((4-1)/(2*len(prime5.keys())))

# Dictionaries hold total heights (stack heights) per nuc position of 3' and 5' seqs
TotHdict3={}
TotHdict5={}
for i in range(1,21):
    TotHdict3[i] = np.log2(4)-(entropyDict3[i]+e3)
    TotHdict5[i] = np.log2(4)-(entropyDict5[i]+e5)

heightDict3 = {}
heightDict5 = {}
Bases=["A","T","G","C"]
for i in range(1,21):
    heightDict3[i]=[]
    heightDict5[i]=[]
    tmp3 = [TotHdict3[i]*nuc for nuc in freqDict3[i]]
    tmp5 = [TotHdict5[i]*nuc for nuc in freqDict5[i]]
    for idx in range(4):
        heightDict3[i].append((Bases[idx],tmp3[idx]))
        heightDict5[i].append((Bases[idx],tmp5[idx]))
    heightDict3[i]=sorted(heightDict3[i],key=lambda x:x[1])
    heightDict5[i]=sorted(heightDict5[i],key=lambda x:x[1]) 


FH=3
FW=6
plt.figure(figsize=(FW,FH))
PW=2.4
PH=1
rPW=PW/FW
rPH=PH/FH

panel1=plt.axes([1/12,.3,rPW,rPH])
panel2=plt.axes([0.56666666,0.3,rPW,rPH])


# By default imshow will try not to squish imgs
# Thus we need to turn auto on for aspect
# extent options: extent=[left,right,bottom,top]
# extent sets the bounds for the image
panel1.set_xlim(-10,10)
panel1.set_ylim(0,2)
panel1.set_xticks(np.linspace(-10,10,5))
panel1.set_yticks(np.linspace(0,2,5))

panel2.set_xlim(-10,10)
panel2.set_ylim(0,2)
panel2.set_xticks(np.linspace(-10,10,5))
panel2.set_yticks(np.linspace(0,2,5))


A=mpimg.imread(bases+"/A_small.png")
T=mpimg.imread(bases+"/T_small.png")
C=mpimg.imread(bases+"/C_small.png")
G=mpimg.imread(bases+"/G_small.png")

# heightDict3[x+11] and heightDict5[x+11]
picDict={"A":A, "T":T, "G":G, "C":C}
for x in np.arange(-10,10,1):
    top=0
    bot=0
    for nuc,height in heightDict5[x+11]:
        top+=height
        panel1.imshow(picDict[nuc],aspect="auto",origin="upper",extent=[x,x+1,bot,top])
        bot+=height
    top=0
    bot=0
    for nuc,height in heightDict3[x+11]:
        top+=height
        panel2.imshow(picDict[nuc],aspect="auto",origin="upper",extent=[x,x+1,bot,top])
        bot+=height


rectangle1=mplpatches.Rectangle([0,0], .05,2, linewidth=0, color="black")
rectangle2=mplpatches.Rectangle([0,0], .05,2, linewidth=0, color="black")
panel1.add_patch(rectangle1)
panel2.add_patch(rectangle2)

panel1.tick_params(bottom=True,labelbottom=True,
                  left=True, labelleft=True,
                  right=False, labelright=False,
                  top=False, labeltop=False)
panel2.tick_params(bottom=True,labelbottom=True,
                  left=False, labelleft=False,
                  right=False, labelright=False,
                  top=False, labeltop=False)
panel1.set_title("5'SS")
panel1.set_xlabel("Distance to\nSplice Site")
panel1.set_ylabel("Bits")

panel2.set_title("3'SS")
panel2.set_xlabel("Distance to\nSplice Site")


plt.savefig(output,dpi=600)
