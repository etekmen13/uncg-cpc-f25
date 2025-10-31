import math
n,x = map(int,input().split())

points = []
for i in range(n):
    x,y,v = map(int, input().split())
    points.append((x,y,v))


points = sorted(points,key= lambda p: -math.atan2(p[1],p[0]-x))

# print points as csv format
for p in points:
    print(f"{p[0]},{p[1]}")

