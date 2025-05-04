class ADT:
    def __init__(self): # Constructor
        self.a = []

    def add(self, x):
        for item in self.a:
            if item == x:
                return 
        self.a.append(x)

    def remove(self, x):
        found = False
        for i in range(len(self.a)):
            if self.a[i] == x:
                del self.a[i]
                found = True
                break
        if not found:
            print(f"Element {x} not found in Set.")

    def union(self, other):
        result = []
        for item in self.a:
            result.append(item)
          
        for item in other.a:
            duplicate = False
            for res_item in result:
                if res_item == item:
                    duplicate = True
                    break
            if not duplicate:
                result.append(item)
        self.a = result
      

    def intersection(self, other):
        result = []
        for item in self.a:
            for other_item in other.a:
                if item == other_item:
                    result.append(item)
                    break
        self.a = result

    def diff(self, other):
        result = []
        for item in self.a:
            found = False
            for other_item in other.a:
                if item == other_item:
                    found = True
                    break
            if not found:
                result.append(item)
        self.a = result

    def display(self):
        return self.a

    def isSubset(self, other):
        for item in self.a:
            found = False
            for other_item in other.a:
                if item == other_item:
                    found = True
                    break
            if not found:
                return False
        return True

    def search(self, x):
        for item in self.a:
            if item == x:
                return True
        return False

    def size(self):
        count = 0
        for i in self.a:
            count += 1
        return count
      
