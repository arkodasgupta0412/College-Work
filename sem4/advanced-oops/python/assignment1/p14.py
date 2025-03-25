class PriorityQueue:
    def __init__(self):
        self.queue = []
    
    def push(self, item, priority):
        self.queue.append((priority, item))
        self.queue.sort(reverse=True, key=lambda x: x[0])
    
    def pop(self):
        if not self.is_empty():
            return self.queue.pop(0)[1]
        return None
    
    def peek(self):
        if not self.is_empty():
            return self.queue[0][1]
        return None
    
    def is_empty(self):
        return len(self.queue) == 0

def main():
    pq = PriorityQueue()
    while True:
        print("\nMenu:")
        print("1. Add item with priority")
        print("2. Pop highest priority item")
        print("3. Peek at highest priority item")
        print("4. Exit")
        choice = int(input("Enter choice: "))
        
        if choice == 1:
            item = input("Enter item: ")
            priority = int(input("Enter priority: "))
            pq.push(item, priority)
        elif choice == 2:
            item = pq.pop()
            if item is not None:
                print("Popped item:", item)
            else:
                print("Queue is empty.")
        elif choice == 3:
            item = pq.peek()
            if item is not None:
                print("Highest priority item:", item)
            else:
                print("Queue is empty.")
        elif choice == 4:
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()