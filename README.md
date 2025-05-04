# **Library management system** 
A project that implement data structure for simulating the library system for both a librarian and a user

## Feature 
### Library : 
- Organize the book data in the system.
- Organize the member data.
- Search the book in the system.
- Check the borrowed history of each book and each member
### User : 
- Login and change the member data
- Borrow and return the book
- Reserve the book in the system

## Data structure 
- Hash map : For divide the category of book
- Linked list : For insert book in each category

## How to use 
1. Clone the repository 
``` git clone https://github.com/Phenwatsa/File_Code_Project_CPE112```

2. Using the command 
``` gcc -g Main_Program.c 1_User/User.c 2_Libralian/Libralian.c 3_Function/Book_Management_Func.c 3_Function/Borrow_Return_Func.c 3_Function/Data_Func.c 3_Function/Member_Func.c 3_Function/Other_Func.c -I3_Function -o LibrarySystem ``` 

3. ``` ./LibrarySystem ```