// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

#define MAX_INPUT_LENGTH 20

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_order
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  const std::string account_number = "CharlieBrown42";
  char user_input[MAX_INPUT_LENGTH]; //update value to ensure variable is used
  std::cout << "Enter a value: ";
  std::cin.getline(user_input, MAX_INPUT_LENGTH);

  //Check if input violates length of input.
  //If violated, alert user of overflow
  //Clear buffer and cin errors
  if (!std::cin) {
	  std::cout << "Buffer Overflow. Input values exceeding limit will be trimmed." << std::endl << std::endl;
	  //Clear errors from cin
	  std::cin.clear();
	  //Clear buffer
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu