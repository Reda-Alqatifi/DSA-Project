#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//! >>>>>>>>>>   D S A  _  P r o j e c t  -  M A I N   <<<<<<<<<<<<


//TODO - >>>>>>>>>>>>>>]  General  [<<<<<<<<<<<<<<

//* Section data
struct Section
{
    string name;
    int booksNum; //! to count the book inside the section

    int No; //! just to count them
};


///////

//* Book data
struct Book
{
    string title;
    string author;
    string code;
    string section;
    float price;
    int quantity;

    int No; //! just to count them
};


//////

//! Doubly Linked List for books
struct NodeBook
{
    Book book;

    NodeBook *next;
    NodeBook *previous;
};

struct DoublyLinkedList
{
    NodeBook *head;
};

DoublyLinkedList booksList = {NULL}; //! to intialize "head" of this object by "NULL"


//////

//! Linked List for sections
struct NodeSection
{
    Section section;

    NodeSection *next;
};

struct LinkedList
{
    NodeSection *head;
};

LinkedList sectionsList = {NULL}; //! to intialize "head" of this object by "NULL"


///////////////////////////////////////////////


//TODO - >>>>>>>>>>>>>>]  Functions  [<<<<<<<<<<<<<<


//! functions which gonna be used many times, and they dont belong to any of the above
struct GeneralFunctions
{
    //! Handeling Errors function - (not same data type imput)
    void handleErrors(int &choice)
    {
        while (cin.fail())
        {
            cout<<"\n>>>>] This option doesn't exist"<<endl;
            cin.clear();
            cin.ignore(1000 , '\n');

            cout<<"> Enter another option please : ";
            cin>>choice;
        }
    }

    //! To change the input case int Lower (small letters), very important in Searching
    void lowerCase(string &word)//* changes the orginal value
    {
        //! to make it Lower
        for (size_t Lower = 0 ; Lower < word.length() ; Lower++) 
        {
            if (word[Lower] >= 'A' && word[Lower] <= 'Z') 
            {
                word[Lower] = word[Lower] + ('a' - 'A');
            }
        }
    }

    //! to print a line from char you want
    //* recommended : length = 50  ,  symbol = '-'
    void printLine(int length , char symbol)
    {
        cout<<string(length, symbol)<<endl;
    }
    
    //! to stop the screen till the user click 'Enter'
    void pause()
    {
        cout<<"\n> Press Enter to continue...";
        cin.ignore();
        cin.get();

        cout<<endl;
        printLine(50 , '-');
    }

    //! To update the  number "No" of the node, usually we use it befor displaying
    /* caller is  Section or Book */
    void updateNo(const string &caller)
    {
        if(caller == "Book")
        {
            int i = 1;
            for (NodeBook *temp = booksList.head ; temp != NULL ; temp = temp->next)
            {
                temp->book.No = i;
                i++;
            }
        }
        else //! for Section
        {
            int i = 0;
            for (NodeSection *temp = sectionsList.head ; temp != NULL ; temp = temp->next)
            {
                temp->section.No = i;
                i++;
            }
        }
    }

    //! Clear memory leak for ponters
    //TODO - We will just use it one time, in the end of the "main()"
    void clearMemoryLeak()
    {
        //! for books :
        NodeBook *currentBook = booksList.head;
        while (currentBook != NULL)
        {
            NodeBook *nextNode = currentBook->next;
            delete currentBook;
            currentBook = nextNode;
        }
        booksList.head = NULL;

        //////

        //! for sections :
        NodeSection *currentSection = sectionsList.head;
        while (currentSection != NULL)
        {
            NodeSection *nextNode = currentSection->next;
            delete currentSection;
            currentSection = nextNode;
        }
        sectionsList.head = NULL;
    }

    //! to put a text in the miidle of a space
    string centerText(const string &text , int width)
    {
        int leftSpace = (width - text.length()) / 2;
        int rightSpace = width - text.length() - leftSpace;

        return string(leftSpace , ' ') + text + string(rightSpace , ' ');
    }

    //! to make the 1st letter of every word in a text  in "Upper case" , useful for display
    string UpperCaseFirstLetter(string text) //* doesn't change the orginal value
    {
        bool Upper = true;

        for (size_t i = 0 ; i < text.length() ; i++)
        {
            if (text[i] == ' ') // * or isspace(words[i])
            {
                Upper = true;
            }
            else
            {
                if (Upper)
                {
                    text[i] = toupper(text[i]);
                    Upper = false;
                }
                else
                {
                    text[i] = tolower(text[i]);
                }
            }
        }

        return text;
    }
};

GeneralFunctions generalFunctions; //* Global Object to use anywhere


//////////////////////////////////////


struct TotalFunctions //! DONE
{
    int totalBooks()
    {
        int count = 0;
        for (NodeBook* temp = booksList.head; temp != NULL; temp = temp->next)
            count++;
        return count;
    }

