/* 
Description: <This program simulates a Cash Deposit Machine (CDM) and
Automated Teller Machine (ATM). It allows users to perform banking 
transactions such as depositing cash or checks, withdrawing money,
and other related operations.> 
Version: <15.8> 
*/ 

#include <stdio.h>
#include <string.h>
#include <math.h>

// Constant Definitions
#define STUDENT_NUMBER 12412007
#define MAX_TRANSACTIONS 5

// Structure
typedef struct 
{
    char TransactionType[15];
    float TypeAmount;
    float RunningBalance;

} TransactionRecord;



// Function Prototypes
void displayDivider(); 
int addTransaction(TransactionRecord record[], int *index, const char *type, float BalanceChanges, float FinalBalance);
int initialLogin(int nIsLogin);
int changePin(int *Pin);
float balanceInquiry(float fBalance);
int deposit(TransactionRecord record[], int *count, float *fBalance);
int withdrawal(TransactionRecord record[], int *count, float *fBalance);
int transfer_of_funds(TransactionRecord record[], int *count, float *fBalance);
int payBills(TransactionRecord record[], int *count, float *fBalance);
void viewTransaction(TransactionRecord record[], int count);
void mainMenu();

/*   
<To divide sections> 
*/ 
void displayDivider() {
   printf("---------------------------------------------------------------------------------\n");
} 



/*   
<Program loging in with account number and password> 
Precondition: <It verifies the account number and password> 
@param <nIsLogin> <to know if login or logout> 
@return <the result show 1 or 0> 
*/ 
int initialLogin(int nIsLogin) {  
    // define variable
    int nDefaultPin;
    float fInitialBalance;
    int nAttempts;
    int nAccountNumber; 
    int nPin;

    // values
    nDefaultPin = 123456;
    nAttempts = 1;

    // Process of initial login
    for (nAccountNumber; nAttempts < 4 && nIsLogin == 0; nAttempts++) {
        printf("Enter Account Number: ");
        scanf("%d", &nAccountNumber);
        printf("Enter PIN (Six Digits): ");
        scanf("%d", &nPin);

        if (nAccountNumber == STUDENT_NUMBER && nPin == nDefaultPin) {
            printf("Welcome, Account: %d\n", nAccountNumber);
            displayDivider();
            return 1;
        } else if (nAttempts == 3) {
            printf("Failed logins have reached three attempts.\n");
            return 0;
        } else {
            printf("Sorry, the account number and PIN did not match. Please try again.\n");
            displayDivider();
        }
    }
}

//new login
int changePassLogin(int Password) {  
    // define variable
    float fInitialBalance;
    int nAttempts;
    int nAccountNumber; 
    int nPin;

    // values
    nAttempts = 1;

    // Process of initial login
    for (nAccountNumber; nAttempts < 4; nAttempts++) {
        printf("Enter Account Number: ");
        scanf("%d", &nAccountNumber);
        printf("Enter PIN (Six Digits): ");
        scanf("%d", &nPin);

        if (nAccountNumber == STUDENT_NUMBER && nPin == Password) {
            printf("Welcome, Account: %d\n", nAccountNumber);
            displayDivider();
            return 1;
        } else if (nAttempts == 3) {
            printf("Failed logins have reached three attempts.\n");
            return 0;
        } else {
            printf("Sorry, the account number and PIN did not match. Please try again.\n");
            displayDivider();
        }
    }
}


/* 
<Description of function> 
Precondition: <precondition / assumption> 
@param <name> <purpose> 
@return <description of returned result> 
*/ 
void mainMenu() { 
    int nChosenNumber;
    float balance = 1000;
    int Pin = 123456;
    int login_code = 0;
    float balanceChanges;
    const char *type = "";
    int NewPin = 0;

    TransactionRecord record[MAX_TRANSACTIONS];
    int count = 0;

    do { // menu 
        printf("[1] - Change PIN\n");
        printf("[2] - Balance Inquiry\n");
        printf("[3] - Deposit\n");
        printf("[4] - Withdraw\n");
        printf("[5] - Transfer Funds\n");
        printf("[6] - Pay Bills\n");
        printf("[7] - View Transactions\n");
        printf("[0] - Logout\n");
        printf("Enter option number: ");
        scanf("%d", &nChosenNumber);
        
        // switch case for user input
        switch (nChosenNumber) {
            case 0:
                printf("You have successfully logged out. Goodbye!\n");
                displayDivider();
                break;
            case 1:
                displayDivider();
                // Pin = changePin(Pin);
                NewPin = changePin(&Pin);
                if (NewPin == -1) { // login if password is wrong
                    if (initialLogin(0) == 0) 
                    {
                        nChosenNumber = 0;
                    }
                }
                else if (NewPin != 123456) { // login after change password
                    if (changePassLogin(NewPin) == 0)
                    {
                        nChosenNumber = 0;
                    }
                }
                break;
            case 2:
                displayDivider();
                balanceInquiry(balance);
                break;
            case 3:
                displayDivider();
                deposit(record, &count, &balance);
                break;
            case 4:
                displayDivider();
                withdrawal(record, &count, &balance);
                break;
            case 5:
                displayDivider();
                transfer_of_funds(record, &count, &balance);
                break;
            case 6:
                displayDivider();
                payBills(record, &count, &balance);
                break;
            case 7:

                viewTransaction(record, count);
                break;
            default:
                printf("Invalid option number. Please try agian.\n");
                displayDivider();
                break;
        }
    } while (nChosenNumber != 0); // the menu will end if user input is 0
}

