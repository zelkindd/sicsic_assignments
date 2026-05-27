#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/**************************************************************************************************/
/***************************YOU MUST REMARK IT BEFORE SUBMISSION***********************************/
#define DEBUGON
/***************************YOU MUST REMARK IT BEFORE SUBMISSION***********************************/
/**************************************************************************************************/

/* Submitters
Name1: Razel Elmoznino    ID: 206004095
Name2: Dan Zelkind        ID: 211571948
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* structures */
typedef struct item {
    char* name;
    int  id;
    struct wlst* warehouses;
} item;

typedef struct warehouse {
    char* location;
    int  code;
    struct itemlst* items;
} warehouse;

typedef struct itemlst {
    item* data;
    struct itemlst* next;
} itemlst;

typedef struct wlst {
    warehouse* data;
    struct wlst* next;
} wlst;


/******************************************* your's prototypes *******************************************************************************/

item* find_item_by_id(itemlst* head, int id);
warehouse* find_warehouse_by_code(wlst* head, int code);
void add_item(itemlst** head, char* name, int id);
void add_warehouse(wlst** head, char* name, int code);
void print_items(itemlst* head);
void print_warehouses(wlst* head);
void assign_item_to_warehouse(itemlst* item_head, wlst* w_head, int item_id, int w_code);
void unassign_item_to_warehouse(itemlst* item_head, wlst* w_head, int item_id, int w_code);
void print_error_message(int errid);

/******************************************* your's functions ********************************************************************************/

/* Errors:
 * 1: new item malloc fail
 * 2: name malloc fail
 * 3: itemlist malloc fail
 * 4: warehouse malloc fail
 * 5: location malloc fail
 * 6: wlist malloc fail
 * 7: wlist malloc fail
*/



//Search for an item in the main list by ID
item *find_item_by_id(itemlst *head, int id) {
    itemlst *temp = head;
    while (temp != NULL) {
        if (temp->data->id == id) {
            return temp->data; //Item found, return a pointer to it
        }
        temp = temp->next;
    }
    return NULL; //The item does not exist in the list
}

