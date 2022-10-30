#pragma once
/* Downloads the specified page from the specified address. You can set the following parameters:
adress: Server address e.g. "de.wikipedia.org"
page: Page on the specified server e.g. "/wiki/Intelligentes_Wohnen"

The memory where the returned pointer points to must be deallocated with function free().
*/
char* httpget(char* adress, char* page);