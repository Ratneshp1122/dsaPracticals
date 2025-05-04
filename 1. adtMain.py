from 1. ADTFunctions.py import ADT

def menu():
    print("\nMenu:")
    print("1. Add element to the set")
    print("2. Remove element from the set")
    print("3. Check if an element is present in the set")
    print("4. Get the size of the set")
    print("5. Get the union of two sets")
    print("6. Get the intersection of two sets")
    print("7. Get the difference of two sets")
    print("8. Check if a set is a subset of another set")
    print("9. To display set")
    print("9. Exit")
  set1 = ADT()
while True:
    menu()
    choice = int(input("Enter your choice: "))
    
    if choice == 1:
        element = input("Enter an element to add: ")
        set1.add(element)
        print(f"Updated set: {set1.a}")
    elif choice == 2:
        element = input("Enter an element to remove: ")
        set1.remove(element)
        print(f"Updated set: {set1.a}")
    elif choice == 3:
        element = input("Enter an element to search: ")
        found = set1.search(element)
        print(f"Element {'found' if found else 'not found'} in the set.")
    elif choice == 4:
        print(f"Size of the set: {set1.size()}")
    elif choice == 5:
        set2 = ADT()
        elements = input("Enter elements of the second set ").split(",")
        for elem in elements:
            set2.add(elem.strip())
        set1.union(set2)
        print(f"Union of sets: {set1.a}")
    elif choice == 6:
        set2 = ADT()
        elements = input("Enter elements of the second set").split(",")
        for elem in elements:
            set2.add(elem.strip())
        set1.intersection(set2)
        print(f"Intersection of sets: {set1.a}")
    elif choice == 7:
        set2 = ADT()
        elements = input("Enter elements of the second set").split(",")
        for elem in elements:
            set2.add(elem.strip())
        set1.difference(set2)
        print(f"Difference of sets: {set1.a}")
    elif choice == 8:
        set2 = ADT()
        elements = input("Enter elements of the second set ").split(",")
        for elem in elements:
            set2.add(elem.strip())
        is_subset = set1.subset(set2)
        print(f"Set1 is {'a' if is_subset else 'not a'} subset of Set2.")


    elif choice == 9:
        print(set1.display())


    elif choice == 10:
        break
    else:
        print("Invalid choice. Please try again.")