/* 
<This function allows user to change their PIN> 
Precondition: <The PIN is stored as pointer, and user should 
input correct current PIN before they can set new PIN> 
@param <int *Pin> <to update the PIN> 
@return <return 0 if PIN successfully changed, return -1 if 
user fails to input the PIN within three tries> 
*/ 
int changePin(int *Pin) { 

    int nCurrentPIN;
    int nNewPIN = 0;
    int nVerifyNewPIN;
    int nTries_CurrentPIN = 1;
    int nTries_NewPin = 1;

    // Validate the current PIN
    while (nTries_CurrentPIN < 4) {
        printf("Enter current PIN (Six Digits [100000 - 999999]): ");
        scanf("%d", &nCurrentPIN);

        // Check if current PIN is correct
        if (nCurrentPIN == *Pin) { 
            nTries_CurrentPIN = 4; // correct PIN then exit loop

            while (nTries_NewPin < 4) { // 3 attemps to enter valid new PIN
                printf("Enter new PIN (Six Digits [100000 - 999999]): ");
                scanf("%d", &nNewPIN);
                printf("Verify new PIN: ");
                scanf("%d", &nVerifyNewPIN);

                // Check if new pin = current pin
                if (nNewPIN == *Pin || nVerifyNewPIN == *Pin) {
                    printf("New PIN can not be the same as the current PIN.\n");
                    nTries_NewPin ++;
                    displayDivider();
                } // Check if new PIN in the range
                else if (nNewPIN < 100000 || nNewPIN > 999999 || nVerifyNewPIN < 100000 || nVerifyNewPIN > 999999) {
                    printf("New PIN must be exactly six digits. Please try again.\n");
                    nTries_NewPin++;
                    displayDivider();
                } // Ensure both new and verify pin is equal
                else if (nNewPIN == nVerifyNewPIN) {
                    printf("PIN changed succesfully. Please re-login\n");
                    nTries_NewPin = 4;
                    displayDivider();
                    *Pin = nVerifyNewPIN;
                    return *Pin;
                } else {
                    printf("Please try again\n");
                    nTries_NewPin++;
                    displayDivider();
                }
            }
        } else { // Input incorrect PIN
            printf("Incorrect PIN\n");
            nTries_CurrentPIN++;
            
            if (nTries_CurrentPIN == 4) { // After 3 attempts = lock account
                printf("Changing your PIN has reach three attempts.\n");
                printf("Your account will be logged out.\n"); 
            }
            displayDivider();
        }
    }   
    return -1;
}

/* 
<Display current balance> 
Precondition: <fBlance has 1000 pesos at first> 
@param <fBalance> <display current balance> 
@return <no return only prints the current balance> 
*/ 
float balanceInquiry(float fBalance) {
    printf("Account Number: 12412007\n");
    printf("Your current balance is: %.2f pesos.\n", fBalance);
    displayDivider();
}

