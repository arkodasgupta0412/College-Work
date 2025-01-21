import java.util.Scanner;

class Instructor {
    private String name;
    private String phoneNumber;

    static Instructor[] instructors = new Instructor[50];
    static int instructorCount = 0;

    public Instructor(String name, String phoneNumber) {
        this.name = name;
        this.phoneNumber = phoneNumber;
        if (instructorCount < 50) {
            instructors[instructorCount++] = this;
        } else {
            System.out.println("Instructor limit reached.");
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public static int getInstructorCount() {
        return instructorCount;
    }

    public static void displayAllInstructors() {
        for (int i = 0; i < instructorCount; i++) {
            System.out.println((i + 1) + ". Name: " + instructors[i].name + ", Phone: " + instructors[i].phoneNumber);
        }
    }
}

class TextBook {
    private String title;
    private String author;
    private String publisher;
    static TextBook[] textBooks = new TextBook[50];
    static int textBookCount = 0;

    public TextBook(String title, String author, String publisher) {
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        if (textBookCount < 50) {
            textBooks[textBookCount++] = this;
        } else {
            System.out.println("TextBook limit reached.");
        }
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getPublisher() {
        return publisher;
    }

    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    public static int getTextBookCount() {
        return textBookCount;
    }

    public static void displayAllTextBooks() {
        for (int i = 0; i < textBookCount; i++) {
            System.out.println((i + 1) + ". Title: " + textBooks[i].title + ", Author: " + textBooks[i].author + ", Publisher: " + textBooks[i].publisher);
        }
    }
}

class Course {
    private String courseName;
    private Instructor instructor;
    private TextBook textBook;

    static Course[] courses = new Course[50];
    static int courseCount = 0;

    public Course(String courseName, Instructor instructor, TextBook textBook) {
        this.courseName = courseName;
        this.instructor = instructor;
        this.textBook = textBook;
        if (courseCount < 50) {
            courses[courseCount++] = this;
        } else {
            System.out.println("Course limit reached.");
        }
    }

    public static int getCourseCount() {
        return courseCount;
    }

    public static void displayAllCourses() {
        for (int i = 0; i < courseCount; i++) {
            System.out.println((i + 1) + ". Course: " + courses[i].courseName);
            System.out.println("   Instructor: " + courses[i].instructor.getName());
            System.out.println("   TextBook: " + courses[i].textBook.getTitle());
        }
    }
}

class p8 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("\n--- University System Menu ---");
            System.out.println("1. Add Instructor");
            System.out.println("2. Add TextBook");
            System.out.println("3. Add Course");
            System.out.println("4. Display All Instructors");
            System.out.println("5. Display All TextBooks");
            System.out.println("6. Display All Courses");
            System.out.println("7. Exit");
            System.out.print("Enter your choice: ");

            int choice = sc.nextInt();
            sc.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter Instructor Name: ");
                    String instructorName = sc.nextLine();
                    System.out.print("Enter Instructor Phone Number: ");
                    String instructorPhone = sc.nextLine();
                    new Instructor(instructorName, instructorPhone);
                    break;
                case 2:
                    System.out.print("Enter TextBook Title: ");
                    String textBookTitle = sc.nextLine();
                    System.out.print("Enter Author Name: ");
                    String authorName = sc.nextLine();
                    System.out.print("Enter Publisher: ");
                    String publisher = sc.nextLine();
                    new TextBook(textBookTitle, authorName, publisher);
                    break;
                case 3:
                    if (Instructor.getInstructorCount() == 0 || TextBook.getTextBookCount() == 0) {
                        System.out.println("Please add at least one Instructor and one TextBook before adding a Course.");
                        break;
                    }
                    System.out.print("Enter Course Name: ");
                    String courseName = sc.nextLine();
                    System.out.println("Select Instructor:");
                    Instructor.displayAllInstructors();
                    int instructorIndex = sc.nextInt() - 1;
                    sc.nextLine();
                    System.out.println("Select TextBook:");
                    TextBook.displayAllTextBooks();
                    int textBookIndex = sc.nextInt() - 1;
                    sc.nextLine();
                    if (instructorIndex >= 0 && instructorIndex < Instructor.getInstructorCount()
                            && textBookIndex >= 0 && textBookIndex < TextBook.getTextBookCount()) {
                        new Course(courseName, Instructor.instructors[instructorIndex], TextBook.textBooks[textBookIndex]);
                    } else {
                        System.out.println("Invalid selections.");
                    }
                    break;
                case 4:
                    System.out.println("All Instructors:");
                    Instructor.displayAllInstructors();
                    break;
                case 5:
                    System.out.println("All TextBooks:");
                    TextBook.displayAllTextBooks();
                    break;
                case 6:
                    System.out.println("All Courses:");
                    Course.displayAllCourses();
                    break;
                case 7:
                    System.out.println("Thank You");
                    sc.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