    int totalSections()
    {
        int count = 0;
        for (NodeSection* temp = sectionsList.head; temp != NULL; temp = temp->next)
            count++;
        return count;
    }

    int totalBooksInSection(const string& sectionName)
    {
        int count = 0;
        for (NodeBook* temp = booksList.head; temp != NULL; temp = temp->next)
        {
            if(temp->book.section == sectionName || 
               (sectionName == "Neither" && temp->book.section.empty()))
                count++;
        }
        return count;
    }

    void showDetailedSummary()
    {
        TotalFunctions total;
        cout << "\n" << string(50, '=') << endl;
        cout << "|" << generalFunctions.centerText("LIBRARY SUMMARY", 48) << "|" << endl;
        cout << string(50, '=') << endl;
        cout << "| " << setw(30) << left << "Total Sections" 
             << ": " << setw(14) << left << total.totalSections() << " |" << endl;
        cout << "| " << setw(30) << left << "Total Books" 
             << ": " << setw(14) << left << total.totalBooks() << " |" << endl;
        cout << string(50, '-') << endl;
        
        //! Show books per section
        for (NodeSection* temp = sectionsList.head; temp != NULL; temp = temp->next)
        {
            cout << "| " << setw(30) << left << ("Books in " + temp->section.name) 
                 << ": " << setw(14) << left << temp->section.booksNum << " |" << endl;
        }
        cout << string(50, '=') << endl;
    }

    void totalMenu()
    {
        int choice;

        do
        {
            cout << "\n" << string(50, '=') << endl;
            cout << "|" << generalFunctions.centerText("Total Menu", 48) << "|" << endl;
            cout << string(50, '=') << endl;
            cout << "| " << setw(46) << left << "1 - Total amount of books." << " |" << endl;
            cout << "| " << setw(46) << left << "2 - Total amount of sections." << " |" << endl;
            cout << "| " << setw(46) << left << "3 - Detailed library summary." << " |" << endl;
            cout << "| " << setw(46) << left << "4 - Back to the Main Menu." << " |" << endl;
            cout << string(50, '=') << endl;
            cout << "\n> Enter Your Choice : ";

            cin >> choice;
            generalFunctions.handleErrors(choice);

            switch(choice)
            {
                case 1:
                    cout << "\n>>> Total Books in Library: " << totalBooks() << endl;
                    generalFunctions.pause();
                    break;

                case 2:
                    cout << "\n>>> Total Sections in Library: " << totalSections() << endl;
                    generalFunctions.pause();
                    break;

                case 3:
                    showDetailedSummary();
                    generalFunctions.pause();
                    break;

                case 4:
                    return;

                default:
                    cout << "\n>>> Wrong Entry! Please try again.\n";
                    generalFunctions.pause();
                    break;
            }


        } while(choice != 4);
    }
};


//////////////


struct DisplayFunctions //! DONE
{
    //! Print table header for books
    void printBooksHeader()
    {
        cout << endl;
        generalFunctions.printLine(91 , '=');
        cout << "| " << setw(3) << left << "No." 
             << "| " << setw(20) << left << "Title"
             << "| " << setw(15) << left << "Author"
             << "| " << setw(10) << left << "Code"
             << "| " << setw(12) << left << "Section"
             << "| " << setw(7)  << left << "Price"
             << "| " << setw(8)  << left << "Quantity |\n";
        generalFunctions.printLine(91 , '=');
    }

    //! Print all books in formatted table
    void displayBooks()
    {
        generalFunctions.updateNo("Book");

        if(booksList.head == NULL)
        {
            cout << "\n>>> There are no books in the library!\n";
            return;
        }

        printBooksHeader();

        for (NodeBook* temp = booksList.head; temp != NULL; temp = temp->next)
        {
            cout << "| " << setw(3) << left << temp->book.No
                 << "| " << setw(20) << left << 
                 (temp->book.title.length() > 20 ? temp->book.title.substr(0, 17) + "..." : temp->book.title)
                 << "| " << setw(15) << left << 
                 (temp->book.author.length() > 15 ? temp->book.author.substr(0, 12) + "..." : temp->book.author)
                 << "| " << setw(10) << left << temp->book.code
                 << "| " << setw(12) << left << temp->book.section
                 << "| $" << setw(6) << left << fixed << setprecision(2) << temp->book.price
                 << "| " << setw(9) << left << temp->book.quantity << "|\n";
        }

        generalFunctions.printLine(91 , '=');
    }

    //! Print table header for sections
    void printSectionsHeader()
    {
        generalFunctions.printLine(36 , '=');
        cout << "| " << setw(3) << left << "No." 
             << "| " << setw(20) << left << "Section Name" 
             << "| " << setw(6) << left << "Books" << "|\n";
        generalFunctions.printLine(36 , '=');
    }

