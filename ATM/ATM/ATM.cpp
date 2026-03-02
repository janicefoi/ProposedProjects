// ATM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

int ATM_Transaction(); //Prototype of the function
int anotherTransaction, amountToWithdraw, amountToDeposit, pin; //Global Variable
double balance = 1000; //Global Variable, Initial balance to be 1000 for everyone

int main()
{
	printf("********Welcome to bank!******** \n");
	printf("Enter your pin number please: ");
	scanf("%d", &pin);
	if (pin != 1234)
	{
		printf("Sorry your pin is wrong, please try again.");
	}

	else
	{
		ATM_Transaction();
	}
}

int ATM_Transaction()
{
	int choice;
	printf("Enter your option!\n\n");
	printf("1. Balance Enquiry \n");
	printf("2. Cash Withdraw \n");
	printf("3. Deposit Cash \n");
	printf("4. Exit \n\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1: //Balance Enquiry
		printf("Your bank balance is: %.2f", balance);
		printf("\n\nDo you want to perform another transaction?\nPress 1 to proceed or 2 to exit\n\n");
		scanf("%d", &anotherTransaction);

		if (anotherTransaction == 1)
		{
			ATM_Transaction();
		}
		break;

	case 2: //Withdraw
		printf("Please enter amount to withdraw: ");
		scanf("%d", &amountToWithdraw);

		if (amountToWithdraw <= balance)
		{
			printf("Please collect your cash.");
			balance = balance - amountToWithdraw;
			printf("Your available balance is %lf\n", balance);

			printf("\n\nDo you want to perform another transaction?\nPress 1 to proceed or 2 to exit\n\n");
			scanf("%d", &anotherTransaction);

			if (anotherTransaction == 1)
			{
				ATM_Transaction();
			}
		}
		else
		{
			printf("Sorry in-sufficient funds in your account");
			printf("\n\nDo you want to perform another transaction?\n Press 1 to proceed and 2 to exit\n\n");
			scanf("%d", &anotherTransaction);
			if (anotherTransaction == 1)
			{
				ATM_Transaction();  // call our ATM_Transaction method here
			}
		}
		break;

	case 3: //Deposit
		printf("Please enter amount to deposit: ");
		scanf("%d", &amountToDeposit);
		balance = amountToDeposit + balance;
		printf("Thank you for depositing, your updated balance is %.2f", balance);

		printf("\n\nDo you want to perform another transaction?\nPress 1 to proceed or 2 to exit\n\n");
		scanf("%d", &anotherTransaction);

		if (anotherTransaction == 1)
		{
			ATM_Transaction();
		}
		break;

	default:
		printf("Thank you for using our ATM services.");
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
