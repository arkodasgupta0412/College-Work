#include <iostream>
#include <string>
#include <vector>
#define STU_ISSUE_LIMIT 2
#define FAC_ISSUE_LIMIT 10

class Book;
class Member;
class Student;
class Faculty;
class Transaction;
class BookList;
class MemberList;
class TransactionLog;
class Library;

enum Status
{
    PENDING,
    RETURNED
};

int generateTransactionId()
{
    static int id = 100;
    return id++;
}

class Book
{
    int b_id;
    int sno;
    int copy;
    std::string title;
    std::string author;
    std::string publisher;
    double price;

public:
    Book(int b_id, std::string title, std::string author, std::string publisher, double price, int sno, int copy)
        : b_id(b_id), title(title), author(author), publisher(publisher), price(price), sno(sno), copy(copy) {}

    int get_bookId() const
    {
        return b_id;
    }
    int get_copy() const
    {
        return copy;
    }
    int get_sno() const
    {
        return sno;
    }
    void set_copy(int x) { copy += x; }

    void show() const
    {
        std::cout << b_id << "\t\t\t" << title << "\t\t\t" << author << "\t\t\t" << publisher << "\t\t\t\t" << price << "\t\t\t" << sno << "\t\t\t" << copy << std::endl;
    }
};

class Member
{

protected:
    int m_id;
    std::string name;
    std::string email;
    std::string address;
    int issues;
    int type;

public:
    // Member() : issues(0) {}
    Member(int m_id, const std::string name, const std::string email, const std::string address, int type)
        : m_id(m_id), name(name), email(email), address(address), type(type), issues(0) {}

    virtual ~Member() = default;
    virtual bool checkIssueLimit(int) const = 0;
    void show(int);
    int get_memberId() const { return m_id; }
    int get_issues() const { return issues; }
    int get_type() const { return type; }
    void set_issue(int x) { issues += x; }
};

class Student : public Member
{
public:
    Student(int id, const std::string name, const std::string email, const std::string address, int type)
        : Member(id, name, email, address, type) {}

    bool checkIssueLimit(int issues) const override
    {
        return issues < STU_ISSUE_LIMIT;
    }
};

class Faculty : public Member
{
public:
    Faculty(int id, const std::string name, const std::string email, const std::string address, int type)
        : Member(id, name, email, address, type) {}

    bool checkIssueLimit(int issues) const override
    {
        return issues < FAC_ISSUE_LIMIT;
    }
};

class BookList
{
    std::vector<Book> blist;
    int uniqueBookCheck(int);

public:
    int searchBook(int);
    void addBook(void);
    void showBooks(void);
    friend class Transaction;
    friend void performTransaction(BookList &, MemberList &, TransactionLog &);
};

class MemberList
{
    std::vector<Member *> mlist;
    int uniqueMemberCheck(int);

public:
    int searchMember(int);
    void addMember(void);
    void showMembers(void);
    /* std::vector<Member *> getList(void)
    {
       return mlist;
    } */
    friend class Transaction;
    friend void performTransaction(BookList &, MemberList &, TransactionLog &);
};

class Transaction
{
    int t_id;
    int m_id;
    int b_id;
    int sno;
    int type;
    Status status;
    std::string date;

public:
    Transaction() {}
    Transaction(int m_id, int b_id, int sno, int type, Status status)
        : t_id(generateTransactionId()), m_id(m_id), b_id(b_id), sno(sno), type(type), status(status) {}

    bool operator==(Transaction &t)
    {
        return m_id == t.m_id && b_id == t.b_id && sno == t.sno && type == t.type && status == t.status;
    }

    // Declare performTransaction as a friend function
    friend void performTransaction(BookList &, MemberList &, TransactionLog &);

    Transaction generateTransactionSlip(BookList &, MemberList &);
    void showTransactionDetail();
    int get_memberId() const { return m_id; }
    void set_status(Status s) { status = s; }
};

class TransactionLog
{
    std::vector<Transaction> log;
    int searchLog(int);
    int empty() { return log.size() == 0; }

public:
    void addLog(Transaction &t) { log.push_back(t); }
    void updateLog(Transaction &t);
    void showTransaction(int); // show transaction history for a particular member
    void showLog();            // show entire log
};

