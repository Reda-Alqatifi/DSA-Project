#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//! >>>>>>>>>>   D S A  _  P r o j e c t  -  M A I N   <<<<<<<<<<<<


//TODO - >>>>>>>>>>>>>>]  General  [<<<<<<<<<<<<<<

const string ERROR = "Error"; //! to handle errors;

//* Section data
struct Section
{
    string name;
    int booksNum;

    int No; //! just to count them, and to use them in term of adding books 
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

    DoublyLinkedList books; //! for Nested Linked List
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
    void handleErrors(int &choice , string &Error /*if he choose wrong option again*/)
    {
        if(cin.fail())
        {
            cout<<"\n>>>>] This option doesn't exist"<<endl;
            cin.clear();
            cin.ignore(1000 , '\n');

            cout<<"> Enter another option please : ";
            cin>>choice;

            if (cin.fail())
            {
                cout<<"\n>>>>] This option doesn't exist"<<endl;
                cin.clear();
                cin.ignore(1000 , '\n');

                cout<<"\n<< YOU ARE JUST PLAYING! GO HOME! >>\n"<<endl;
                
                Error = ERROR;
            }
            else
            {
                Error = " ";
            }
        }
    }

    //! To change the input case int Lower (small letters), very important in Searching
    void lowerCase(string &word)//* changes the orginal value
    {
        // to make it Lower
        for (size_t Lower = 0 ; Lower < word.length() ; Lower++) 
        {
            if (word[Lower] >= 'A' && word[Lower] <= 'Z') 
            {
                word[Lower] = word[Lower] + ('a' - 'A');
            }
        }
    }

    //! to print a line from char you want
    void printLine(int length/*better one is 50*/ , char symbol/*better one is '-'*/)
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
    void updateNo(/*Section or Book*/const string &type)
    {
        if(type == "Book")
        {
            int i = 1;
            for (NodeBook *temp = booksList.head ; temp != NULL ; temp = temp->next)
            {
                temp->book.No = i;
                i++;
            }
        }
        else
        {
            int i = 1;
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

struct SortFunctions
{

};


//////////////


struct DisplayFunctions
{
    //! >>>>>>>>>>>>> Just for 'testing output' (Temporary) :
    void displayBooks()
    {
        NodeBook *current;
        current = booksList.head;

        cout << "\n" << generalFunctions.centerText("<< Books List >>" , 50) 
            << endl << endl;
        while(current != NULL)
        {
            cout << "Book No :  " << current->book.No << endl;
            cout << "title :  " << current->book.title << endl;
            cout << "author :  " << current->book.author << endl;
            cout << "code :  " << current->book.code << endl;
            cout << "section :  " << current->book.section << endl;
            cout << "price :  " << current->book.price << endl;
            cout << "quantity :  " << current->book.quantity << endl;

            generalFunctions.printLine(50 , '-');

            current = current->next;
        }
    }

    void displaySections()
    {
        NodeSection *current;
        current = sectionsList.head;

        cout << "\n" << generalFunctions.centerText("<< Sections List >>" , 50)
            << endl << endl;
        while(current != NULL)
        {
            cout << "Section No :  " << current->section.No << endl;
            cout << "Section name :  " << current->section.name << endl;
            cout << "num of Books in it :  " << current->section.booksNum << endl;

            generalFunctions.printLine(50 , '-');

            current = current->next;
        }
    }

    void displaySectionsBooks()//Nestd list
    {
        NodeSection *current;
        NodeBook *books;
        current = sectionsList.head;

        cout << "\n" << generalFunctions.centerText("<< Sections List >>" , 50)
            << endl << endl;
        while(current != NULL)
        {
            cout << "Section No :  " << current->section.No << endl;
            cout << "Section name :  " << current->section.name << endl;
            
            books = current->books.head;
            cout << " >>> Books in it :  " << endl;
            while(books != NULL)
            {
                cout << "Book No :  " << books->book.No << endl;
                cout << "title :  " << books->book.title << endl;
                cout << "code :  " << books->book.code << endl;
                
                generalFunctions.printLine(50 , '-');

                books = books->next;
            }
            

            generalFunctions.printLine(50 , '=');

            current = current->next;
        }
    }

    void displayMenu()
    {
        cout<<"\n1- displayBooks"<<endl;
        cout<<"2- displaySections"<<endl;
        cout<<"3- displaySectionsBooks"<<endl; // nested list
        cout<<"4- return"<<endl;

        cout<<"\n> Enter Your Choice : ";
    }

    void displayMenuChoice()
    {
        int choice;
        
        do
        {
            displayMenu();
            cin>>choice;

            switch (choice)
            {
                case 1:
                    displayBooks();
                    break;
                
                case 2:
                    displaySections();
                    break;
                
                case 3:
                    displaySectionsBooks();
                    break;
                
                case 4:
                    return;

                default:
                    break;
            }

        } while (choice != 4);
        
    }

};

DisplayFunctions displayFunctions; //* Global Object to use anywhere


///////////////


struct AddFunctions //!  Done!
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
        newNode->books.head = NULL; //! very important for Nested Linked List

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

    //! display entire sections
    void sectionsDisplayToAdd(const string &type /*Section or Book*/) 
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
                if(type == "Book") //! for 'books' adding process
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

        //! to check if we have a reppeted section and not insert at a node
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
            sectionsDisplayToAdd("Section"); //! To display the emtire sections for sections

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

        } while (choice != "no" || choice != "n");

    }

    /////////

    //TODO - add books into a section "Nested Linked List" :
    
