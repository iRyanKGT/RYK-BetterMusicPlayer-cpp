/* ========================================================================= */
/*	PROGRAM Better Music Player

    AUTHOR: Ryan Kunjbehari
    FSU MAIL NAME: EF0825229
    RECITATION SECTION NUMBER: 02
    RECITATION INSTRUCTOR NAME: Yanan Yu
    COP 3014 - Summer 2009
    PROJECT NUMBER: 5
    DUE DATE: Monday 7/20/2009
    PLATFORM: Windows OS using Microsoft Visual C++ Express 2008 compiler

SUMMARY

This program initially opens up a file and then displays a menu to the user. 
This menu enables the user to choose between four options that either play
the songs in SongData.txt in a certain order or quit the progran.

INPUT

The input is entirely interactive.  It will only require the user to 
enter in the choice on the music player menu to pick the style of play 
desired.  All input is typed in at the keyboard by the user 
(person running the program). 

OUTPUT

All output goes to the text (console) window.  The program prints an output 
title and echoprints the user's input in a readable fashion.  A four option 
menu is printed out as well for the user to enter in a choice.

ASSUMPTIONS

We cannot assume that all input data is valid and correctly entered by the 
user.  Therefore, this program counteracts this problem by looping the file 
menu choice selection.  The menu opening loop tests for correct choice of the 
numbers 1-4.

*/

/* ========================================================================= */

#include <iostream>
#include <fstream>			// for file I/O (Reading the text file)
#include <string>			// for reading the file name the user inputs  
#include <cstdlib>			// for random song playlist
#include <iomanip>			// used for setw precision
#include <ctime>			// used to initialize time in srand function.
using namespace std;

/* ========================================================================= */

/* Type Definition for the Genre */
enum Genre {COUNTRY, DANCEPARTY, ELEVATOR, ROCK};


/* Global Constants */
const int ARRAY_SIZE = 15;	// Array Size

/*Function Prototypes:
OpenNewFile() - Opens the text file, ShowMenu() - Display's the menu, 
Standard Play() - Plays the songs in normal order, RandomPlay() - Plays
the songs in a randomized fashion, PlayOneSong() - Plays only one song
and lists its genre, PrintSongName() - used to output genre and to change
data type from enum to string type, Quit() Terminates the Program */
void OpenNewFile(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE]);  
void ShowMenu();														
void StandardPlay(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE]);		
void RandomPlay(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE]);			
void PlayOneSong(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE]);			
void PrintSongName(Genre type);												
void Quit(bool& flag);
 

int main()
{
	// named symbolic constants and variables
	char choice;				  // Holds the menu choice
	bool flag = true;			  // flag for menu choice error detection
	int songIds[ARRAY_SIZE];	  // Array with 15 elements
	Genre songTypes[ARRAY_SIZE];  // Array with 15 elements

	// print overall program output heading
	cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n\n";
	cout <<	"*=*=*=*=*=*=*=*      Welcome to      *=*=*=*=*=*=*\n"; 
	cout <<	"*=*=*=*=*=*=*=*   Ryan's Redefined   *=*=*=*=*=*=*\n"; 
	cout <<	"*=*=*=*=*=*=*=*     Music Player     *=*=*=*=*=*=*\n\n";
	cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n\n";
	
	OpenNewFile(songIds, songTypes);  // Call to OpenNewFile function 
									  // for the arrays

	do
	{		
		// This displays the menu and also gets the user's choice
		ShowMenu();
		cin >> choice;
		cin.ignore(80,'\n');	   // Ignores everything after 
								   // initial character choice
	
			
		/* All of the cases in this switch call to their respective 
		functions down below in order to perform the tasks selected 
		from the outputted user menu */
		switch (choice) 
		{
			case '1': StandardPlay(songIds, songTypes);	
				break;
			case '2': RandomPlay(songIds, songTypes);
				break;
			case '3': PlayOneSong(songIds, songTypes); 
				break;
			case '4': Quit(flag);
				break;
			default : // used for error detection
				cout << "You have entered an incorrect choice,\n";
				cout << "Please enter 1, 2, 3, or 4: \n";
				break;	
		}
		
	}while (flag);
	return 0;
}

	
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to dispaly the menu.				*									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void ShowMenu()  
{ // ShowMenu
	cout << "\nPick a task to perform: \n\n";
	cout << "1. Play Current Playlist In Order\n"; 
	cout <<	"2. Play Randomized Playlist\n"; 
	cout <<	"3. Play One Song\n";
	cout <<	"4. Leave the Program\n";
	cout << "Please enter your choice: ";
} // ShowMenu

		
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to initially open the file to be used for *	  
// analysis in this program.									  *									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void OpenNewFile 
(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE])     // its corresponding
														   // stream variable

