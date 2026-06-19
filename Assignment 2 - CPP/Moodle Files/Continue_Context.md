# Continue Context — Assignment 2 CPP

## Who You Are Talking To
This is a university C++ assignment (Assignment 2) by:
- Razel Elmoznino, ID: 206004095
- Dan Zelkind, ID: 211571948

A previous Claude Code session on a Windows machine did significant work. You are continuing on a Linux machine.
Read this file fully before doing anything.

---

## Project Structure

```
Assignment 2 - CPP/
├── Moodle Files/
│   ├── assignment2.cpp       ← main() entry point (DO NOT MODIFY)
│   ├── assignment2CPP2026B.pdf ← original assignment PDF
│   ├── in.txt                ← test input (pipe this into our exe)
│   ├── out.txt               ← exact expected output to match
│   ├── output2.4.exe         ← reference exe (Windows only, for testbench)
│   ├── steps.txt             ← step plan for this assignment
│   └── Continue_Context.md   ← this file
└── Coding/
    ├── Product.h / Product.cpp
    ├── ShoppingCart.h / ShoppingCart.cpp
    ├── Supplier.h / Supplier.cpp
    ├── Customer.h / Customer.cpp
    ├── Menu.h / Menu.cpp      ← NEWLY CREATED
```

---

## Step Plan (from steps.txt)

| Step | Description | Status |
|------|-------------|--------|
| 1 | Review assignment PDF | ✅ Done |
| 2 | Review existing class files | ✅ Done |
| 3 | Plan Menu class | ✅ Done |
| 4 | Implement Menu.h + Menu.cpp | ✅ Done |
| 4.5 | Fix broken functions in existing files | ✅ Done |
| 5 | Integrate assignment2.cpp | ✅ Done (it was already correct) |
| 6 | Compile and create exe | ❌ START HERE |
| 7 | Create detailed test plan | ❌ |
| 8 | Create testbench files to compare our exe vs out.txt | ❌ |
| 9 | Fix any failed tests until output matches exactly | ❌ |

---

## Step 6 — Compile Command

Run this from the `Coding/` directory:
```bash
g++ -o assignment2 "../Moodle Files/assignment2.cpp" Product.cpp ShoppingCart.cpp Supplier.cpp Customer.cpp Menu.cpp
```

Fix ALL compiler errors before moving on.

---

## Assignment Overview (from PDF)

This is a store management system with two sides:
- **Supplier side** — manages inventory, prices, stock, profit
- **Customer side** — browses store, adds to cart, checks out

### Classes Summary

**Product** — represents a product with auto-incremented ID, name, price, quantity.
- `static int next_id` starts at 1, increments on each new product creation
- Key operators: `==`, `!=`, `++`, `+=`, `-=`, `<<`

**ShoppingCart** — holds a list of Products and tracks total_price.
- `add_Product(p)` / `add_Product(p, qty)` — adds to cart, updates total
- `remove_Product(p)` / `remove_Product(p, qty)` — removes, updates total
- `Get_total()` — returns total price
- `operator[](int id)` — returns `Product*` by ID or nullptr
- `operator<<` — prints "Shopping Cart Details:" + items + "Total Price: X"
- `print_receipt()` — prints "Shopping Cart:" + items + "Total Price: X" (used at checkout)

**Supplier** — manages inventory vector and profit counter.
- `counter` starts at 0; DEBITED when stock is purchased (counter -= price*qty)
- `counter` CREDITED when customer checks out (counter += payment)
- `add_new_product(name, price, qty)` — creates Product, adds to inventory, debits counter
- `add_quantity(id, qty)` — adds qty to existing product, debits counter
- `find_product(id)` — returns `const Product*` or nullptr
- `change_price(id, new_price)` — updates price
- `remove_Product(p)` / `remove_Product(p, qty)` — removes from inventory
- `customer_purchases(Customer &c)` — validates stock, deducts inventory, calls c.checkout(), credits counter
- `operator<<` — prints "Supplier Details:" + all products + "Total Profit: X"

