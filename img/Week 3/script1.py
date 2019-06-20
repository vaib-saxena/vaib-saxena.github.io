import rhinoscriptsyntax as rs
import random

def radical(y):
	x1=random.uniform(-10,10)
	z1=random.uniform(-10,10)

	x2=random.uniform(-20,20)
	z2=random.uniform(-20,20)

	x3=random.uniform(-3000,3000)
	z3=random.uniform(-3000,3000)

	x4=random.uniform(-40,40)
	z4=random.uniform(-40,40)

	x5=random.uniform(-50,50)
	z5=random.uniform(-50,50)

	listofpoints=[(x1,y,z1),(x2,y,z2),(x3,y,z3),(x4,y,z4),(x5,y,z5)]
	return rs.AddInterpCurve(listofpoints,3)

for c in range(100):
	aCurve=radical(c)
	if c==10:
		rs.MoveObject(aCurve, (random.uniform(1000,200),random.uniform(1000,200), random.uniform(1000,200)))