/* 
<Deposit money into their account> 
Precondition: <The balance has 1000 pesos> 
@param <*fBalance> <adds deposit value to current balance> 
@return <no return, updates current balance> 
*/ 
int deposit(TransactionRecord record[], int *count, float *fBalance) { 

    int nDenomination;
    int nPesos;
    int nNumberOfBills;
    int nCurrentDeposit;
    int nRunningDeposit = 0;
    char cYesOrNo;               // ask user yes or no
    int nIsTrue = 1;             // flag to control while loop

    // loop continue deposit until user cancel
    while (nIsTrue == 1) {

        do { // choosing deposit denomination
          printf("Choose your deposit denomination\n");
          printf("[1] - P100\n");
          printf("[2] - P200\n");
          printf("[3] - P500\n");
          printf("[4] - P1000\n");
          printf("[0] - Cancel\n");

          printf("Denomination: ");
          scanf("%d", &nDenomination);
      
          switch (nDenomination) {
              case 1:
                  nPesos = 100;
                  break;
              case 2:
                  nPesos = 200;         
                  break;
              case 3:
                  nPesos = 500;  
                  break;
              case 4:
                  nPesos = 1000;         
                  break;
              case 0:
                  nIsTrue = 0;
                  break;
              default:
                  printf("Invalid input please try again.\n");
                  displayDivider();
                  break;
          }
        } while (nDenomination < 0 || nDenomination > 4); // Repeat loop until valid denomination

        // Denomination = 0 means exit
        if (nDenomination == 0) {
            printf("Transaction cancelled. Going back to the main menu.\n");
            displayDivider();

        } else {
            do { 
                printf("Number of bills (up to 10 bills only): ");
                scanf("%d", &nNumberOfBills);

                // Check if number of bills is valid
                if (nNumberOfBills < 1 || nNumberOfBills > 10) {
                    printf("Invalid number of bills. Please try again\n");
                    displayDivider();
                } 

            } while (nNumberOfBills < 1 || nNumberOfBills > 10);

            // calculate current and running deposits
            nCurrentDeposit = nPesos * nNumberOfBills;
            nRunningDeposit += nCurrentDeposit;

            printf("Current Deposit: P%d.00\n", nCurrentDeposit);
            printf("Running Deposit: P%d.00\n", nRunningDeposit);
            printf("Do you wish to deposit more Y/N: ");
            scanf(" %c", &cYesOrNo);

            switch (cYesOrNo) {
                case 'Y':
                case 'y':
                    displayDivider(); // continue deposit
                    break;
                default:
                    nIsTrue = 0;
                    displayDivider(); // Exit deposit
                    break;
            }
        }
    }
    *fBalance += nRunningDeposit;
    addTransaction(record, count,"Deposit", +nRunningDeposit, *fBalance);

}

/* 
<Withdrawing money> 
Precondition: <The balance has 1000 pesos> 
@param <*fBalance> <minus withdrawn value from the current balance> 
@return <no return, updates current balance> 
*/ 
int withdrawal (TransactionRecord record[], int *count, float *fBalance) { 

    int nWithdrawAmount = 0;
    int nIsTrue = 1;

    if (*fBalance == 0.00){
        printf("Your current balance is %.2f pesos, can not withdraw\n", *fBalance);
        nIsTrue = 0;
        displayDivider();
    } 
    else
    {

        while (nIsTrue == 1) {
            // ask user how much to withdraw
            printf("How much do you wish to withdraw? Input '0' to cancel (Intervals of P100 only): ");
            scanf("%d", &nWithdrawAmount);

            // if 0 = cancel
            if (nWithdrawAmount == 0) {
                nIsTrue = 0;
            } // can not be negative
            else if (nWithdrawAmount < 0) { 
                printf("You can not withdraw a negative amount. Please try again.\n");
                displayDivider();
            } // should be interval of 100
            else if (nWithdrawAmount % 100 != 0 && nWithdrawAmount > 0) {
                printf("The withdrawal amount should be an interval of P100.00. Please Try Again!\n");
                displayDivider();
            } // withdrawAmount should not be greater than balance
            else if (nWithdrawAmount > *fBalance){
                printf("Sorry, your balance in insufficient. Your current balance is %.2f.\n", *fBalance);
                displayDivider();
            } // all conditions are met , then exit the loop
            else {
                nIsTrue = 0;
            }
        }; // Repeat loop until valid amount or 0
        
        // if user cancelled the transaction
        if (nWithdrawAmount == 0) {
            printf("Transaction is cancelled.\n");
            displayDivider();
            nWithdrawAmount = 0;
        } // if valid withdrawal amount then update the balance
        else {
            *fBalance -= nWithdrawAmount;
            printf("P%d.00 pesos has been withdrawn\n", nWithdrawAmount);
            displayDivider();
        }
    }

    addTransaction(record, count,"Withdrawal", -nWithdrawAmount, *fBalance);


}

