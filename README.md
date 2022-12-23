# Tribe_dictionary

Welcome to the English-Tribe Language Dictionary Project! This project allows you to translate English words to a tribe language by building a dictionary and performing lookups. The dictionary is implemented as a binary tree and stored in a "dict.txt" file. The tree is balanced such that the difference in the heights of the left and right subtrees of each node should not exceed 1.

Installation

Before you can run this project, you'll need to install C. Here's how:

Install C

Go to the C website and follow the instructions to install C for your specific operating system.

Running the Project

Once you have C installed, you're ready to run the project. Follow these steps:

Clone or download the project repository to your local machine.
Make sure the "dict.txt" file is in the same folder as the main.c file.
Open the project in your preferred IDE (e.g. Eclipse, Visual Studio).
Run the main.c file.
The program will prompt you to enter an English word for which you want to find the corresponding tribe language word.
If the word is found in the dictionary, the program will print the tribe language word to the screen. If the word is not found and the user does not know the meaning, the program will inform the user and continue to the next prompt.
The program will continue to prompt the user for English words until the user is finished.

Additional Notes

The English words are treated in a case-insensitive manner. For example, "Good" and "good" will both return the same result. However, in the dictionary, there will be only one entry either for "Good" or "good".
The tree is implemented as a linked list with two data fields, one for the English word and one for the corresponding tribe language word. It is assumed that a word (in both languages) is no longer than 10 characters.
The reference count for each word in the dictionary is initialized to 0 in the first phase of the program. It is updated every time the word is looked up.
I hope you enjoy using this project! If you have any questions or issues, don't hesitate to reach out.