**Customer** — holds a ShoppingCart, name.
- `add_to_cart(p, qty)` — delegates to cart
- `remove_from_cart(id, qty)` — finds product in cart, delegates removal
- `checkout()` — returns total, empties cart
- `get_cart()` / `get_cart_modifiable()` — cart access

**BusinessCustomer** (inherits Customer) — has company_name, discount_rate.
- `checkout()` override — applies discount before returning total

**Menu** — manages all user I/O.
- `Supplier supplier` (composition)
- `Customer* customer` (pointer, initialized as `new Customer("")`)
- `mainMenu()` — public entry point
- `storeMenu()` — private, handles supplier menu
- `cartMenu()` — private, handles customer menu

---

## Exact Output Format (CRITICAL — must match out.txt character by character)

### Product::operator<<
```
Product ID: 1, Name: Milk, Price: 3.5, Quantity: 10
```

### Supplier::operator<<
```
Supplier Details:
Product ID: 1, Name: Milk, Price: 3.5, Quantity: 10
Product ID: 2, Name: Bread, Price: 2.99, Quantity: 20
Total Profit: -65
```

### ShoppingCart::operator<< (option 4 - view cart)
```
Shopping Cart Details:
Product ID: 2, Name: Bread, Price: 2.99, Quantity: 20
Product ID: 1, Name: Milk, Price: 3.5, Quantity: 10
Total Price: 94.8
```

### ShoppingCart::print_receipt() (checkout confirmation)
```
Shopping Cart:
Product ID: 2, Name: Bread, Price: 2.99, Quantity: 20
Product ID: 1, Name: Milk, Price: 3.5, Quantity: 10
Total Price: 94.8
```

### Main Menu
```

Main Menu:
1. Store Menu
2. Shopping Cart Menu
3. Exit
Enter your choice:
```

### Store Menu
```

Store Menu:
1. Print store
2. Add quantity to existing product or add new product
3. Change existing product price
4. Remove product from the store
5. View total profit
6. Exit
Enter your choice:
```

### Shopping Cart Menu
```

Shopping Cart Menu:
1. Print items in store
2. Add product to cart from store
3. Remove product
4. View cart
5. Check out
6. Exit
Enter your choice:
```

---

## Menu Logic — Exact Behavior Per Option

### storeMenu()

**Option 1 (Print store):**
```
cout << supplier;
```

**Option 2 (Add product or quantity):**
```
cout << supplier;
"Enter product ID: " → read id
if not found:
    "Product not found."
    "Adding new product."
    "Enter product name: " → read name
    "Enter product price: " → read price
    "Enter quantity: " → read qty
    supplier.add_new_product(name, price, qty)
    "Product added."
if found:
    "Product found: " + *find_product(id)
    "Enter quantity to add: " → read qty
    supplier.add_quantity(id, qty)
    "Quantity updated."
```

**Option 3 (Change price):**
```
cout << supplier;
"Enter product ID: " → read id
if not found: "Product not found."
if found:
    "Product found: " + *find_product(id)
    "Enter new price: " → read price
    supplier.change_price(id, price)
    "Price updated successfully."
```

**Option 4 (Remove product):**
```
cout << supplier;
"Enter product ID: " → read id
if not found: "Product not found."
if found:
    supplier.remove_Product(*find_product(id))
    "Product removed."
```

**Option 5 (Total profit):**
```
"Total profit: " + supplier.get_total_profit()
```
NOTE: lowercase 'p' in "profit" here!

**Option 6 (Exit):**
```
"Exiting supplier menu."
return;
```

**Invalid:**
```
"Invalid option. Please try again."
```

After EVERY case (including 6 before return): `cout << endl;`

---

### cartMenu()

**Option 1 (Print items in store):**
```
"Items in the store:"
cout << supplier;
```

