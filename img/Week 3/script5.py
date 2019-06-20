import rhinoscriptsyntax as rs
import random

for c in range(20):
	listofpoint=[]
	for i in range(3):
		x=random.uniform(-200,200)
		y=random.uniform(-200,200)
		z=random.uniform(-300,300)
		a=rs.AddPoint(x,y,z)
		rs.MoveObject(a,(random.uniform(-400,400),random.uniform(-200,200),random.uniform(-400,400)))
		print a
		listofpoint.append((x,y,z))

	rs.AddPolyline(listofpoint)

getcurves=rs.GetObjects("select curves",4)
for curve in getcurves:
	vector=(random.uniform(-10,10),random.uniform(-10,10),random.uniform(-10,10))
	copycurve=rs.CopyObject(curve,vector)
	rs.AddLoftSrf([curve,copycurve])
	divisionpoints=rs.DivideCurve(copycurve,10)
	x1=0
	y1=0
	z1=0
	t=0
	for point in divisionpoints:   
		print point
		rs.AddPoint(point)
		x1=x1+point[0]
		y1=y1+point[1]
		z1=z1+point[2]
		t=t+1
	avX=x1/t
	avY=y1/t
	avZ=z1/t
while avX>-100 and avX<100 and avY>-100 and avY<100 and avZ>-100 and avZ<100:
	newcurve=copycurve
	copycurve=rs.CopyObject(curve,vector)
	rs.AddLoftSrf([newcurve,copycurve])
	divisionpoints=rs.DivideCurve(copycurve,10)
	x1=0
	y1=0
	z1=0
	t=0
	for point in divisionpoints:   
		print point
		rs.AddPoint(point)
		x1=x1+point[0]
		y1=y1+point[1]
		z1=z1+point[2]
		t=t+1
	avX=x1/t
	avY=y1/t
	avZ=z1/t











	"""midpoint=rs.CurveMidPoint(copycurve)
				x=midpoint[0]
				y=midpoint[1]
				z=midpoint[2]"""