    //! just for reusebility of code
    void NestedListInsertMethod(NodeBook *currentBookMain , NodeSection *currentSection)
    {
        NodeBook *Copy = new NodeBook; //! to Make a node to copy values on
                    
        Copy->book = currentBookMain->book; //! to copu the orginal node
        Copy->next = NULL;
        Copy->previous = NULL;
        
        if (currentSection->books.head == NULL) //! 1st node
        {
            currentSection->books.head = Copy;
            
        }
        else //! other nodes
        {
            NodeBook *last;
            
            //! t0 intilaize it wth the head for a specific section
            last = currentSection->books.head; 

            while(last->next != NULL)
            {
                last = last->next;
            }

            last->next = Copy;
            Copy->next = NULL;
            Copy->previous = last;
        }
        
        //! to Update 'No'
        int i = 1;
        for(NodeBook *temp = currentSection->books.head ; temp != NULL ; temp = temp->next)
        {
            temp->book.No = i;
            i++;
        }
    }
    
    //! to insert books into thier sections
    void insertNestedList(NodeBook *currentBookMain)
    {

        if (currentBookMain == NULL) //! no books
        {
            return;
        }
        else //! have books
        {
            NodeSection *currentSection = sectionsList.head;

            while (currentSection != NULL)
            {
                
                if (currentBookMain->book.section == currentSection->section.name)
                {
                    NestedListInsertMethod(currentBookMain , currentSection);
                    
                    return;
                }
                else if(currentBookMain->book.section.empty() &&
                        currentSection == sectionsList.head)        //! Neither
                {
                    NestedListInsertMethod(currentBookMain , currentSection);
                }
                
                
                currentSection = currentSection->next;
            }

        }
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

        insertNestedList(newNode); //! to insert the book into its section
    }
    
    void writeBook(Book &data , int &counter) //! To write a new Book details
    {
        string Error; //! to handle non sense input
        
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

        sectionsDisplayToAdd("Book"); //! to display the entire sections but for books
        
        cout << " ) - (Write a Number) : ";
        
        NodeSection *currentSection;
        currentSection = sectionsList.head;
        
        int sectionNum;
        cin >> sectionNum;

        generalFunctions.handleErrors(sectionNum , Error); //! to handle non sense input

        

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
        if (cin.fail())
        {
            cout << "\n>>>>] This option doesn't exist" << endl;
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "> Enter another option please : ";
            cin >> data.price;

            if (cin.fail())
            {
                cout << "\n>>>>] This option doesn't exist" << endl;
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\n<< The price will cosidered as '0' till you update it >>\n"
                     << endl;

                Error = ERROR;
            }
        }

        //! Availible Quantity :
        Error;
        cout << "> Availible Quantity : ";
        cin >> data.quantity;
        
        generalFunctions.handleErrors(data.quantity , Error); //! to handle non sense input

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

        } while (choice != "no" || choice != "n");

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

        string Error; //! to handle non sense input
        
        int choice;
        do
        {
            menuAdd();
            cin>>choice;

            generalFunctions.handleErrors(choice , Error); //! to handle non sense input
            if(Error == ERROR) //!to return the user to main menu if he chose a wrong option
            {
                generalFunctions.printLine(50 , '-');
                return;
            }

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
                    break;
            }

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


struct RemoveFunctions
{
    
};


////////////////////////////////////////////////////////////


/////////////


struct TotalFunctions 
{

};


/////////////


struct Menues
{
    AddFunctions addFunctions;
    RemoveFunctions removeFunctions;
    UpdateFunctions updateFunctions;
    SortFunctions sortFunctions;
    SearchFunctions searchFunctions;
    //* 'Display' has been decleared as a global object.
    TotalFunctions totalFunctions;
    
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
        string Error = " ";

        addFunctions.baseConstSections(); //! to intial the First three sections (Important)

        do
        {
            mainMenu();
            cin>>choice;

            generalFunctions.handleErrors(choice , Error);
            if(Error == "Error") //! to return the user to main if he chose a wrong option
            {
                generalFunctions.printLine(50 , '-');
                return;
            }

            switch (choice)
            {
                case 1: //! Add
                    addFunctions.menuAddChoice();
                    break;
                
                case 2: //! Remove
                    /*Working on it*/
                    break;

                case 3: //! Update
                    /*Working on it*/
                    break;

                case 4: //! Sort
                    /*Working on it*/

                    break;

                case 5: //! Search
                    /*Working on it*/
                    break;

                case 6: //! display
                    displayFunctions.displayMenuChoice(); //! just for testing (Temporary)
                    break;

                case 7: //! Total
                    /*Working on it*/
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


/////////////


//! >>>>>>>>>>>>>>>>>>    M A I N

int main()
{
    Menues menues;
    AddFunctions Add;

    //////////////////////////////////////

    //! Greeting sentence
    cout<<"\n\n"<<generalFunctions.centerText(string(46 , '-') , 64)<<endl;
    cout<<"<<<<<<<<[   Welcome to our Library Management System   ]>>>>>>>>"<<endl;
    cout<<generalFunctions.centerText(string(46 , '-') , 64)<<endl<<endl;

    ///////////////////

    //! The Main Menu

    menues.employeeChoice(); //! Every operations will be here

    //////////////////

    generalFunctions.clearMemoryLeak(); //! Delete all pointers

    ///////////////////

    //! Concluding sentence
    cout<<endl<<endl;
    generalFunctions.printLine(79 , '=');
    cout<<"|             T h e  _  P r o g r a m  _  i s  _  F i n i s h e d             |"
    <<endl;
    generalFunctions.printLine(79 , '=');
    cout<<endl<<endl;

    ///////////////////
    
    return 0;
}