**Option 2 (Add product to cart):**
```
"Items in the store:"
cout << supplier;
"Enter product ID to add: " → read id
if not found: "Product not found."
if found:
    "Enter quantity: " → read qty
    supplier_stock = find_product(id)->get_quantity()
    if qty > supplier_stock: "Not enough stock."
    cart_qty = (product in cart ? its quantity : 0)
    qty_to_add = min(qty_capped_to_supplier_stock, supplier_stock - cart_qty)
    if qty_to_add > 0: customer->add_to_cart(*p, qty_to_add)
    "Product added to cart."
```

IMPORTANT: `qty_capped = min(qty, supplier_stock)`. Then `qty_to_add = min(qty_capped, supplier_stock - cart_qty)`.
"Product added to cart." is ALWAYS printed (even if 0 was added).
"Not enough stock." is ONLY printed when `qty > supplier_stock`.

**Option 3 (Remove product from cart):**
```
"Items in the cart:"
cout << customer->get_cart();
"Enter product ID to remove: " → read id
"Enter quantity to remove: " → read qty
if customer->remove_from_cart(id, qty) fails: "Product not found in cart."
else: "Product removed."
```

**Option 4 (View cart):**
```
"Items in the cart:"
cout << customer->get_cart();
```

**Option 5 (Checkout):**
```
total = customer->get_cart().Get_total()
"Total price: " + total
"Would you like to check out? (y/n): " → read confirm
if confirm == 'y':
    "Total price: " + total       ← printed AGAIN
    customer->get_cart().print_receipt()
    supplier.customer_purchases(*customer)   ← deducts stock, clears cart, updates counter
```
NOTE: on 'n' → do nothing, just let the loop continue.

**Option 6 (Exit):**
```
"Exiting shopping cart menu."
return;
```

**Invalid:**
```
"Invalid option. Please try again."
```

After EVERY case: `cout << endl;`

---

## Key Behavioral Facts

1. **Profit tracking**: `counter -= price * qty` when supplier buys stock. `counter += payment` when customer checks out.
2. **Cart persistence**: cart is NOT reset between Shopping Cart menu sessions. It persists on the Customer object.
3. **No customer type prompt**: Main menu option 2 goes straight to cartMenu(). The test input does NOT include customer name/type input.
4. **"Total profit:" vs "Total Profit:"**: Option 5 uses lowercase 'p'. The operator<< uses uppercase 'P'.
5. **Blank line rule**: After every menu operation, `cout << endl` is printed before the menu loops and reprints.
6. **Menu headers start with endl**: Each menu (main, store, cart) starts with `cout << "\nStore Menu:" << endl` etc.

---

## Step 7 — Test Plan

After compiling, create a test plan that covers:
- All 6 store menu options (including not-found and found cases)
- All 6 cart menu options (including not-found, not enough stock, exact stock, partial stock)
- Checkout with 'y' and 'n'
- Cart persistence across sessions
- Profit calculation correctness
- Invalid menu options

---

## Step 8 — Testbench

Create a shell script that:
1. Runs `./assignment2 < "../Moodle Files/in.txt" > our_output.txt`
2. Compares `our_output.txt` with `Moodle Files/out.txt` using `diff`
3. Reports PASS or FAIL with line differences shown

Example script (`run_test.sh` in Coding/):
```bash
#!/bin/bash
./assignment2 < "../Moodle Files/in.txt" > our_output.txt 2>&1
diff our_output.txt "../Moodle Files/out.txt"
if [ $? -eq 0 ]; then
    echo "ALL TESTS PASSED"
else
    echo "DIFFERENCES FOUND - see above"
fi
```

---

## Step 9 — Fix Failures

Compare diff output line by line. Common issues to look for:
- Extra/missing blank lines
- Wrong text in headers ("Shopping Cart Details:" vs "Shopping Cart:")
- "Total profit:" vs "Total Profit:" casing
- Missing endl after operations
- Wrong order of print statements in menu options

Fix each difference, recompile, re-run testbench until `diff` is clean.

---

## What The Previous Session Could NOT Verify

The Windows shell could not capture g++ stderr, so the compiled code was NEVER tested.
Menu.cpp and the fixes to existing files were written correctly based on careful analysis of in.txt and out.txt but may have compile errors or logic bugs. Trust the testbench output, not assumptions.
