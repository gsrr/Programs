import sys


def split(p):
        p1, p2 = p.split()
        return int(p1), int(p2)

def triangleArea(p1, p2, p3):
        a , b = split(p1)
        c , d = split(p2)
        e , f = split(p3)
        return abs(a * d + c * f + b * e - b * c - d * e - a * f)

while True:
        line = sys.stdin.readline().strip()
        if line == "":
                break
        num = int(line)
        points = []
        for i in range(num):
                point = sys.stdin.readline().strip()
                points.append(point)

        maxArea = 0
        for i in range(0, num):
                for j in range(i + 1, num):
                        for k in range(j + 1, num):
                                area = triangleArea(points[i], points[j], points[k])
                                if area > maxArea:                                        
                                        maxArea = area
        
        print "%.2f"%(float(maxArea/2.0))
                                                


