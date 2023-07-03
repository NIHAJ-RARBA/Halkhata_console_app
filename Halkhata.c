#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    char name[50];
    int number;
    double price;
} sold_item;

typedef struct
{
    char name[101];
    char mobileNo[12]; // 11 digit number
    double due;
} Customer;

typedef struct
{
    char mobileNo[12]; // mobile number used as ID
    char date[50];
    int item_number;
    double paid;
    sold_item arr[30]; // assuming a maximum of 30 items bought
} bill;

// declaring globally for functions to access freely
char varName[50];
char varMobile[12];
double paying;
Customer customer_array[100];
bill bill_array[100];
int positionInArray = 0;

bill billing;
sold_item sold;
Customer customer_var;

int count = 0;

void update(Customer cust)
{
    FILE *fp = fopen("customer.txt", "r+w");
    FILE *fp1 = fopen("bills.txt", "r+w");
    if (!fp)
        printf("Can't open!");

    int found = 0;

    while (fread(&customer_var, sizeof(customer_var), 1, fp))
    {
        if (strcmp(customer_var.mobileNo, cust.mobileNo) == 0)
        {
            found = 1;
            // printf("%d %d", customer_var.due, cust.due);
            fseek(fp, -(sizeof(Customer)), SEEK_CUR);
            fwrite(&cust, sizeof(Customer), 1, fp);
            break;
        }
    }
    fclose(fp);

    if (found == 0)
    {
        fp = fopen("customer.txt", "a+");
        strcpy(customer_var.name, cust.name);
        strcpy(customer_var.mobileNo, cust.mobileNo);
        customer_var.due = cust.due;
        fwrite(&customer_var, sizeof(Customer), 1, fp);
        fclose(fp);
    }
}

void read_from_file()
{
    FILE *fp = fopen("customer.txt", "r");
    FILE *fp1 = fopen("bills.txt", "r");

    int i = 0;
    while (fread(&customer_array[i], sizeof(Customer), 1, fp))
    {
        i++;
        count++;
    }

    i = 0;
    while (fread(&bill_array[i], sizeof(bill), 1, fp1))
    {
        i++;
    }
    fclose(fp);
    fclose(fp1);
}