    //! Display all sections
    void displaySections()
    {
        generalFunctions.updateNo("Section");

        if(sectionsList.head == NULL)
        {
            cout << "\n>>> There are no sections yet!\n";
            return;
        }

        printSectionsHeader();

        for (NodeSection* temp = sectionsList.head; temp != NULL; temp = temp->next)
        {
            cout << "| " << setw(3) << left << temp->section.No
                 << "| " << setw(20) << left << temp->section.name
                 << "| " << setw(6) << left << temp->section.booksNum << "|\n";
        }

        generalFunctions.printLine(36 , '=');
    }

    //! Display menu
    void displayMenu()
    {
        cout << "\n" << string(50, '=') << endl;
        cout << "|" << generalFunctions.centerText("Display Menu", 48) << "|" << endl;
        cout << string(50, '=') << endl;
        cout << "| " << setw(46) << left << "1 - Display books." << " |" << endl;
        cout << "| " << setw(46) << left << "2 - Display sections." << " |" << endl;
        cout << "| " << setw(46) << left << "3 - Back to the Main Menu." << " |" << endl;
        cout << string(50, '=') << endl;
        cout << "\n> Enter Your Choice : ";
    }

    //! Menu choice loop
    void displayMenuChoice()
    {
        int choice;

        do
        {
            displayMenu();
            cin >> choice;
            generalFunctions.handleErrors(choice);

            switch(choice)
            {
                case 1:
                    displayBooks();
                    generalFunctions.pause();
                    break;
                
                case 2:
                    displaySections();
                    generalFunctions.pause();
                    break;
                
                case 3:
                    return;

                default:
                    cout << "\n>>> Wrong Entry! Please try again.\n";
                    generalFunctions.pause();
                    break;
            }

        } while(choice != 3);
    }
};

DisplayFunctions displayFunctions; //* Global Object to use anywhere


///////////////


struct SortFunctions //! DONE
{

    //TODO - "Sort ( Merge Sort )" :
    
    //! to split the list into tow lists from the middle
    void splitList(NodeBook *head , NodeBook **firstHalf , NodeBook **secondHalf)
    {
        //! to find the middle of the list
        NodeBook *slow = head; //* move  one step
        NodeBook *fast = head->next; //* move  tow steps

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next; //! it will stop at the middle of the list
            fast = fast->next->next;
        }

        *firstHalf = head;
        *secondHalf = slow->next; //! the 2nd half will start after the mid of the whole list
        
        //! to break the links betwean the 1st half and the 2nd half
        if (slow->next != NULL)
        {
            slow->next->previous = NULL;
        }
        slow->next = NULL;
    }

    //! to 'merge' and 'sort' the lists,
    /* caller is :  title , code , author , section , price , or quantity */
    NodeBook *sortedMerge(NodeBook *ListA , NodeBook *ListB , const string &caller)
    {
        //! to stop the 'recursion' if one list reaches its end
        if (ListA == NULL)
        {
            return ListB;
        }
        if (ListB == NULL)
        {
            return ListA;
        }

        NodeBook *result = NULL; //! The head of the merged list

        bool compare; //! to compare the '1st list' with the '2nd list'

        //* sort them by smaller to greator only
        if (caller == "title")
            compare = ListA->book.title < ListB->book.title;

        else if (caller == "code")
            compare = ListA->book.code < ListB->book.code;

        else if (caller == "author")
            compare = ListA->book.author < ListB->book.author;

        else if (caller == "price")
            compare = ListA->book.price < ListB->book.price;

        else if (caller == "quantity")
            compare = ListA->book.quantity < ListB->book.quantity;

        else //! section
            compare = ListA->book.section < ListB->book.section;


        //! if compare is 'true' ( ListA  <  ListB )
        if (compare)
        {
            result = ListA;
            result->next = sortedMerge(ListA->next , ListB , caller); //! mrege recursivly

            if (result->next != NULL)
            {
                result->next->previous = result;
            }
            result->previous = NULL; //! the previous of the head of the list
        }
        else //! if compare is 'false' ( ListA  >  ListB )
        {
            result = ListB;
            result->next = sortedMerge(ListA , ListB->next , caller); //! mrege recursivly

            if (result->next != NULL)
            {
                result->next->previous = result; //! to link the nodes' previous pointer
            }
            result->previous = NULL; //! the previous of the head of the list
        }

        return result; 
    }

    //! to manage every operations recursivly
    /* caller is :  title , code , author , section , price , or quantity */
    void mergeSort(NodeBook **head , const string &caller)
    {
        
        //! if it is  empty  or  it has only one element
        if (head == NULL || *head == NULL || (*head)->next == NULL)
        {
            return;
        }
        
        NodeBook *firstHalf;
        NodeBook *secondHalf;

        splitList(*head , &firstHalf , &secondHalf); //! to split the list into tow lists

        mergeSort(&firstHalf , caller); //! to split the 1st half till it has only one node
        mergeSort(&secondHalf , caller); //! to split the 2nd half till it has only one node

        //! to sort the nodes from each half and merge them together
        *head = sortedMerge(firstHalf , secondHalf , caller);
    }

    /////////////////////////
    
    //TODO - "Menu" :

    void menuSort() //! Add functions menu
    {
        cout << endl;
        generalFunctions.printLine(60, '=');
        cout << "|" << generalFunctions.centerText("Sort Menu", 58) << "|" << endl;
        generalFunctions.printLine(60, '-');

        cout << "| " << setw(57) << left << "1 - Sort by { Title }." << "|" << endl;
        cout << "| " << setw(57) << left << "2 - Sort by { Code }." << "|" << endl;
        cout << "| " << setw(57) << left << "3 - Sort by { Author }." << "|" << endl;
        cout << "| " << setw(57) << left << "4 - Sort by { Section }." << "|" << endl;
        cout << "| " << setw(57) << left << "5 - Sort by { Price }." << "|" << endl;
        cout << "| " << setw(57) << left << "6 - Sort by { Quantity }." << "|" << endl;
        cout << "| " << setw(57) << left << "7 - Back to the Main Menu. " << "|" << endl;

        generalFunctions.printLine(60, '=');

        /////////////////////////////////////

        cout << "\n> Enter your choice : ";
    }
    void menuSortChoice() //! Loop to choese which you want to add
    {
        Section section;
        Book book;
        
        int choice;
        do
        {
            menuSort();
            cin>>choice;
            
            generalFunctions.handleErrors(choice); 

            switch (choice)
            {
                case 1: //! Sort by Title
                    mergeSort(&booksList.head , "title");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;
                
                case 2: //! Sort by Code
                    mergeSort(&booksList.head , "code");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;

                case 3: //! Sort by Author
                    mergeSort(&booksList.head , "author");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;
                
                case 4: //! Sort by Section
                    mergeSort(&booksList.head , "section");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;
                
                case 5: //! Sort by Price
                    mergeSort(&booksList.head , "price");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;

                case 6: //! Sort by Quantity
                    mergeSort(&booksList.head , "quantity");
                    displayFunctions.displayBooks();
                    generalFunctions.pause();
                    break;

                case 7://! Return to thw main menu
                    return;
                
                default:
                    cout<<"\n* Wrong Entry! please try again!"<<endl;
                    break;
            }

            generalFunctions.printLine(50 , '-'); //! print a Line between each option

        } while (choice != 7);
        
    }
};