{  // OpenNewFile
	int count = 0;
	char type;
	ifstream inFile;
	inFile.open ("SongData.txt");

	if (!inFile)   // complement of inFile to see if it was opened correctly
		{
			cout << endl << "The file was not opened successfully." << endl;
			cout << endl << "The program will now come to a close." << endl;

			exit(EXIT_FAILURE);	     // located in std libs
		}

	// Read the 15 songs from the file into the array.
	for (count = 0; count < ARRAY_SIZE; count++)
	{
		inFile >> songIds[count] >> type;

		// change data type from char to enum type
		switch (type)
		{
			case 'C': songTypes[count] = COUNTRY;
				break;
			case 'D': songTypes[count] = DANCEPARTY;
				break;
			case 'E': songTypes[count] = ELEVATOR;
				break;
			case 'R': songTypes[count] = ROCK;
				break;
		}
	}

	// Close the file.
	inFile.close();
		
}   // OpenNewFile  


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to read the songs from the file	*			
// into an array for standard play.						*									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void PrintSongName(Genre type)
{  // PrintSongName
	// change data type from enum to string type
	switch(type)
	{
		case COUNTRY:
			cout << "Country";
			break;
		case DANCEPARTY:
			cout << "Dance Party";
			break;
		case ELEVATOR:
			cout << "Elevator";
			break;
		case ROCK:
			cout << "Rock";
			break;
	}
}  // PrintSongName



//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to read the songs from the file	*			
// into an array for standard play.						*									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void StandardPlay(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE])
{   // StandardPlay
	int count;					// Loop counter variable
	
	// Display the songs in the playlist
	cout << "The songs will play in the following order: ";
	for (count = 0; count < ARRAY_SIZE; count++)
	{	
		cout << songIds[count] << " ";
		PrintSongName(songTypes[count]);
		cout << endl;
	}
	
}   // StandardPlay


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to read the songs from the file	*			
// into an array for random play.						*									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void RandomPlay(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE])
{	// RandomPlay

	unsigned int seed;				// seeds (initializes) rand()
	int index;
	int randomIds[ARRAY_SIZE];
	bool repeat[ARRAY_SIZE] = {false};

	seed = static_cast<unsigned>(time (NULL));
	srand (seed);

	int count = 0;
	
	for(count=0; count<15; count++)
	{	
		index = rand()%15;
		
		while(repeat[index] == true)
		{
			index = rand()%15;
		}

		randomIds[count] = index;
		repeat[index] = true;
	}
	//print the random playlist
	cout << "The songs will play in the following order: ";
	for (count = 0; count < ARRAY_SIZE; count++)
	{			
		index = randomIds[count];
		cout << songIds[index] << " ";
		PrintSongName(songTypes[index]);
		cout << endl;
	}

}	// RandomPlay


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function that asks the user to pick a song 1-15  *									
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void PlayOneSong(int songIds[ARRAY_SIZE], Genre songTypes[ARRAY_SIZE])
{  // PlayOneSong
	int choice;   // to hold a menu choice

	cout << "Please select a song to play\n";
	cout << "Please enter a song number 1-15: \n";
	cin >> choice; 

	while(choice < 1 || choice > 15)
	{
		cout << "You have entered an incorrect choice,\n";
		cout << "Please enter a song number 1-15: \n";
		cin >> choice;
	}
	
	cout << "Thank You, Your song: "
		 << songIds[choice-1] << " ";
	PrintSongName(songTypes[choice-1]);
	cout << " is now playing." << endl;
}  // PlayOneSong


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Here is the function to quit the program	*	  																	
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void Quit(bool& flag)
{ // Quit
	flag = false;		
	cout << "\n\nShutting down Music Player, Goodbye!\n";
} // Quit


/* ========================================================================= */
/*                           END OF PROGRAM                                  */
/* ========================================================================= */