itemlst *find_item_node(itemlst *head, int id) {
    //return the node
    itemlst *temp = head;
    while (temp != NULL) {
        if (temp->data->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; //The item does not exist in the list
}





//Search for a warehouse in the main list by code
warehouse *find_warehouse_by_code(wlst *head, int code) {
    wlst *temp = head;
    while (temp != NULL) {
        if (temp->data->code == code) {
            return temp->data; //Warehouse found, return a pointer to it
        }
        temp = temp->next;
    }
    return NULL; //The warehouse does not exist in the list
}

wlst *find_warehouse_node(wlst *head, int code) {
    wlst *temp = head;
    while (temp != NULL) {
        if (temp->data->code == code) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; //The warehouse does not exist in the list
}


//Adds a new item to the main linked list
void add_item(itemlst **head, char *name, int id) {
    if (find_item_by_id(*head, id) != NULL) {
        return; //Item exists, nothing added to the list
        // SHOULD IT RETURN THE ITEM? (cross with the reference)
    }
    //Allocate memory for the item structure
    item *new_item = (item *) malloc(sizeof(item));
    if (new_item == NULL) {
        print_error_message(1);
    }
    //Allocate memory for the item's name string
    new_item->name = (char *) malloc(strlen(name) + 1);
    if (new_item->name == NULL) {
        free(new_item);
        print_error_message(2);
    }
    //copy the data
    strcpy(new_item->name, name);
    new_item->id = id;
    new_item->warehouses = NULL;
    //Allocate memory for the main list node
    itemlst *new_node = (itemlst *) malloc(sizeof(itemlst));
    if (new_node == NULL) {
        free(new_item->name);
        free(new_item);
        print_error_message(3);
    }
    new_node->data = new_item;
    new_node->next = NULL;
    //Insert the new node at the end of the main items list
    if (*head == NULL) {
        // head is the only node
        *head = new_node;
    } else {
        // find the last node in the list
        itemlst *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

//Adds a new warehouse to the main linked list
void add_warehouse(wlst **head, char *name, int code) {
    if (find_warehouse_by_code(*head, code) != NULL) {
        return; //Warehouse exists, nothing added to the list
    }
    //Allocate memory for the warehouse structure
    warehouse *new_warehouse = (warehouse *) malloc(sizeof(warehouse));
    if (new_warehouse == NULL) {
        print_error_message(4);
    }
    //Allocate memory for the warehouse location string
    new_warehouse->location = (char *) malloc(strlen(name) + 1);
    if (new_warehouse->location == NULL) {
        free(new_warehouse);
        print_error_message(5);
    }
    //copy the data
    strcpy(new_warehouse->location, name);
    new_warehouse->code = code;
    new_warehouse->items = NULL;
    //Allocate memory for the main list node
    wlst *new_node = (wlst *) malloc(sizeof(wlst));
    if (new_node == NULL) {
        free(new_warehouse->location);
        free(new_warehouse);
        print_error_message(6);
    }
    new_node->data = new_warehouse;
    new_node->next = NULL;
    //Insert the new node at the end of the main warehouses list
    if (*head == NULL) {
        *head = new_node;
    } else {
        wlst *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

//Prints the entire list of items in the system
void print_items(itemlst *head) {
    printf("item LIST:\n");
    itemlst *temp = head;
    while (temp != NULL) {
        if (temp->data != NULL) {
            printf("%d:%s\n", temp->data->id, temp->data->name);

            // If this item is assigned to any warehouses - print them
            if (temp->data->warehouses != NULL) {
                printf("Item Warehouses: ");
                wlst *sub_w = temp->data->warehouses;
                while (sub_w != NULL) {
                    if (sub_w->data != NULL) {
                        printf("%d-%s", sub_w->data->code, sub_w->data->location);
                    }
                    // if there's another warehouse next
                    if (sub_w->next != NULL) {
                        printf(", ");
                    }
                    sub_w = sub_w->next;
                }
                printf("\n");
            }
        }
        temp = temp->next;
    }
}

//Prints the entire list of warehouses in the system
void print_warehouses(wlst *head) {
    printf("warehouse LIST:\n");
    wlst *temp = head;
    while (temp != NULL) {
        if (temp->data != NULL) {
            printf("Warehouse code %d, Warehouse name: %s\n", temp->data->code, temp->data->location);

            // If this warehouse contains any items, print them
            if (temp->data->items != NULL) {
                printf("items: ");
                itemlst *sub_i = temp->data->items;
                while (sub_i != NULL) {
                    if (sub_i->data != NULL) {
                        // Exact required format: ID X Name Y |
                        printf("ID %d Name %s | ", sub_i->data->id, sub_i->data->name);
                    }
                    sub_i = sub_i->next;
                }
                printf("\n");
            }
        }
        temp = temp->next;
    }
}

void assign_item_to_warehouse(itemlst *item_head, wlst *w_head, int item_id, int w_code) {
    // locate item and warehouse nodes
    item *target_item = find_item_by_id(item_head, item_id);
    warehouse *target_w = find_warehouse_by_code(w_head, w_code);
    if (target_w == NULL || target_item == NULL) {
        return;
    }

    // ** Create a new connection node for the item's warehouse list
    wlst *new_w_node = (wlst *) malloc(sizeof(wlst));
    if (new_w_node == NULL) {
        print_error_message(7);
    }
    new_w_node->data = target_w;
    new_w_node->next = NULL;

    // Insert new_w_node at the end of target_item->warehouses sub-list
    if (target_item->warehouses == NULL) {
        target_item->warehouses = new_w_node;
    } else {
        wlst *temp_w = target_item->warehouses;
        while (temp_w->next != NULL) {
            temp_w = temp_w->next;
        }
        temp_w->next = new_w_node;
    }

    // ** Create a new connection node for the warehouse's item list
    itemlst *new_i_node = (itemlst *) malloc(sizeof(itemlst));
    if (new_i_node == NULL) {
        free(new_w_node);
        print_error_message(8);
    }
    new_i_node->data = target_item;
    new_i_node->next = NULL;

    // Insert new_i_node at the end of target_warehouse->items sub-list
    if (target_w->items == NULL) {
        target_w->items = new_i_node;
    } else {
        itemlst *temp_i = target_w->items;
        while (temp_i->next != NULL) {
            temp_i = temp_i->next;
        }
        temp_i->next = new_i_node;
    }
}

void unassign_item_to_warehouse(itemlst *item_head, wlst *w_head, int item_id, int w_code) {
// remove the item from warehouse's linkedlist
    // find the warehouse in wh main
    wlst *target_w = find_warehouse_node(w_head, w_code);
    if (target_w == NULL) {return;}

    itemlst *curr_item = target_w->data->items;
    itemlst *prev_item = NULL;

    if (curr_item != NULL && curr_item->data->id == item_id) {
        // first node is the one to remove
        itemlst *to_free = curr_item;
        target_w->data->items = curr_item->next;
        free(to_free);
        curr_item = NULL; // skip the while loop below
    }

    while (curr_item != NULL) {
        if (curr_item->data->id == item_id) {
            prev_item->next = curr_item->next;
            free(curr_item);
            break;
        }
        prev_item = curr_item;
        curr_item = curr_item->next;
    }
    

    // remove the warehouse from the item's linkedlist
    item *target_item = find_item_by_id(item_head, item_id);
    if (target_item == NULL) { return; }

    wlst *curr_w = target_item->warehouses;
    wlst *prev_w = NULL;

    if (curr_w != NULL && curr_w->data->code == w_code) {
        wlst *to_free = curr_w;
        target_item->warehouses = curr_w->next;
        free(to_free);
        curr_w = NULL;
    }

    while (curr_w != NULL) {
        if (curr_w->data->code == w_code) {
            prev_w->next = curr_w->next;
            free(curr_w);
            break;
        }
        prev_w = curr_w;
        curr_w = curr_w->next;
    }

}

/*****************************************new objects and insert object functions******************************************************/



/****************************************find Matchings and register item to Warehouse*************************************************/



/********************************************uregisters objects*************************************************************************/



/***********************************************printout functions***********************************************************************/


/***************************************************free**********************************************************************************/


/*******************************************Generate And Assign Items And Warehouses******************************************************/


/*DO NOT TOUCH THIS FUNCTION */
void getstring(char* buf, int length) {
    int len;
    //buf = fgets(buf, length, stdin);
	scanf("%s", buf);
    len = (int)strlen(buf);
    if (buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}


/*DO NOT TOUCH THIS FUNCTION */

void print_error_message(int errid) {
	#ifdef DEBUGON
	fprintf(stderr, "BGU ERROR %d\n", errid);
	#else
	fprintf(stderr, "BGU ERROR\n");	
	#endif
	exit(-1);
}

/*DO NOT TOUCH THIS MAIN TEMPLATE - ONLY ADD YOUR FUNCTIONS CALLS */
int main() {
    itemlst* items = 0;
    wlst* warehouses = 0;
    char  c;
    char  buf[100];
    int   id, num;
	


    do {
        printf("Choose:\n"
            "    i - new item\n"
            "    w - new warehouse\n"
            "    a - assign an item to a warehouse\n"
            "    u - unassign an item from a warehouse(not delete!)\n"
            "    p - print status\n"
			"    g - generating and assigning 100 items to 10 warehouses\n"
            "    q - quit\n");

        while ((c = (char)getchar()) == '\n');
        getchar();

        switch (c) {
        case 'i':
            printf("Adding new item.\n");

            printf("item name: ");
            getstring(buf, 100);
			

            printf("item ID: ");
            scanf("%d", &id);
			
			printf("\n Add new item: name %s item id: %d",buf, id);

            add_item(&items, buf, id);

            break;

        case 'w':
            printf("Adding new warehouse.\n");

            printf("\n warehouse name: ");
            getstring(buf, 100);

            printf("\n warehouse code: ");
            scanf("%d", &num);
			
			printf("\n Add new warehouse: name %s warehouse code: %d",buf, num);

            add_warehouse(&warehouses, buf, num);

            break;

        case 'a':
            printf("Assign an item to a warehouse.\n");

            printf("item ID: ");
            scanf("%d", &id);

            printf("warehouse code: ");
            scanf("%d", &num);

            assign_item_to_warehouse(items, warehouses, id, num);

            break;

        case 'u':
            printf("Remove an item from a warehouse.\n");

            printf("item ID: ");
            scanf("%d", &id);

            printf("warehouse code: ");
            scanf("%d", &num);

           unassign_item_to_warehouse(items, warehouses, id, num);

            break;

        case 'p':
            printf("Printing status.\n");

            print_items(items);
            print_warehouses(warehouses);

            break;
			
		case 'g':  // generating and assigning items and warehouses
			printf("Generating and assigning items to warehouses\n");

			srand(1948);
			for (int i = 0; i < 10; i++) {
				strcpy(buf, "Warehouse");
				buf[9] = '0' + i;
				buf[10] = '\0';
				add_warehouse(&warehouses, buf, i);
			}
			for (int i = 0; i < 100; i++) {
				strcpy(buf, "Item");
				if (i < 10) {
					buf[4] = '0' + i;
					buf[5] = '\0';
				} else {
					buf[4] = '0' + i / 10;
					buf[5] = '0' + i % 10;
					buf[6] = '\0';
				}
				add_item(&items, buf, i);
				int randomCode = rand() % 10;
				assign_item_to_warehouse(items, warehouses, i, randomCode);
			}

			break;

        case 'q':
            printf("Quitting...\n");
            break;
        }

        if (c != 'q')
            printf("\n");
    } while (c != 'q');

    //your free functions
	return 0;
    
}




