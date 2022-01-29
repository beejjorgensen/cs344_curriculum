#include <stdio.h>
#include <stdlib.h>

int get_balance(void)
{
    FILE *fp = fopen("balance.txt", "r");

    int balance;
    
    int c = fscanf(fp, "%d", &balance);

    if (c != 1)
        printf("get_balance failed\n");

    fclose(fp);

    return balance;
}

void set_balance(int balance)
{
    FILE *fp = fopen("balance.txt", "w");

    fprintf(fp, "%d", balance);

    fclose(fp);
}

void deposit(int amount)
{
    int balance = get_balance();

    printf("Deposit balance: %d\n", balance);

    balance += amount;

    set_balance(balance);
}

void withdraw(int amount)
{
    int balance = get_balance();

    printf("Withdraw balance: %d\n", balance);

    if (amount > balance)
        return;

    balance -= amount;

    set_balance(balance);

}

int main(void)
{
    for (int i = 1; i < 10; i++) {
        deposit(i);
    }

    for (int i = 1; i < 10; i++) {
        withdraw(i);
    }
}