///////////////


struct AddFunctions //!  DONE
{
    //TODO - Add "Sections" :

    void insertSectionNode(Section data) //! to Create a new section Node
    {
        if (data.name.empty()) //* to not insert an empty section at a node
        {
            return;
        }
        
        NodeSection *newNode;
        newNode = new NodeSection; //! or    newNode = new Node();
        newNode->section = data;

        if(sectionsList.head == NULL) //! 1st node
        {
            sectionsList.head = newNode;
            newNode->next = NULL;
        }
        else //! other nodes
        {
            NodeSection *last;
            last = sectionsList.head;

            while(last->next != NULL)
            {
                last = last->next;
            }
            last->next = newNode;
            newNode->next = NULL;
        }
    }
    
    //! Const sections, that the user will have since the beginning
    void baseConstSections() 
    {
        const int SIZE = 4;
        Section sections[SIZE];

        sections[0].name = "Neither"; //! if not from any section
        sections[0].No = 0;
        sections[0].booksNum = 0;
        
        sections[1].name = "Fiction";
        sections[1].No = 1;
        sections[1].booksNum = 0;

        sections[2].name = "Acadimic";
        sections[2].No = 2;
        sections[2].booksNum = 0;

        sections[3].name = "Business";
        sections[3].No = 3;
        sections[3].booksNum = 0;

        for (int i = 0 ; i < SIZE ; i++)
        {
            insertSectionNode(sections[i]); //! to insert them into the node
        }
    }

    //! display entire sections, caller is  Book or Section
    void sectionsDisplay(const string &caller) 
    {
        NodeSection *current;
        current = sectionsList.head;

        if (sectionsList.head == NULL) //! no nodes
        {
            cout << "There is no sections yet!" << endl;
        }
        else //! have nodes
        {
            generalFunctions.updateNo("Section"); //! to update the section's number "No"
            
            while (current != NULL)
            {
                if(caller == "Book") //! for 'books' adding process
                {
                    cout << current->section.No << " - " << current->section.name;
                    if(current->next != NULL)
                    {
                        cout<<" , ";
                    }
                }
                else //! for 'sections' adding process
                {
                    cout << current->section.No << " - " << current->section.name 
                        << "." << endl;
                }
                

                current = current->next;
            }
        }
    }
    void writeSection(Section &data) //! To write a new Section name
    {
        string answer;

        //! section Name:
        cout << "> Enter the Section Name : ";
        cin.ignore();
        getline(cin , answer);
        
        string answerCopy = answer;
        generalFunctions.lowerCase(answerCopy); //!to lower the copy 'not changing the value'


        NodeSection *current;
        current = sectionsList.head;

        bool same = false; // to check if the typed value ame as another value of the list
        while(current != NULL)
        {
            string temp = current->section.name; //! a copy for the nodes value
            generalFunctions.lowerCase(temp); //! to lower it without change the orginal node

            if(answerCopy == temp) // if the user type a section which is already in the list
            {
                cout << "\nyou have this section already!" << endl;
                
                data.name.clear(); //! to not insert it at a node
                same = true;
                return;
            }
            
            current = current->next;
        }
        
        if(!same) // if the input has a uniqe name 
        {
            data.name = answer;
            data.booksNum = 0; //! to intialaize its number of books
            
            cout << "* Section has been added successfully!" << endl;
        }

    }
    
