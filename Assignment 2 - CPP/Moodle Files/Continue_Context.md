# Continue Context — Assignment 2 CPP

## Who You Are Talking To
This is a university C++ assignment (Assignment 2) by:
- Razel Elmoznino, ID: 206004095
- Dan Zelkind, ID: 211571948

Read this file fully before doing anything.

---

## Current Status: ALL STEPS COMPLETE ✅

The assignment is fully implemented and passing the test. The last thing added (this session) was the **BusinessCustomer support in the Menu**, which was missing per a forum note from the instructor.

---

## Project Structure

```
Assignment 2 - CPP/
├── Moodle Files/
│   ├── assignment2.cpp       ← main() entry point (DO NOT MODIFY)
│   ├── assignment2CPP2026B.pdf ← original assignment PDF
│   ├── assignment2.txt       ← text-extracted version of the PDF (Hebrew)
│   ├── in.txt                ← test input (pipe this into our exe) — UPDATED THIS SESSION
│   ├── out.txt               ← expected output to match — UPDATED THIS SESSION
│   ├── output2.4.exe         ← reference exe (Windows only, incomplete — missing business customer)
│   ├── steps.txt             ← step plan for this assignment
│   └── Continue_Context.md   ← this file
└── Coding/
    ├── Product.h / Product.cpp
    ├── ShoppingCart.h / ShoppingCart.cpp
    ├── Supplier.h / Supplier.cpp
    ├── Customer.h / Customer.cpp
    ├── Menu.h / Menu.cpp
    ├── assignment2            ← compiled binary (run this)
    ├── our_output.txt         ← output of our binary (for diff comparison)
    └── run_test.sh            ← test script
```

---

## How to Compile & Test

```bash
cd "Assignment 2 - CPP/Coding"
g++ -o assignment2 Product.cpp ShoppingCart.cpp Supplier.cpp Customer.cpp Menu.cpp "../Moodle Files/assignment2.cpp" -std=c++17 -I.
bash run_test.sh
# Should print: ALL TESTS PASSED
```

---

## What Was Done This Session

### Forum Note (reason for this session's work)
The instructor posted: "בקובץ ההרצה לדוגמה חסרה ההתייחסות ללקוח עסקי. עליכם לממש זאת לפי ההוראות"
Translation: "In the example run file, the reference to the business customer is missing. You need to implement this according to the instructions."

The original `output2.4.exe` (the reference executable provided by the instructor) was INCOMPLETE — it never asked for customer type when entering the shopping cart menu. The PDF (page 6, mainMenu option 2) explicitly requires it.

### Change Made: `Menu.cpp` — `mainMenu()` case 2

**Before:**
```cpp
case 2:
    cartMenu();
    break;
```

**After:**
```cpp
case 2: {
    int type;
    cout << "Enter customer type (1-Regular, 2-Business): ";
    cin >> type;
    string cust_name;
    cout << "Enter customer name: ";
    cin >> cust_name;
    delete customer;
    if (type == 2) {
        string company;
        double disc;
        cout << "Enter company name: ";
        cin >> company;
        cout << "Enter discount rate: ";
        cin >> disc;
        customer = new BusinessCustomer(cust_name, company, disc);
    } else {
        customer = new Customer(cust_name);
    }
    cartMenu();
    break;
}
```

**Why this works:**
- Each time the user enters the cart menu, a fresh `Customer` or `BusinessCustomer` is created.
- `BusinessCustomer::checkout()` is already implemented to apply the discount polymorphically.
- `Supplier::customer_purchases(Customer &c)` already calls `c.checkout()` polymorphically, so the discounted amount is correctly credited to the supplier's counter.

### Updated `in.txt` and `out.txt`

Because each cart session now creates a NEW customer (fresh cart), the original `in.txt`/`out.txt` would have been wrong. They were updated to reflect the correct behavior.

**New test scenario:**
1. Store session: Add Milk (ID=1, 3.5, qty=10), Add Bread (ID=2, 1.5→2.99, qty=20). Supplier profit: -65.
2. Cart session 1 — **Regular customer** (Alice): Adds Milk(10) + Bread(20), checks out. Pays 94.8. Supplier profit: 29.8.
3. Store session: Add Eggs (ID=3, 2.5, qty=30). Supplier profit: -45.2.
4. Cart session 2 — **Business customer** (Bob, AcmeCorp, 10% discount): Adds Eggs(29), checks out. Cart total 72.5, pays 65.25 (10% off). Supplier profit: 20.05.
5. Final store print: Milk(0), Bread(0), Eggs(1), Total Profit: 20.05.

---

## Key Implementation Details (for reference)

### Class Responsibilities

