#include"Library.h"
#include"User_Database.h"
#include"Book_Database.h"
#include<fstream>
#include<sstream>
#include<string>


class Library{
private:
    static const int number_of_attributes_in_file = 6; //Keeps track of number of columns in csv file delimied by ','

    long unsigned int total_number_of_books;
    std::vector<Book> books_database_vector; // The indices will be nothing but the book_id
    std::unordered_map<std::string, Book> books_database_by_author; // Hashmaps used
    std::unordered_map<std::string, Book> books_database_by_publisher; // Hashmaps used
    std::unordered_map<std::string, Book> books_database_by_title; // Hashmaps used


public:
    /*
    Constructor and Destructors
    */
    Library(string book_database_file, string user_database_file);           //done
    ~Library();           //done

    /*
    Operations on books
    */
    bool addBook();           //done
    bool deleteBook();           //done
    bool searchBookByBookId();           //done
    bool searchBookByTitle();           //done
    bool searchBookByAuthor();           //done
    bool searchBookByPublisher();           //done

    /*
    Issue and return functions
    */
    void issueBook(user user_info, Book book_to_be_issued);
    void returnBook();
    void claimBook();

};

  Library::Library(string book_database_file, string user_database_file){
    if(book_database.loadDatabase(book_database_file) && user_database.loadDatabase(user_database_file)){
      cout<<"Successfully loaded both the databases !!";
    }
    else {
      cerr<<"Error loading the databases !!!";
    }

  }

  Library::~Library(){
    if(updateDatabase(book_database, "books.txt") && updateDatabase(user_database, "users.txt")){
      cout<<"Successfully written into the databases !!";
    }
    else {
      cerr<<"Error writing into the databases !!!";
    }

  }

  /*
  Checks whether a book exists previously, udpdates it and adds it to the database if not.
  */
  bool Library::addBook(){
    Book newbook;
    cout<<"Please enter the Title of the book !"<<endl;
    cin>>newbook.title;
    cout<<"Please enter the Author of the book !"<<endl;
    cin>>newbook.author;
    cout<<"Please enter the Publisher of the book !"<<endl;
    cin>>newbook.publisher;

    Book* the_book = book_database.searchBookByTitle(newbook.title);
    //the_book will point out to the book search for if exists
    if(the_book != NULL){
      the_book->increamentCopies();
      return true;
    }
    else{
      return (book_database.addBook(newbook) != NULL); //Note that new  book_id will be given to the book
    }

    /*
    Checks the book exists or not and accordingly deletes it if it does.
    */
    bool Library::deleteBook(){
      Book book_to_be_deleted;
      cout<<"Please enter the Title of the book !"<<endl;
      cin>>book_to_be_deleted.title;
      cout<<"Please enter the Author of the book !"<<endl;
      cin>>book_to_be_deleted.author;
      cout<<"Please enter the Publisher of the book !"<<endl;
      cin>>book_to_be_deleted.publisher;

      Book* the_book = book_database.searchBookByTitle(book_to_be_deleted.title);

        if(the_book == NULL){
          cerr << "The book you mentioned doesnot exist !"<<endl;
          return false;
        }else{
          return book_database.deleteBook(the_book);
        }
    }

    /*
    Checks the book exists or not  based on the book_id and displays the info
    */
    bool Library::searchBookByBookId(){
      cout<<"Please enter the book id of the Book!"<<endl;
      long unsigned int  book_id;
      cin>> book_id;

      Book* the_book = book_database.searchBookByBookId( book_id);

      if(the_book != NULL){
        the_book->displayInfo();
        return true;
      }else{
        cerr<<"There is no book with the given book id!"<<endl;
        return false;
      }

    }

    /*
    Checks the book exists or not based on the title of the book and displays the info
    */
    bool Library::searchBookByTitle(){
      cout<<"Please enter the Title of the Book!"<<endl;
      string title;
      cin>>title;

      Book* the_book = book_database.searchBookByTitle(title);

      if(the_book != NULL){
        the_book->displayInfo();
        return true;
      }else{
        cerr<<"There is no book with the given title!"<<endl;
        return false;
      }

    }

    /*
    Checks the book exists or not based on the publisher and displays the info
    */
    bool Library::searchBookByPublisher(){
      cout<<"Please enter the Publisher of the Book!"<<endl;
      string publisher;
      cin>>publisher;

      Book* the_book = book_database.searchBookByPublisher(publisher);

      if(the_book != NULL){
        the_book->displayInfo();
        return true;
      }else{
        cerr<<"There is no book with the given publisher!"<<endl;
        return false;
      }

    }


    /*
    Checks the book exists or not based on the Author and displays the info
    */
    bool Library::searchBookByAuthor(){
      cout<<"Please enter the Author of the Book!"<<endl;
      string author;
      cin>>author;

      Book* the_book = book_database.searchBookByAuthor(author);

      if(the_book != NULL){
        the_book->displayInfo();
        return true;
      }else{
        cerr<<"There is no book with the given author!"<<endl;
        return false;
      }

    }


  }