    void connectSectionsAdding(Section &data) //! To connect section add Functions togethor
    {
        writeSection(data);

        //! to check if we have a reppeted section and not insert it at a node
        if(data.name.empty())
        {
            return;
        }
        else
        {
            insertSectionNode(data);
        }
        
    }
    
    void inputSectionLoop(Section &data ) //! To handle the adding in a loop
    {
        string choice;
        
        do
        {
            cout << "\nSections you have :" << endl;
            sectionsDisplay("Section"); //! To display the emtire sections for sections

            cout << "\nDo you want to add another section ( yes / no ) ?  ";
            cin >> choice;
            generalFunctions.lowerCase(choice); //! to make it lower case

            if (choice == "yes" || choice == "y")
            {
               connectSectionsAdding(data);
            }
            else if (choice == "no" || choice == "n")
            {
                cout << "Ok!" << endl;
                return;
            }
            else
            {
                cout << "Wrong Entry! Please Try Again." << endl;
            }

        } while (choice != "no" && choice != "n");

    }

    /////////

    //TODO - Add "Books" :

    void insertBookNode(Book data) //! to Create a new book Node
    {
        NodeBook *newNode;
        newNode = new NodeBook; //! or    newNode = new Node();
        newNode->book = data;

        if(booksList.head == NULL) //! no nodes
        {
            booksList.head = newNode;
            newNode->next = NULL;
            newNode->previous = NULL;
        }
        else //! other nodes
        {
            NodeBook *last;
            last = booksList.head;

            while(last->next != NULL)
            {
                last = last->next;
            }
            last->next = newNode;
            newNode->next = NULL;
            newNode->previous = last;
        }
    }
    
    void writeBook(Book &data , int &counter) //! To write a new Book details
    {
        //! Title:
        cout << "> Title : ";
        
        string answerTitle , answerTitleCopy;
        
        cin.ignore();
        getline(cin , answerTitle);
        
        answerTitleCopy = answerTitle; // to check without changing the orginal title
        generalFunctions.lowerCase(answerTitleCopy); //! to lower it


        NodeBook *currentBook;
        currentBook = booksList.head;

        bool same = false; // to check if the typed value ame as another value of the list
        while (currentBook != NULL)
        {
            string temp = currentBook->book.title; //! a copy for the nodes value
            generalFunctions.lowerCase(temp); //! to lower it without change the orginal node

            if(answerTitleCopy == temp)//if the user type section which already in the list
            {
                cout << "\nyou have this book already!" << endl;
                same = true;
                
                data.title.clear(); //! to not insert it at a node
                counter--; //! to reevaluate the counter to its correct value
                return;
            }
            
            currentBook = currentBook->next;
        }
        
        if(!same) // if the input has a uniqe title 
        {
            data.title = answerTitle;
        }
        

        //! Author :
        cout << "> Author : ";
        getline(cin , data.author);
        

        //! Code :
        cout << "> Code : ";
        string answerCode;
        cin >> answerCode;

        currentBook = booksList.head;

        same = false; // to check if the typed value ame as another value of the list
        while (currentBook != NULL)
        {
            string temp = currentBook->book.code; //! a copy for the nodes value

            if(answerCode == temp) // if the user type a section which is already in the list
            {
                cout << "\nyou have a book with this code already!" << endl;
                cout << "Pleaes, Try Again!" << endl;

                cout << "> Code : ";
                cin >> data.code;
                same = true;
                break;
            }
            
            currentBook = currentBook->next;
        }
        
        if(!same) // if the input has a uniqe title 
        {
            data.code = answerCode;
        }


        //! Section :
        cout << "> Section ( ";

        sectionsDisplay("Book"); //! to display the entire sections but for books
        
        cout << " ) - (Write a Number) : ";
        
        NodeSection *currentSection;
        currentSection = sectionsList.head;
        
        int sectionNum;
        cin >> sectionNum;

        generalFunctions.handleErrors(sectionNum); 

        same = false;
        while (currentSection != NULL)
        {
            if(sectionNum == currentSection->section.No) //! to equalize data with the node
            {
                if(sectionNum == sectionsList.head->section.No) //!to consider it 'Neither'
                {
                    data.section.clear();
                    sectionsList.head->section.booksNum++;
                    same = true;
                }
                else
                {
                    data.section = currentSection->section.name;
                    currentSection->section.booksNum++;
                    same = true;
                }
                

                break;
            }

            currentSection = currentSection->next;
        }

        if(!same) //! If the choice doesn't from the entire section
        {
            data.section.clear();
            sectionsList.head->section.booksNum++; //! to consider them 'Neither'
        }
        

        //! Price :
        cout << "> Price ($) : ";
        cin >> data.price;

        //* we didn't use the function "handleErrors" because it just recieves integers.
        while (cin.fail())
        {
            cout<<"\n>>>>] This option doesn't exist"<<endl;
            cin.clear();
            cin.ignore(1000 , '\n');

            cout<<"> Enter another option please : ";
            cin >> data.price;
        } 
        
        
        //! Availible Quantity :
        cout << "> Availible Quantity : ";
        cin >> data.quantity;
        
        generalFunctions.handleErrors(data.quantity); 

        //! No :
        data.No = counter;
    }