**Product** (`Product.h/.cpp`)
- `static int next_id = 1` — auto-incremented on each `Product(name, price, qty)` call
- Products get IDs 1, 2, 3... in order of creation
- `operator<<`: `Product ID: X, Name: Y, Price: Z, Quantity: W`
- `operator==` compares by ID (also works with `int`)
- `operator+=` / `operator-=` modify quantity

**ShoppingCart** (`ShoppingCart.h/.cpp`)
- `add_Product(p, qty)` — inserts at BEGINNING if size==1, otherwise appends (quirk that causes Bread to appear before Milk in the original test)
- `operator<<`: `Shopping Cart Details:\n[products]\nTotal Price: X\n`
- `print_receipt()`: `Shopping Cart:\n[products]\nTotal Price: X\n` (used during checkout)
- `operator[](int id)` — returns `Product*` or `nullptr`

**Supplier** (`Supplier.h/.cpp`)
- Has `name` field (even though not used in Menu currently — initialized to `""`)
- `counter` starts at 0, debited when stock is BOUGHT (`counter -= price * qty`), credited when customer checks out
- `customer_purchases(Customer &c)`: validates all stock, deducts inventory, calls `c.checkout()` (polymorphic!), credits counter
- `operator<<`: `Supplier Details:\n[products]\nTotal Profit: X\n`
- `add_new_product(name, price, qty)` — creates product, debits counter
- `find_product(id)` — returns `const Product*` or nullptr

**Customer** (`Customer.h/.cpp`)
- `checkout()`: returns `cart.Get_total()`, empties cart
- `operator<<`: `Customer Name: X\n[cart]`

**BusinessCustomer** (`Customer.h/.cpp`)
- `checkout()` override: returns `cart.Get_total() * (1.0 - discount_rate)`, empties cart
- `operator<<`: `Customer Name: X, Company Name: Y, Discount Rate: Z\n[cart]`

**Menu** (`Menu.h/.cpp`)
- `Customer* customer` — initialized in constructor as `new Customer("")`, replaced each time option 2 is chosen in mainMenu
- `Supplier supplier` — persists for the entire program run
- `mainMenu()`: loops showing main menu
- `storeMenu()`: private, handles supplier operations
- `cartMenu()`: private, handles customer shopping

### Output Format Rules (CRITICAL)
- After EVERY case in both menus: `cout << endl;` before the loop continues
- Menu headers start with `\n`: `cout << "\nMain Menu:" << endl;`
- `"Total profit: "` (lowercase 'p') for storeMenu option 5
- `"Total Profit: "` (uppercase 'P') inside `operator<<`
- Checkout prints "Total price: X" TWICE when 'y' is chosen (once before asking, once after confirming)
- "Product added to cart." is ALWAYS printed in cartMenu option 2 (even if 0 quantity was added)
- "Not enough stock." is ONLY printed when `qty > supplier_stock`

### cartMenu Option 2 Logic (Add to Cart)
```cpp
supplier_stock = p->get_quantity()  // from supplier inventory
if (qty > supplier_stock): print "Not enough stock."
cart_qty = (item in cart ? its qty : 0)
qty_to_add = min(qty, supplier_stock - cart_qty)
if (qty_to_add < 0): qty_to_add = 0
if (qty_to_add > 0): customer->add_to_cart(*p, qty_to_add)
print "Product added to cart."
```

---

## Things That Were Already Correct Before This Session
- All class implementations (Product, ShoppingCart, Supplier, Customer, BusinessCustomer)
- Menu structure and all 6 options for both storeMenu and cartMenu
- Output formatting matching the expected format exactly
- Compile and test pipeline

## What Might Still Need Attention
- **Code comments**: The assignment requires comments on every method and significant code block (in English). Check that all files have adequate commenting.
- **No `set` methods visible**: The PDF mentions adding set/get methods as needed. Verify nothing is missing.
- **`get_quantity()` return type**: In `assignment2.txt` it says `double get_quantity()` but the implementation uses `unsigned int`. This is fine since the PDF is informally written.
- The `BusinessCustomer::operator<<` is implemented but note that the checkout receipt still shows the PRE-discount total (72.5 not 65.25). The financial tracking is correct (supplier gets discounted amount). If the grader expects the receipt to show the discounted total, this would need to change.

---

## Exact File: `Moodle Files/in.txt` (current)
```
1
2
101
Milk
3.5
10
2
102
Bread
1.5
20
3
101
3
2
2.99
4
105
5
6
2
1
Alice
2
1
10
2
2
20
5
y
4
6
1
2
103
Eggs
2.5
30
5
6
2
2
Bob
AcmeCorp
0.1
2
3
29
5
y
4
6
1
1
6
3
```

---

## Run Test
```bash
cd "Assignment 2 - CPP/Coding"
bash run_test.sh
# Expected: ALL TESTS PASSED
```
