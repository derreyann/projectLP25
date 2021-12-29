#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils.h"
#include "database.h"
#include "sql.h"
#include "table.h"
#include "check.h"

#define SQL_COMMAND_MAX_SIZE 1500

int main(int argc, char *argv[]) {

    // Here: check parameters with getopt
    // -d database_name
    // -l directory of the parent database folder (default: current directory)
    //create table
    create_query_t table;
    strcpy(table.table_name, "test");
    table.table_definition.fields_count=2;
    strcpy(table.table_definition.definitions[0].column_name, "field");
    strcpy(table.table_definition.definitions[1].column_name, "field2");
    table.table_definition.definitions[0].column_type = TYPE_INTEGER;
    table.table_definition.definitions[1].column_type = TYPE_PRIMARY_KEY;
    create_query_t *ptable = &table;

    
    char buffer[SQL_COMMAND_MAX_SIZE];
    query_result_t query;
    
    do {
        printf("> ");
        fflush(stdin);
        if (fgets(buffer, SQL_COMMAND_MAX_SIZE, stdin) == NULL)
            continue;
        buffer[strlen(buffer)-1] = '\0';
        if (strcmp(buffer, "exit") == 0)
            break;
        
        printf("%s\n", buffer);

        if(parse(buffer, &query) == NULL) {
            continue;
        }

        
        // Here: parse SQL, check query, execute query
        if (strcmp(buffer, "drop") == 0)
            drop_table("test");
        if (strcmp(buffer, "create") == 0)
            create_table(ptable);
        if (strcmp(buffer, "free idx") == 0)
            printf("free index: %d\n", find_first_free_record("test"));
    } while (true);

    return 0;
}
