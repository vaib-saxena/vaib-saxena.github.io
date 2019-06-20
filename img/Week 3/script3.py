import rhinoscriptsyntax as rs
import random
for c in range(50):
	listofpoint=[]
	for i in range(2):
		x=random.uniform(-200,200)
		y=random.uniform(-200,200)
		z=random.uniform(-300,300)
		listofpoint.append([x,y,z])
		
	rs.AddPolyline(listofpoint)

lines1=rs.GetObjects("select lines1")
lines2=rs.GetObjects("select lines2")
threshold=2000
for line1 in lines1:
	for line2 in lines2:
		mid1=rs.CurveMidPoint(line1)
		mid2=rs.CurveMidPoint(line2)
		if rs.Distance(mid1,mid2)<threshold:
			rs.AddLoftSrf([line1, line2])