/* 
<Transfering money to another account> 
Precondition: <The balance has 1000 pesos> 
@param <*fBalance> <minus transfering value from the current bala> 
@return <no return, updates current balance> 
*/ 
int transfer_of_funds (TransactionRecord record[], int *count, float *fBalance) { 

    int nTransferAccount;
    int nAmountToTransfer;
    int nIsTrue = 1;
    if (*fBalance == 0) 
    {
        printf("Current Balance is 0.00 pesos, can not transfer funds.\n");
        displayDivider();
    } 
    else 
    {
        
        // loop for transfer account number
        do {
            printf("Enter Account Number (Eight Digits [10000000 - 99999999]) or 0 to cancel: ");
            scanf("%d", &nTransferAccount);

            // if 0 then cancel transaction
            if (nTransferAccount == 0) {
                printf("Transaction cancelled. Going back to the main menu.\n");
                displayDivider();
                nIsTrue = 0;
            } // validate the account number 
            else if (nTransferAccount < 10000000 || nTransferAccount > 99999999) {
                printf("Account number must be eight digits and within the prescribed range.\n");
                printf("Please re-enter the account number.\n");
                displayDivider();
            } // if valid account number 
            else {

                do {
                    printf("Enter amount to transfer or 0 to cancel: ");
                    scanf("%d", &nAmountToTransfer);

                    // if 0 = cancel transaction
                    if (nAmountToTransfer == 0) {
                        printf("Transaction cancelled. Going back to the main menu.\n");
                        displayDivider();
                        nIsTrue = 0; 
                    } // amount should be positive
                    else if (nAmountToTransfer < 0) {
                        printf("Transfer amount must be a positive value between 1 and 50000! Please re-enter.\n");
                        displayDivider();
                    } // should not be greater 50,000 pesos
                    else if (nAmountToTransfer > 50000) {
                        printf("Transfer amount must be a value between 1 and 50000! Please re-enter.\n");
                        displayDivider();
                    } // amount not greater than balance 
                    else if (nAmountToTransfer > *fBalance) {
                        printf("The amount to be transferred must not be greater than the current balance of the account.\n");
                        displayDivider();
                    } // all conditions are met then print message 
                    else {
                        *fBalance -= nAmountToTransfer;
                        printf("%d.00 pesos has been transferred to %d.\n", nAmountToTransfer, nTransferAccount);
                        displayDivider();
                        nIsTrue = 0; 
                    }

                } while (nIsTrue == 1);
            } 

        } while (nIsTrue == 1);

    }
    addTransaction(record, count,"Transfer_Funds", -nAmountToTransfer, *fBalance);
}

 /* 
<Paying Bills to Biller 1 to 5> 
Precondition: <The balance has 1000 pesos> 
@param <*fBalance> <minus pay bills from the current balance> 
@return <no return, updates current balance> 
*/   
int payBills(TransactionRecord record[], int *count, float *fBalance) { 
    float nPayment;
    int nBillerNumber;
    int nIsTrue = 1;

    printf("[1] - Biller 1\n");
    printf("[2] - Biller 2\n");
    printf("[3] - Biller 3\n");
    printf("[4] - Biller 4\n");
    printf("[5] - Biller 5\n");
    printf("[0] - Cancel\n");

    // choosing biller
    do {
        printf("Choose biller: ");
        scanf("%d", &nBillerNumber);

        // if valid biller
        if (nBillerNumber < 6 && nBillerNumber > 0) {
            do {
                printf("Enter amount to pay: ");
                scanf("%f", &nPayment);
                // cancel pay bills if 0
                if (nPayment == 0) {
                    printf("Payment cannot be zero or less!\n");
                    displayDivider();
                } // no negative pay bills value 
                else if (nPayment < 0) {
                    printf("Payment cannot be negative. Please try again.\n");
                    displayDivider();
                } // pay bills can not be greater than balance 
                else if (*fBalance < nPayment) {
                    printf("Your current balance is only %.2f pesos. Please try again.\n", *fBalance);              
                } // all conditions are met 
                else {
                    *fBalance -= nPayment;
                    printf("%.2f pesos has been paid to Biller %d.\n", nPayment, nBillerNumber);
                    nIsTrue = 0;
                    displayDivider();
                }
            } while (nIsTrue == 1);
            
            
            nBillerNumber = 0;
        // if 0 the exit pay bills
        } else if (nBillerNumber == 0) {
            printf("Bills payment has been terminated.\n");
            displayDivider();
        // no valid biller
        } else {
            printf("The chosen biller is not available. Please choose again.\n");
            displayDivider();
        }
    } while (nBillerNumber != 0);

    addTransaction(record, count,"Pay_Bills", -nPayment, *fBalance);
}

int addTransaction(TransactionRecord record[], int *index, const char *type, float BalanceChanges, float FinalBalance) {
    
    strcpy(record[*index].TransactionType, type);
    record[*index].TypeAmount = BalanceChanges;
    record[*index].RunningBalance = FinalBalance;
    (*index)++;
    
}


void viewTransaction(TransactionRecord record[], int count) {

    int i;
    char sign;
    if (count == 0) {
        printf("No transactions to display.\n");
        return;
    }

    printf("Transaction #\t Transaction\t Type Amount\t Running Balance\n");
    for (i = 0; i < count; i++) {
        if (record[i].TypeAmount >= 0) 
        {
            sign = '+';
        } else {
            sign = '-';
        }

        printf("%d.\t\t %-11s\t %c%.2f \t %.2f \n",
            (i + 1), 
            record[i].TransactionType,
            sign,
            fabs(record[i].TypeAmount),
            record[i].RunningBalance);
    }
    displayDivider();

}

int main() 
{   

    int nIsTrue = 1;

    if (initialLogin(0) == 1) {
        mainMenu();
    } else {
        printf("The transaction will be terminated!\n");
        displayDivider();
        nIsTrue = 0;
    }

   return 0;
}