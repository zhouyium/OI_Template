from sys import stdin
input = lambda: stdin.readline().rstrip('\r\n')

class BIT:
    def __init__(self, n, func=lambda x, y: x + y):
        self.n = n + 1
        self.tree = [0]*self.n
        self.func = func

    def query(self, i):  # func(1, i)
        x = 0
        while i > 0:
            x = self.func(self.tree[i], x)
            i -= i & -i
        return x
    
    def update(self, i, x):  # 1-indexing
        while i < self.n:
            self.tree[i] = self.func(x, self.tree[i])
            i += i & -i