    //!To connect book add Functions togethor
    void connectBooksAdding(Book &data , int &counter)
    {
        writeBook(data , counter);
        
        //! to check if we have a reppeted title and not insert at a node
        if(data.title.empty())
        {
            return;
        }
        else
        {
            insertBookNode(data);
        }
        
    }

    void inputBookLoop(Book &data ) //! To handle the adding in a loop
    {
        string choice = "yes";

        //! to count books
        int counter = 1;
        for (NodeBook *temp = booksList.head ; temp != NULL ; temp = temp->next)
        {
            temp->book.No = counter;
            counter++;
        }

        do
        {
            if (choice == "yes" || choice == "y")
            {
                generalFunctions.printLine(50 , '-');
                cout << "\nEnter The Book number [ " << counter << " ] details.\n\n";
                connectBooksAdding(data , counter);

                counter++;
            }
            else if (choice != "no" && choice != "n" && choice != "yes" && choice != "y")
            {
                cout << "Wrong Entry! Please Try Again." << endl;
            }

            cout << "\nDo you want to add another book ( yes / no ) ? ";
            cin >> choice;
            generalFunctions.lowerCase(choice);

            if (choice == "no" || choice == "n")
            {
                cout << "Ok!" << endl;
                return;
            }

        } while (choice != "no" && choice != "n");

    }
    
    /////////////////////////
    
    //TODO - "Menu" :

    void menuAdd() //! Add functions menu
    {
        cout<<endl;
        generalFunctions.printLine(60 , '=');
        cout<<"|"<<generalFunctions.centerText("Add Menu", 58)<<"|"<<endl;
        generalFunctions.printLine(60 , '-');

        cout<<"| "<<setw(57)<<left<<"1 - Add a new book."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"2 - Add a new section."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"3 - Back to the Main Menu. "<<"|"<<endl;

        generalFunctions.printLine(60 , '=');

        /////////////////////////////////////

        cout<<"\n> Enter your choice : ";
    }
    void menuAddChoice() //! Loop to choese which you want to add
    {
        Section section;
        Book book;
        
        int choice;
        do
        {
            menuAdd();
            cin>>choice;

            generalFunctions.handleErrors(choice); 

            switch (choice)
            {
                case 1: //! Add book
                    inputBookLoop(book);
                    break;
                
                case 2: //! Add Section
                    inputSectionLoop(section);
                    break;

                case 3://! Return to thw main menu
                    return;
                
                default:
                    cout<<"\n* Wrong Entry! please try again!"<<endl;
                    break;
            }

            generalFunctions.printLine(50 , '-'); //! print a Line between each option

        } while (choice != 3);
        
    }
};


///////////////


struct UpdateFunctions
{

};


///////////////


struct SearchFunctions
{

};


///////////////


struct RemoveFunctions //! DONE
{
    //TODO - Remove "Books" :
    
    //! to remove the node 'book'
    void removeBook( NodeBook *book)
    {
        if (booksList.head == NULL) //! no Nodes
        {
            cout << "\nThere is no books!\n" << endl;
            return;
        }

        //! to update books counter inside the section
        for (NodeSection *temp = sectionsList.head ; temp != NULL ; temp = temp->next)
        {
            if (book->book.section == temp->section.name)
            {
                temp->section.booksNum--;
                break;
            }
            else if (book->book.section.empty() && temp == sectionsList.head)
            {
                temp->section.booksNum--;
                break;
            }
        }

        if (book == booksList.head ) //! firstst Node
        {
            booksList.head = booksList.head->next;
            if(booksList.head != NULL) //! if only one node
            {
                booksList.head->previous = NULL;
            }   
            book->next = NULL;
            
            delete book;
        }
        else if (book->next == NULL) //! last Node
        {
            book->previous->next = NULL;
            book->previous = NULL;

            delete book;
        }
        else //! other Nodes
        {
            book->previous->next = book->next;
            book->next->previous = book->previous;
            book->previous = NULL;
            book->next = NULL;

            delete book;
        }
    }

