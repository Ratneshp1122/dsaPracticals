class HashTable:

    def __init__(self, size):
        self.dummy = -9999
        self.a = [self.dummy] * size

    def hashFunc(self, key):
        return key % len(self.a)

    def insert(self, key, method='linear'):
        index = self.hashFunc(key)
        print(f"Inserting {key} at index {index}...")

        if self.a[index] == self.dummy:
            self.a[index] = key
            print(f"Inserted at {index}")
        else:
            print(f"Collision at {index}")
            i = 1
            while True:
                if method == 'linear':
                    new_index = (index + i) % len(self.a)
                elif method == 'quadratic':
                    new_index = (index + i * i) % len(self.a)
                else:
                    raise ValueError("Unknown probing method.")
                if self.a[new_index] == self.dummy:
                    self.a[new_index] = key
                    print(f"Inserted at {new_index} using {method} probing")
                    break
                i += 1
                
if __name__ == "__main__":
    size = int(input("Enter Number of Entries: "))
    h = HashTable(size)
    for i in range(size):
        key = int(input(f"Enter Key {i+1}: "))
        method = input("Enter probing method (linear/quadratic): ").strip().lower()
        h.insert(key, method)
