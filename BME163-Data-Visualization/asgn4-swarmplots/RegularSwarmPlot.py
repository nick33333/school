import matplotlib.pyplot as plt
import matplotlib.patches as mplpatches
import numpy as np
import time
import matplotlib as mpl



def swarmplot(panel,yList,xCenter,PW,PH,xmin,xmax,ymin,ymax,span,pointsize,color):
	xrange=xmax-xmin
	yrange=ymax-ymin
	minDist = pointsize/72 # diameter of a point from the plot function
	increment=((minDist/10)/PW)*xrange # 1/10th of miin dist makes the plot smoother 

	placedPoints=[]
	stop=False
	for yPos in yList: # draw new point
		if not stop:
			xPos=xCenter
			if len(placedPoints)==0:
				placedPoints.append((xPos,yPos))
			else:
				comparePoints=[]
				for point in placedPoints:
					yPosPlaced=point[1]
					ydist=np.abs(((yPos-yPosPlaced)/yrange)*PH)
					if ydist<minDist:
						comparePoints.append(point)
				if len(comparePoints) > 0:
					placed=False
					shift=0
					while placed==False:
						for direction in [-1,1]:
							distance_list=[]
							xPos=xCenter+(shift*direction)
	
							for point in comparePoints:
								xPosPlaced=point[0] # x-position of the point placed before
								yPosPlaced=point[1] # y-position of the point placed before
								xdist=((xPos-xPosPlaced)/xrange)*PW
								ydist=((yPos-yPosPlaced)/yrange)*PH
								distance=(xdist**2 + ydist**2)**0.5
								distance_list.append(distance)
		
							if min(distance_list) > minDist:
								placedPoints.append((xPos,yPos))
								placed=True
								break
							else:
								shift+=increment
								if shift>span/2:
									stop=True
				else:
					placedPoints.append((xPos,yPos))
	xList=[]
	yList=[]
	for point in placedPoints:
		xList.append(point[0])
		yList.append(point[1])
	median=np.median(yList)
	print(median)
	panelCenter.plot(xList,yList,
					marker='o',
					markerfacecolor=color,
					markeredgecolor='black',
					markersize=pointsize,
					markeredgewidth=0,
					linewidth=0)
	panel.plot([xCenter-span/2,span/2+xCenter],[median,median],
               linewidth=1, color='red',zorder=5)
	# panel.plot([position-width/2,position+width/2],[median,median],
 #               linewidth=1, color='red')



plt.style.use('BME163')
font = {'size':14}
mpl.rc('font', **font)
FH=3
FW=7

plt.figure(figsize=(FW,FH))

PWc=5
PHc=2

rPWc=PWc/FW
rPHc=PHc/FH

# left, bottom, width, height
panelCenter = plt.axes([0.1,0.2,rPWc,rPHc])

# Mean, stdev, number of points
xList=[]
yList=[]

inFile=open('BME163_Input_Data_3.txt','r')

binsize=1.5 # The smaller the bin size the less overlap, the larger the bin size vice versa
dataDict = {}
for line in inFile:
	splitLine=line.strip().split('\t')
	name=splitLine[0]
	Rep1=int(name.split('_')[3])
	if Rep1>=11:
		Rep1=11
	Rep2=float(splitLine[1])
	if Rep1 not in dataDict:
		dataDict[Rep1]=[]
	dataDict[Rep1].append(Rep2)

xmin=0
xmax=12
ymin=75
ymax=100



for xBin in np.arange(0,12,1): # This determines number of swarms... kinda
	if xBin in dataDict:
		print(xBin)
		yList=dataDict[xBin]
		start=time.time()
		swarmplot(panelCenter,yList,xBin,PWc,PHc,xmin,xmax,ymin,ymax,binsize/2,1.5,'black')
		end=time.time()
		duration=end-start
		print(duration)

x = np.linspace(0.25,11.75,500)
y = 500*[95]
line = panelCenter.plot(x,y, "--",linewidth=0.8, color='black', dashes=[3,7,8,7])


panelCenter.tick_params(bottom=True, labelbottom=True,
						left=True, labelleft=True,
						right=False, labelright=False,
						top=False, labeltop=False)

panelCenter.set_xticks(np.linspace(1,11,11))
panelCenter.set_yticks(np.linspace(75,100,6))
panelCenter.set_xlim(0.5,11.5)
panelCenter.set_ylim(ymin,ymax)
panelCenter.set_ylabel("Identity (%)", fontsize=12)
panelCenter.set_xlabel("Subread coverage", fontsize=12)


plt.savefig("Old_Vollmers_swarm.png", dpi=600)


