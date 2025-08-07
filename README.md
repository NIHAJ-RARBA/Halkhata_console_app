# Halkhata Console Application

A simple console-based application for managing store transactions and customer records.

## Overview

Halkhata is a billing and customer management system that allows store owners to:
- Record customer purchases
- Track customer dues and payments
- Look up billing history
- Maintain complete transaction records

## Features

1. **Buy Items**: Record new purchases for customers
2. **Bill Lookup**: Search and view customer billing history by mobile number
3. **Pay Dues**: Process payments and update customer dues
4. **Check Records**: View all customer transactions and billing history
5. **Exit**: Close the application

## Data Storage

The application uses two text files for data persistence:
- `customer.txt`: Stores customer information (name, mobile number, dues)
- `bills.txt`: Stores detailed billing information (items, prices, quantities, dates)

## How to Use

1. Compile the program: `gcc Halkhata.c -o Halkhata`
2. Run the executable: `./Halkhata`
3. Select from the menu options (1-5)
4. Follow the prompts to enter required information

## Data Structures

- **Customer**: Name, mobile number (used as ID), and due amount
- **Bill**: Mobile number, date, item count, paid amount, and array of purchased items
- **Item**: Name, quantity, and price per unit

## File Operations

The program automatically saves all transactions to files and loads existing data when performing lookups or payments.
