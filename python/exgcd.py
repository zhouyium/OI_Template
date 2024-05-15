def extgcd(a, b):
  if b == 0:
    return 1, 0, a
    
  y, x, g = extgcd(b, a % b)
  y -= (a // b) * x
  
  return x, y, g


x, y = map(int, input().split())
a, b, g = extgcd(y, -x)

if abs(g) > 2:
  print(-1)
  exit()
  
print(a * 2 // g, b * 2 // g)