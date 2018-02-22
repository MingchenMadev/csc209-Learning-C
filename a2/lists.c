#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lists.h"
/*
 * Return a pointer to the struct calendar with name cal_name
 * or NULL if no calendar with this name exists in the cal_list
 */
Calendar *find_calendar(Calendar *cal_list, char *cal_name) {
    Calendar * current;
    current = cal_list;
    // go through al the calendars return the one with cal_name as its name
    while(current!= NULL){
	    if(!strncmp(current->name, cal_name, sizeof(cal_name))){
		  return current;
	    }
        current = current->next;
    }
    //If after i reach the end of the linked list i still couldnt find the calendar with name = cal_name
    // I return NULL
    return NULL;
}


/* 
 * Return a pointer to the user with name username or NULL
 *   if no such user exists in user_list 
 */
User *find_user(User *user_list, char *username) {
    User * current;
    current = user_list;
    // go through al the calendars return the one with username as its name
    while(current != NULL){
	    if(strcmp(current->name, username) == 0){
            return current;
	    }
        current = current->next;
    }
    //If after i reach the end of the linked list i still couldnt find the user with name = username
    // I return NULL
    return NULL;
}


/* 
 * If a calendar with name cal_name does not exist, create a new
 * calendar by this name and insert it at the front of the calendar list.
 * Return values:
 *    0 if successful
 *   -1 if a calendar by cal_name already exists
 */
int add_calendar(Calendar **cal_list_ptr, char *cal_name) {
    Calendar * new_calendar;
    if ((new_calendar = malloc(sizeof(Calendar))) == NULL){
         perror("malloc");
         exit(1);
    }
    if(find_calendar(*cal_list_ptr, cal_name)!= NULL){
    	return -1;
    }else{
        new_calendar->name = malloc(strlen(cal_name) + 1);
        strcpy(new_calendar->name, cal_name);
        //Base case, if it is the first calendar
        //Then I make head points to new calendar
        if(*cal_list_ptr == NULL){
            *cal_list_ptr = new_calendar;
        }else{
            // I make head points to my new calendar and my new calendar points to what head used to point to
            // this way i make my new calendar the first calendar in my linked list  
            new_calendar->next = *cal_list_ptr;
            *cal_list_ptr = new_calendar;
        }
    }
    return 0;
}

/* 
 * Print to stdout a list of all current calendar names (one per line)
 */
void list_calendars(Calendar *cal_list) {
    Calendar * current = cal_list;
    //Go through all the calendars using a while loop, print to stdout each name of the calendar line by line
    //stops when it reaches NULL, the end of the linked list structure
    while(current != NULL){
	   fprintf(stdout, "%s\n", current->name);
	   current = current->next;
    }
}


/* 
 * If a user with name username does not exist, create a new
 * user by this name and insert it at the end of the user list.
 * Return values:
 *    0 if successful
 *   -1 if username already exists
 */
int add_user(User **user_list_ptr, char *username) {
    User * new_user;
    //If username already existsm i return -1 and exit my function
    if(find_user(*user_list_ptr, username) != NULL){
    	return -1;
    }else{
        if((new_user = malloc(sizeof(User))) == NULL) {
         perror("malloc");
         exit(1);
        }
        new_user->name = malloc(strlen(username) + 1);
        strcpy(new_user->name, username);
        User * current = *user_list_ptr;
        //Base case, if there is no user in my head, then I am trying to add the first user
        //I make my head points to new user
        if(current == NULL){
            *user_list_ptr = new_user;
        }
        else{
            //Other wise, I go to the end of my linked list and make the end points to new user
            while(current->next!= NULL){
                current = current->next;
            }
            current->next = new_user;
            return 0;
        }
    }
    return 0;
}


/* 
 * Print to stdout a list of usernames one per line 
 */
void list_users(User *user_list){
    User * current = user_list;
    //Go through all the users using a while loop, print to stdout each username of the user line by line
    //stops when it reaches NULL, the end of the linked list structure
    while(current != NULL){
	   fprintf(stdout, "%s\n", current->name);
	   current = current->next;
    }
}


/*
 * Subscribe the user username to calendar cal_name
 * Return:
 *    0 if successful
 *   -1 if no user exists by this name
 *   -2 if no calendar exists by this name
 *   -3 if this user is already subscribed to this calendar
 */
int subscribe(User *user_list, Calendar *cal_list, char *username, char *cal_name) {
    if(find_user(user_list, username) == NULL){
	   return -1;
    }
    if(find_calendar(cal_list, cal_name) == NULL){
	   return -2;
    }
    User * my_user = find_user(user_list, username);
    Calendar * my_calendar = find_calendar(cal_list, cal_name);
    Subscription * sub = malloc(sizeof(Subscription));
    sub->calendar = my_calendar;
    sub->next = NULL;
    if(my_user->subscriptions == NULL){
        my_user->subscriptions = sub;
        return 0;
    }else{
        Subscription * current = my_user->subscriptions;
        while(current){
            if(!strcmp(current->calendar->name, cal_name)){
                return -3;
            }
            current = current->next;
        }
    }
    Subscription * current1 = my_user->subscriptions;
    while(current1->next != NULL){
        current1 = current1->next;
    }
    current1->next = sub;
    return 0;
}


