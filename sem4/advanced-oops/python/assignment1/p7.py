import os

def findfiles(directory):
    file_paths = []
    
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            file_paths.append(file_path)
    
    return file_paths

def main():
    directory = input("Enter directory path to search: ")
    
    if not os.path.isdir(directory):
        print("Error: " + directory + " is not a valid directory")
        return
        
    files = findfiles(directory)
    
    print("\nFound " + str(len(files)) + " files:")
    for file in files:
        print(file)

if __name__ == "__main__":
    main()