/*                                      FUNCTION IMPLEMENTATIONS                                               */
void Member::show(int type)
{
    std::cout << m_id << "\t\t\t" << name << "\t\t\t" << email << "\t\t\t" << address << "\t\t\t";
    if (!type)
    {
        std::cout << issues << "\t\t\t" << STU_ISSUE_LIMIT << "\t\t\t" << "student\n";
    }
    else
    {
        std::cout << issues << "\t\t\t" << FAC_ISSUE_LIMIT << "\t\t\t" << "faculty\n";
    }
}

int BookList::uniqueBookCheck(int id)
{
    for (int i = 0; i < blist.size(); i++)
    {
        if (blist[i].get_bookId() == id)
        {
            return 0;
        }
    }
    return 1;
}

int BookList::searchBook(int id)
{
    for (int i = 0; i < blist.size(); i++)
    {
        if (blist[i].get_bookId() == id)
        {
            return i;
        }
    }
    return -1;
}

void BookList::addBook()
{
    int b_id, copy;
    std::string title, author, publisher;
    double price;

    std::cout << "Enter book id: ";
    std::cin >> b_id;
    std::cout << "Enter title: ";
    std::cin >> title;
    std::cout << "Enter author: ";
    std::cin >> author;
    std::cout << "Enter publisher: ";
    std::cin >> publisher;
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter number of copies: ";
    std::cin >> copy;

    if (uniqueBookCheck(b_id))
    {
        for (int i = 1; i <= copy; i++)
        {
            blist.push_back(Book(b_id, title, author, publisher, price, i, copy));
        }
    }
    else
        std::cout << "Book Id already exists!\n";
}

void BookList::showBooks()
{
    std::cout << "Book Id\t\t\tTitle\t\t\tAuthor\t\t\tPublisher\t\t\tPrice\t\t\tSno\t\t\tCopy\n";
    for (int i = 0; i < blist.size(); i++)
    {
        blist[i].show();
    }
}

int MemberList::uniqueMemberCheck(int id)
{
    for (int i = 0; i < mlist.size(); i++)
    {
        if (mlist[i]->get_memberId() == id)
        {
            return 0;
        }
    }
    return 1;
}

int MemberList::searchMember(int id)
{
    for (int i = 0; i < mlist.size(); i++)
    {
        if (mlist[i]->get_memberId() == id)
        {
            return i;
        }
    }
    return -1;
}

void MemberList::addMember()
{
    int m_id, type;
    std::string name, email, address;

    std::cout << "Enter member id: ";
    std::cin >> m_id;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter address: ";
    std::cin >> address;
    std::cout << "Student(0) / Faculty(1) ? ";
    std::cin >> type;

    if (uniqueMemberCheck(m_id))
    {
        if (type == 0)
            mlist.push_back(new Student(m_id, name, email, address, 0));
        else
            mlist.push_back(new Faculty(m_id, name, email, address, 1));
    }
    else
        std::cout << "Member Id already exists!\n";
}

void MemberList::showMembers()
{
    std::cout << "Member Id\t\tName\t\t\tEmail\t\t\tAddress\t\t\tIssues\t\t\tLimit\t\t\tType\n";
    for (int i = 0; i < mlist.size(); i++)
    {
        mlist[i]->show(mlist[i]->get_type());
    }
}

Transaction Transaction::generateTransactionSlip(BookList &book_rec, MemberList &member_rec)
{
    int m_id, b_id, type;
    Transaction invalid(0, 0, 0, 0, RETURNED);

    std::cout << "Enter member Id: ";
    std::cin >> m_id;

    int mIdx = member_rec.searchMember(m_id);

    if (mIdx != -1)
    {
        std::cout << "Enter 0 for issue, 1 for return: ";
        std::cin >> type;

        Member *member = member_rec.mlist[mIdx];

        if (!type)
        {
            if (!member->checkIssueLimit(member->get_issues()))
            {
                std::cout << "Issue limit reached. Please return pending books first.\n";
                return invalid;
            }

            std::cout << "Enter book id: ";
            std::cin >> b_id;

            int bIdx = book_rec.searchBook(b_id);

            if (bIdx != -1)
            {
                Book &book = book_rec.blist[bIdx];
                if (book.get_copy() <= 0)
                {
                    std::cout << "No copies available for this book.\n";
                    return invalid;
                }

                std::cout << "Transaction slip generated for issuing book.\n";
                return Transaction(m_id, b_id, book.get_sno(), type, PENDING);
            }

            else
            {
                std::cout << "Invalid book ID. Please check the book list.\n";
                return invalid;
            }
        }

        else if (type == 1)
        {
            std::cout << "Enter book Id and serial number: ";
            std::cin >> b_id >> sno;

            int bIdx = book_rec.searchBook(b_id);
            if (bIdx == -1)
            {
                std::cout << "Invalid book ID. Please check the book list.\n";
                return invalid;
            }

            std::cout << "Transaction slip generated for returning book.\n";
            return Transaction(m_id, b_id, sno, type, RETURNED);
        }
    }

    else
    {
        std::cout << "Invalid member ID. Please register first.\n";
        return invalid;
    }
}

