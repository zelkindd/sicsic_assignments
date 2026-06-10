#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/**************************************************************************************************/
/***************************YOU MUST REMARK IT BEFORE SUBMISSION***********************************/
// #define DEBUGON
/***************************YOU MUST REMARK IT BEFORE SUBMISSION***********************************/
/**************************************************************************************************/

/* Submitters
Name1: Dan Zelkind     ID: 211571948
Name2: Privetname Familyname     ID: xxxxxxxx
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



/******************************************* your's functions ********************************************************************************/



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
            
			//your function

            break;

        case 'w':
            printf("Adding new warehouse.\n");

            printf("\n warehouse name: ");
            getstring(buf, 100);

            printf("\n warehouse code: ");
            scanf("%d", &num);
			
			printf("\n Add new warehouse: name %s warehouse code: %d",buf, num);
            
			//your function

            break;

        case 'a':
            printf("Assign an item to a warehouse.\n");

            printf("item ID: ");
            scanf("%d", &id);

            printf("warehouse code: ");
            scanf("%d", &num);

            //your function

            break;

        case 'u':
            printf("Remove an item from a warehouse.\n");

            printf("item ID: ");
            scanf("%d", &id);

            printf("warehouse code: ");
            scanf("%d", &num);

           //your function

            break;

        case 'p':
            printf("Printing status.\n");

            print_items(items);
            //your function

            break;
			
		case 'g':  // generating and assigning items and warehouses
			printf("Generating and assigning items to warehouses\n");
		
			//your function
			
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




