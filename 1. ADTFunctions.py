class adt:

  def __init__(self):
    self.a = set()

  def add(self,x):
    self.a.add(x)

  def remove(self,x):
    if(x in self.a):
        self.a.remove(x)
    else:
      print(f"Element {x} not found in Set.")

  def union(self,x):
    self.a = self.a | x.a

  def intersection(self,x):
    self.a = self.a & x.a

  def diff(self,x):
    self.a = self.a - x.a

  def display(self):
    return self.a

  def isSubset(self,x):
    return self.a.issubset(x.a)

  def search(self,x):
    return x in self.a

  def size(self):
    return len(self.a)