int main()
{
    int option;
    printf("\t__ ___ ___ __Halkhata__ __ __ __ __");
    printf("\n\n1.Buy\n2.Bill lookup of a specific customer\n3.Pay dues\n4.Check full records\n5.Exit");

    do
    {
        do
        {
            printf("\nPlease enter preferred option: ");
            scanf("%d", &option);
            getchar();
        } while (option < 1 || option > 5);

        switch (option)
        {
        case (1):
        {
            printf("\nEnter name: ");
            gets(customer_var.name);
            printf("Enter mobile no.: ");
            gets(customer_var.mobileNo);
            strcpy(billing.mobileNo, customer_var.mobileNo);
            printf("Enter number of items: ");
            scanf("%d", &billing.item_number);
            fflush(stdin);

            float total = 0;
            for (int i = 0; i < billing.item_number; i++)
            {
                printf("Enter item name: ");
                gets(billing.arr[i].name);

                strcpy(billing.date, __DATE__);

                printf("Enter number of this item: ");
                scanf("%d", &billing.arr[i].number);

                printf("Price of this item: ");
                scanf("%lf", &billing.arr[i].price);
                fflush(stdin);
            }

            printf("%s has bought %d items on %s.\n", customer_var.name, billing.item_number, billing.date);
            printf("\n-----------------------------------------------------------------------------------------------\nSl no.\t\tItems\t\tPrice of item\t\tQuantity\t\tAmount\t\t\n-----------------------------------------------------------------------------------------------\n\n");
            for (int i = 0; i < billing.item_number; i++)
            {
                printf("%d\t\t", i + 1);
                printf("%s\t\t", billing.arr[i].name);
                printf("%.2f\t\t\t", billing.arr[i].price);
                printf("%d\t\t\t", billing.arr[i].number);
                printf("%.2f\t\t", billing.arr[i].number * billing.arr[i].price);
                printf("\n");
                total += billing.arr[i].number * billing.arr[i].price;
            }
            printf("-----------------------------------------------------------------------------------------------\n");
            printf("Total Bill\t\t\t\t\t\t\t\t\t%.2f\n", total);
            printf("Paid amount in tk: ");
            scanf("%lf", &billing.paid);
            customer_var.due = total - billing.paid;

            if (customer_var.due > 0)
                printf("Due: %.2lf tk", customer_var.due);
            else if (customer_var.due < 0)
                printf("Amount returned: %.2lftk", fabs(customer_var.due));
            else
                printf("%s has no due", customer_var.name);

            customer_array[positionInArray] = customer_var;
            bill_array[positionInArray] = billing;
            positionInArray++;

            // append to file

            FILE *fp = fopen("customer.txt", "a+");
            FILE *fp1 = fopen("bills.txt", "a+");
            fwrite(&customer_var, sizeof(Customer), 1, fp);
            fwrite(&billing, sizeof(bill), 1, fp1);

            fclose(fp);
            fclose(fp1);

            fflush(stdin);
            break;
        }
        case (2):
        {

            read_from_file();
            fflush(stdin);
            printf("\nEnter mobile number to look up bill: ");
            gets(varMobile);

            float total = 0;
            int found = 0;
            for (int i = 0; i < 100; i++)
            {
                if (strcmp(customer_array[i].mobileNo, varMobile) == 0)
                {
                    found = 1;
                    printf("\n\n\n\n");
                    printf("%s, you have bought %d items on %s.\n", customer_array[i].name, bill_array[i].item_number, bill_array[i].date);
                    printf("\n-----------------------------------------------------------------------------------------------\nItems\t\tPrice of item\t\tQuantity\t\tAmount\t\t\n-----------------------------------------------------------------------------------------------\n\n");
                    for (int j = 0; j < bill_array[i].item_number; j++)
                    {
                        printf("%s\t\t", bill_array[i].arr[j].name);
                        printf("%.2f\t\t\t", bill_array[i].arr[j].price);
                        printf("%d\t\t\t", bill_array[i].arr[j].number);
                        printf("%.2f\t\t", bill_array[i].arr[j].price * bill_array[i].arr[j].number);
                        printf("\n");
                        total += bill_array[i].arr[j].number * bill_array[i].arr[j].price;
                    }

                    printf("-----------------------------------------------------------------------------------------------\n");
                    printf("Total bill\t\t\t\t\t\t\t%.2f\n", total);



                    if (customer_array[i].due > 0)
                        printf("Due: %.2lftk", customer_array[i].due);
                    else if (customer_array[i].due < 0)
                        printf("Amount returned: %.2lf", fabs(customer_var.due));
                    else
                        printf("No due.");
                }
            }
            if (found == 0)
            {
                printf("\nNo such customer exists in the records.\n");
            }
            fflush(stdin);
            break;
        }
        case (3):
        {
            read_from_file();
            fflush(stdin);

            printf("\nEnter mobile number to find bill: ");
            gets(varMobile);
            double total = 0;
            int found = 0;
            for (int i = 0; i < 100; i++)
            {
                if (strcmp(customer_array[i].mobileNo, varMobile) == 0)
                {
                    found = 1;
                    double paid;
                    printf("Paid amount: ");
                    fflush(stdin);
                    scanf("%lf", &paid);
                    printf("Paid amount = %lf", paid);
                    printf("\n\n\n");
                    printf("\n%s, you have bought %d items on %s.\n", customer_array[i].name, bill_array[i].item_number, bill_array[i].date);
                    printf("\n---------------------------------------\nItems\t\tAmount\t\tTotal\t\t\n---------------------------------------\n\n");
                    for (int j = 0; j < bill_array[i].item_number; j++)
                    {
                        total += bill_array[i].arr[j].number * bill_array[i].arr[j].price;
                    }

                    bill_array[i].paid += paid;
                    customer_array[i].due -= paid;

                    printf("\nTotal cost\t\t %.2lf", total);
                    printf("\n---------------------------------------\n");

                    if (customer_array[i].due > 0)
                        printf("Current due: %.2lf", customer_array[i].due);
                    else if (customer_array[i].due < 0)
                        printf("Amount returned: %.2lf", fabs(customer_var.due));
                    else
                        printf("No due. Thank you for shopping.");

                    update(customer_array[i]);
                    break;
                }
            }
            if (found == 0)
            {
                printf("\nNo such customer exists in the records.\n");
            }
            fflush(stdin);
            break;
        }
        case (4):
        {
            read_from_file();
            fflush(stdin);

            printf("\t\t\t\t\t\t\t\t\t\t----------ALL RECORDS----------");
            for (int i = 0; i < count; i++)
            {
                float total = 0;
                if (customer_array[i].name == "" || bill_array[i].item_number == 0)
                    continue;
                printf("\n\n\n");
                printf("\n%s has  bought %d items on %s.\n", customer_array[i].name, bill_array[i].item_number, bill_array[i].date);
                printf("\n-----------------------------------------------------------------------------------------------\nSl no\t\tItems\t\tPrice of item\t\tQuantity\t\tAmount\t\t\n-----------------------------------------------------------------------------------------------\n");
                for (int j = 0; j < bill_array[i].item_number; j++)
                {
                    printf("%d\t\t", i + 1);
                    printf("%s\t\t", bill_array[i].arr[j].name);
                    printf("%.2f\t\t\t", bill_array[i].arr[j].price);
                    printf("%d\t\t\t", bill_array[i].arr[j].number);
                    printf("%.2f\t\t", bill_array[i].arr[j].price * bill_array[i].arr[j].number);
                    printf("\n");
                    total += bill_array[i].arr[j].number * bill_array[i].arr[j].price;
                }

                printf("-----------------------------------------------------------------------------------------------\n");
                printf("Total bill\t\t\t\t\t\t\t\t\t%.2f\n", total);

                if (customer_array[i].due > 0)
                    printf("Due: %.2lftk", customer_array[i].due);
                else if (customer_array[i].due < 0)
                    printf("Amount returned: %.2lf", fabs(customer_var.due));
                else
                    printf("No due.");
            }
            fflush(stdin);
            break;
        }
        case (5):
        {
            exit(0);
            break;
        }
        default:
            break;
        }
        printf("\n\n\n");
        printf("\n\n1.Buy\n2.Bill lookup\n3.Pay dues\n4.Check full records\n5.Exit");

    } while (option != 5);

    return 0;
}