void performTransaction(BookList &book_rec, MemberList &member_rec, TransactionLog &log)
{
    Transaction invalid(0, 0, 0, 0, RETURNED);

    Transaction slip = Transaction().generateTransactionSlip(book_rec, member_rec);
    if (slip == invalid)
    {
        std::cout << "Transaction slip has not been generated due to some error\n";
        return;
    }

    int mIdx = member_rec.searchMember(slip.m_id);
    int bIdx = book_rec.searchBook(slip.b_id);

    Member *member = member_rec.mlist[mIdx];
    Book &book = book_rec.blist[bIdx];

    if (slip.type == 0) // Issue transaction
    {
        member->set_issue(1);
        book.set_copy(-1);
        std::cout << "Book issued successfully.\n";
        log.addLog(slip);
    }
    else // Return transaction
    {
        member->set_issue(-1);
        book.set_copy(1);
        std::cout << "Book returned successfully.\n";
        log.updateLog(slip);
    }
}

void Transaction::showTransactionDetail()
{
    std::cout << t_id << "\t\t\t" << m_id << "\t\t\t" << b_id << "\t\t\t" << sno << "\t\t\t" << ((status == PENDING) ? "Pending" : "Returned") << std::endl;
}

int TransactionLog::searchLog(int m_id)
{
    for (int i = 0; i < log.size(); i++)
    {
        if (log[i].get_memberId() == m_id)
            return i;
    }
    return -1;
}

void TransactionLog::updateLog(Transaction &t)
{
    int k = searchLog(t.get_memberId());
    log[k].set_status(RETURNED);
}

void TransactionLog::showTransaction(int m_id)
{
    std::cout << "\nTransaction History for Member ID: " << m_id << std::endl;
    std::cout << "Transaction Id\t\t\tMember Id\t\t\tBook Id\t\t\tSno\t\t\tStatus\n";

    bool found = false;
    for (int i = 0; i < log.size(); i++)
    {
        if (log[i].get_memberId() == m_id)
        {
            log[i].showTransactionDetail();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No transactions found for the given Member ID.\n";
    }
}

void TransactionLog::showLog(void)
{
    std::cout << "\nFull Transaction Log\n";
    std::cout << "Transaction Id\tMember Id\tBook Id\tSerial No.\tStatus\n";

    if (log.empty())
    {
        std::cout << "No transactions logged yet.\n";
        return;
    }

    for (int i = 0; i < log.size(); i++)
    {
        log[i].showTransactionDetail();
    }
}

class Library
{
    BookList brec;
    MemberList mrec;
    TransactionLog log;

public:
    void run()
    {
        int choice;
        while (true)
        {
            std::cout << "\n========================= Library Management System =========================\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. Add Member\n";
            std::cout << "3. Transaction\n";
            std::cout << "4. Show Books\n";
            std::cout << "5. Show Members\n";
            std::cout << "6. Show Transaction History (Entire Log)\n";
            std::cout << "7. Show My Transaction History\n";
            std::cout << "8. Exit\n";
            std::cout << "================================================================================\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                brec.addBook();
                break;

            case 2:
                mrec.addMember();
                break;

            case 3:
                std::cout << "Verifying member and book...\n";
                performTransaction(brec, mrec, log);
                break;

            case 4:
                std::cout << "\n========================= List of Books =========================\n";
                brec.showBooks();
                break;

            case 5:
                std::cout << "\n========================= List of Members =========================\n";
                mrec.showMembers();
                break;

            case 6:
                std::cout << "\n========================= Transaction Log =========================\n";
                log.showLog();
                break;

            case 7:
            {
                std::cout << "\n========================= My Transaction History =========================\n";
                int memberId;
                std::cout << "Enter your Member ID: ";
                std::cin >> memberId;

                log.showTransaction(memberId);
                break;
            }

            case 8:
                std::cout << "\nExiting the system. Thank you for using the Library Management System!\n";
                return;

            default:
                std::cout << "\nInvalid choice! Please try again.\n";
            }
        }
    }
};

int main()
{
    Library lib;
    lib.run();
    return 0;
}