/* 
 * Add an event with this name and date to the calender with name cal_name 
 *  Return:
 *   0 for success
 *  -1 for calendar does not exist by this name
 */
int add_event(Calendar *cal_list, char *cal_name, char *event_name, time_t time) {
    Calendar * my_calendar = malloc(sizeof(Calendar));
    Event * new_event;
    if(((new_event = malloc(sizeof(Event))) == NULL)){
         perror("malloc");
         exit(1);
    }
    new_event->time = time;
    new_event->description = malloc(strlen(event_name) + 1);
    strcpy(new_event->description, event_name);
    my_calendar = find_calendar(cal_list, cal_name);
    //If my calendar does not exist by this name, i return -1 and exit the method
    if(my_calendar == NULL){
	   return -1;
    }
    //Base case, if there is no event, make the head points to my new event
    Event * current = my_calendar->events;
    if(current == NULL){
        my_calendar->events = new_event;
    //Else, I found the link I try to break and add my new event to the linked list
    }else{
        while(current->next!= NULL){
            if(difftime(time, current->time) < 0){
                new_event->next = current->next;
                current->next = new_event;
                return 0;
            }
            current = current->next;
        }
        //If i didnt return 0 in my while loop, that means that my event is the lastest
        //then i added to the end of my linked list
        new_event->next = current->next;
        current->next = new_event;
    }
    return 0;
}

/* 
 * Print to stdout a list of the events in this calendar ordered by time
 *  Return:
 *     0 if successful
 *    -1 if no calendar exists by this name
 */
int list_events(Calendar *cal_list, char *cal_name) {
    //if no calendar exists by this name i return -1
    if(find_calendar(cal_list, cal_name) == NULL){
	   return -1;
    }
    //Otherwise if it exists, I go thourgh this calendar
    //and print the descripition to stdout.
    Event * current = find_calendar(cal_list, cal_name)->events;
    while(current != NULL){
	   fprintf(stdout,"%s\n",current->description);
	   current = current->next;
    }
    return 0;
}
/* 
 * Print to stdout, the description and time of the next event for 
 * user user_name
 *  Return:
 *   0 on success
 *   -1 if this user_name does not exist or has no events
 */
int print_next_event(Calendar *cal_list, User * user_list, char *user_name) {
    User * my_user;
    Event * my_next_events = malloc(sizeof(Event));
    my_user = find_user(user_list, user_name);
    //I check if any of the pointers that I try to call be a NULL
    //To avoid seg Fault
    if(my_user == NULL || my_user->subscriptions == NULL|| my_user->subscriptions->calendar->events == NULL){
	   return -1;
    }
    if((my_next_events = my_user->subscriptions->calendar->events) == NULL){
        return -1;
    }
    //I found my earlist event in my calendar, and I print its descrption and time to stdout
    fprintf(stdout,"%s\n",my_next_events->description);
    fprintf(stdout,"%s\n",ctime(&my_next_events->time));
    return 0;
}


/* 
 * Print to stdout a time-ordered list of all events in any calendars
 *  subscribed to by this user 
 *
 *  Do not change the calendar data-structure. 
 *  Return -1 if this user doesn't exist.
 */
int print_all_events(Calendar *cal_list, User * user_list, char *user_name) {
    User * my_user;
    Calendar * events_to_print;//Create a calendar called events to print
    if(((events_to_print = malloc(sizeof(Calendar))) == NULL)){
         perror("malloc");
         exit(1);
    }
    my_user = find_user(user_list, user_name);
    if(my_user == NULL){
       return -1;
    }
    Calendar * cal = my_user->subscriptions->calendar;
    Event * current;
    events_to_print->name = malloc(sizeof("events_to_print"));
    strcpy(events_to_print->name, "events_to_print");//give this calendar a name
    //For every events in every calendar, I use the add_events function to add to calendar
    //events_to_print, because when ever I add event to my calendar, my add_event function
    //will make sure that the calendar events_to_print is in order of the events time
    while(cal != NULL){
        current = cal->events;
        while(current != NULL){
            add_event(events_to_print, events_to_print->name, current->description, current->time);
            current = current->next;
        }
        cal = cal->next;
    }
    //use list_events to print all the events in this calendar, since with the assumation of my
    // add_event working, all events added by add_events will be in order, so when i print to stdout
    // the result is correct
    list_events(events_to_print, events_to_print->name);
    free(events_to_print);
    return 0;
}