    //! to search about the book we want to remove
    bool searchToRemove(string code , string section)
    {
        NodeBook *book = booksList.head;
        while (book != NULL)
        {
            NodeBook *nextNode = book->next;

            if (code == book->book.code)
            {
                removeBook(book);
                generalFunctions.updateNo("Book"); //! to update books 'No'

                return true;
            }
            
            book = nextNode;
        }
           
        return false;
    }
    
    //////////////

    //TODO - Remove "Section" :
    
    //! to remove the node 'section'
    void removeSection(NodeSection *current , string &section)
    {
        if (sectionsList.head == NULL) //! no Nodes
        {
            cout << "\nThere is no sections!\n" << endl;
            return;
        }

        if (current == sectionsList.head ) //! firstst Node
        {
            cout << "\nYou cant delete this section!" << endl;
            section = "protected";
            return;
        }
        else if (current->next == NULL) //! last Node
        {
            //! to delete the orginal books
            NodeBook *book = booksList.head;
            while (book != NULL)
            {
                NodeBook *nextNode = book->next;
                
                if (book->book.section == current->section.name)
                {
                    removeBook(book);
                }

                book = nextNode;
            }

            //! to delete the section
            NodeSection *temp = sectionsList.head;
            while (temp->next->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = NULL;

            delete current;
        }
        else //! other Nodes
        {
            //! to delete the orginal books
            NodeBook *book = booksList.head;
            while (book != NULL)
            {
                NodeBook *nextNode = book->next;
                
                if (book->book.section == current->section.name)
                {
                    removeBook(book);
                }

                book = nextNode;
            }
            
            //! to delete the section
            NodeSection *temp = sectionsList.head;
            while (temp->next != current)
            {
                temp = temp->next;
            }
            
            temp->next = current->next;
            current->next = NULL;

            delete current;
        }
    }

    /////////////

    //! to get the section from the number instade of its name. (for both section and book)
    /*caller is to decide if it is for removing 'book' or 'section' */
    string sectionsLoopToRemove(string &section , const string &caller)
    {
        NodeSection *current;
        
        int counter , secNo;
        do
        {    
            
            if (caller == "book") //! for book
            {
                if (booksList.head == NULL)
                {
                    cout << "\nthere is no books!" << endl;
                    generalFunctions.pause();
                    return section;
                }
                cout << "\n> Enter the Section [ No. ] you want to remove from : ";
            }
            else //! for section
            {
                cout << "\nSections you have :\n" << endl;

                AddFunctions Add;
                Add.sectionsDisplay("Section");

                cout << "\n> Enter the Section [ No. ] you want to remove : ";
            }
            
            cin >> secNo;
            generalFunctions.handleErrors(secNo);

            current = sectionsList.head;
            counter = 0;     
            while (current != NULL)
            {
                NodeSection *nextNode = current->next;
                if (secNo == current->section.No)
                {
                    section = current->section.name;
                    
                    if(caller != "book") //! to remove section
                    {
                        removeSection(current , section);
                        return section;
                    }
                    
                    return section;
                }

                counter++;
                current = nextNode;
            }

            if (secNo < 0 || secNo > counter)
            {
                cout << "Wrong Entry! Please, Try Again!" << endl;
                continue;
            }

        } while (secNo < 0 || secNo > counter);
        
    }

    //! to let the user write the book information.
    void writeToRemove(const string &caller)
    {
        string choice , code , section;
        AddFunctions Add;

        do
        {
            if (caller == "book") //! for book
            {
                cout << "\nBooks you have : "<<endl;
                displayFunctions.displayBooks();

                cout << "\nSections you have :\n "<<endl;
                Add.sectionsDisplay("Section");
                
                //! to ask about section he wants to remove from
                sectionsLoopToRemove(section , "book"); 

                if (booksList.head == NULL)
                {
                    return;
                }

                cout << "> Enter The book [ Code ] to remove : ";
                cin >> code;

                if (searchToRemove(code , section))
                {
                    cout << "\nThe book with the code [ " << code
                        << " ] has been removed successfully!" << endl;
                }
                else
                {
                    cout << "\nThere is no book with the code [ " << code
                        << " ] in the section '" << section << "'!" << endl;
                }

                cout << "Do you want to remove another book ( yes / no ) ? ";
            }
            else //! for section
            {
                sectionsLoopToRemove(section , "section");

                if (section != "protected")
                {
                    cout << "\nThe section [ " << section
                        << " ] with its all books have been removed successfully!" << endl;
                }

                cout << "Do you want to remove another section ( yes / no ) ? ";
            }
            
            cin >> choice;
            generalFunctions.lowerCase(choice);
            generalFunctions.printLine(50 , '-');

        } while (choice != "no" && choice != "n");
        
    }

    /////////////////////////
    
    //TODO - "Menu" :

    void menuRemove() //! Add functions menu
    {
        cout<<endl;
        generalFunctions.printLine(60 , '=');
        cout<<"|"<<generalFunctions.centerText("Remove Menu", 58)<<"|"<<endl;
        generalFunctions.printLine(60 , '-');

        cout<<"| "<<setw(57)<<left<<"1 - Remove a book."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"2 - Remove a section."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"3 - Back to the Main Menu. "<<"|"<<endl;

        generalFunctions.printLine(60 , '=');

        /////////////////////////////////////

        cout<<"\n> Enter your choice : ";
    }
    void menuRemoveChoice() //! Loop to choese which you want to add
    {
        Section section;
        Book book;
        
        int choice;
        do
        {
            menuRemove();
            cin>>choice;

            generalFunctions.handleErrors(choice); 

            switch (choice)
            {
                case 1: //! Remove book
                    writeToRemove("book");
                    break;
                
                case 2: //! Remove Section
                    writeToRemove("section");
                    break;

                case 3://! Return to thw main menu
                    return;
                
                default:
                    cout<<"\n* Wrong Entry! please try again!"<<endl;
                    break;
            }

            generalFunctions.printLine(50 , '-'); //! print a Line between each option

        } while (choice != 3);
        
    }
};


/////////////////////////


struct Menues
{
    AddFunctions addFunctions; //! DONE
    RemoveFunctions removeFunctions; //! DONE
    UpdateFunctions updateFunctions; 
    SortFunctions sortFunctions; //! DONE
    SearchFunctions searchFunctions;
    /* 'Display' has been decleared as a global object.*/ //! DONE
    TotalFunctions totalFunctions; //! DONE
    
