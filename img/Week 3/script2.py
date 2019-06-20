import rhinoscriptsyntax as rs
import random
import math

def curve1(z):
	a=0
	b=0
	points=[]
	for t in range(0,314,2):
		a+=random.uniform(10,30)
		b+=random.uniform(30,40)
		x=a*math.cos(t)
		y=b*math.sin(t)
		rs.AddPoint(x,y,z)
		points.append((x,y,z))
	return rs.AddInterpCurve(points,3)


def curve2(z):
	a=0
	b=0
	points=[]
	for t in range(0,314):
		a+=random.uniform(90,100)
		b+=random.uniform(200,500)
		x=b*math.cos(t)
		y=a*math.sin(t)
		rs.AddPoint(x,y,z)
		points.append((x,y,z))
		
	return rs.AddInterpCurve(points,3)

for c in range(0,1000,15):
	if c%4==0:
		curve1(c)
	else:
		curve2(c)