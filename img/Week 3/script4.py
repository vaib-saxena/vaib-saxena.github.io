import rhinoscriptsyntax as rs
import random

for c in range(200):
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
getpoints=rs.GetObjects("select points",1)

for curve in getcurves:
	alldistance=[]
	for point in getpoints:
		midpoint=rs.CurveMidPoint(curve)
		distance=rs.Distance(point,midpoint)
		alldistance.append(distance)
	pairing = zip(alldistance,getpoints)
	pairing.sort()
	firstpoint = pairing[0][1]
	rs.ExtrudeCurvePoint(curve,firstpoint)