    //! Employee / Main  Menu and the loop to chose options
    void mainMenu()
    {
        cout<<endl;
        generalFunctions.printLine(60 , '=');
        cout<<"|"<<generalFunctions.centerText("Main Menu", 58)<<"|"<<endl;
        generalFunctions.printLine(60 , '-');

        cout<<"| "<<setw(57)<<left<<"1 - Add a new ( book / section )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"2 - Remove a ( book / section )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"3 - Update a ( book / section )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"4 - Sort the books."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"5 - Search a ( book / section )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"6 - display ( books / sections )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"7 - Total ( books / sections )."<<"|"<<endl;
        cout<<"| "<<setw(57)<<left<<"8 - Exit. "<<"|"<<endl;

        generalFunctions.printLine(60 , '=');

        /////////////////////////////////////

        cout<<"\n> Enter your choice : ";
    }
    void employeeChoice() //! Every operations we gonna do in the program are here
    {
        int choice = 0;

        addFunctions.baseConstSections(); //! to intial the First three sections (Important)

        do
        {
            mainMenu();
            cin>>choice;

            generalFunctions.handleErrors(choice);

            switch (choice)
            {
                case 1: //! Add
                    addFunctions.menuAddChoice();
                    break;
                
                case 2: //! Remove
                    removeFunctions.menuRemoveChoice();
                    break;

                case 3: //! Update
                    /*Working on it*/
                    break;

                case 4: //! Sort
                    sortFunctions.menuSortChoice();

                    break;

                case 5: //! Search
                    /*Working on it*/
                    break;

                case 6: //! display
                    displayFunctions.displayMenuChoice();
                    break;

                case 7: //! Total
                    totalFunctions.totalMenu();
                    break;
                
                case 8: //! Exit
                    generalFunctions.printLine(50 , '-');
                    return;

                default:
                    cout<<"\n* Wrong Entry! please try again!\n"<<endl;
                    break;
            }

            generalFunctions.printLine(50 , '-'); //! print a Line between each option

        } while (choice != 8);
        
    }
};


////////////////////////////////////////////////////////////


//! >>>>>>>>>>>>>>>>>>    M A I N

int main()
{
    Menues menues;

    //////////////////////////////////////

    //! Greeting sentence
    cout << "\n\n" << generalFunctions.centerText(string(46 , '-') , 64) << endl;
    cout << "<<<<<<<<[   Welcome to our Library Management System   ]>>>>>>>>" << endl;
    cout << generalFunctions.centerText(string(46 , '-') , 64) << endl << endl;

    ///////////////////

    //! The Main Menu

    menues.employeeChoice(); //! Every operations will be here

    //////////////////

    generalFunctions.clearMemoryLeak(); //! Delete all pointers

    ///////////////////

    //! Concluding sentence
    cout << endl << endl;
    generalFunctions.printLine(79 , '=');
    cout << "|             T h e  _  P r o g r a m  _  i s  _  F i n i s h e d             |"
        << endl;
    generalFunctions.printLine(79 , '=');
    cout << endl << endl;

    ///////////////////
    
    return 0;
}