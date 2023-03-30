#include <stdio.h>
#include <string.h>
#include <math.h>
#include <err.h>
#include <gmodule.h>
#include "set.h"
#include "dict.h"
#include "automaton.h"
#include "btree.h"
#include "vector.h"

//Initializes a new automaton
automaton* new_automaton()
{
    //allocating memory space on heap
    automaton* autom;
    autom = malloc(sizeof(struct automaton));

    autom->order = 0;
    //Initialising the sets
    autom->initial_states = new_set(4);
    autom->final_states = new_set(4);
    autom->alphabet = new_set(4);

    //Initializing adjlist
    autom->adjlists = malloc(sizeof(struct list));
    autom->adjlists->arc = NULL;
    autom->adjlists->next_arc = NULL;
    autom->adjlists->next_node = NULL;

    return autom;
}

//Adds a state to the automaton
void add_state_automaton(automaton* autom)
{
    //Incrementing automaton size
    autom->order += 1;

    //Adding an adjlist to the automaton
    struct list* search = autom->adjlists;
    while(search->next_node != NULL)
    {
        search = search->next_node;
    }
    struct list* l = malloc(sizeof(struct list));
    l->next_arc = NULL;
    l->next_node = NULL;
    l->arc = NULL;
    search->next_node = l;
}

//Function that returns the list at the position of index index
list* find_list(automaton* autom, ssize_t index)
{
    if(index == -1)
        return autom->adjlists;

    if((size_t) index >= autom->order)
        errx(1, "Trying to access inexistant node");
    struct list* search = autom->adjlists->next_node;
    while(search != NULL && index > 0)
    {
        search = search->next_node;
        index--;
    }
    return search;
}

//Adds an arc to the automaton
void add_arc_automaton(automaton* autom, size_t start, size_t end,
        char* letter)
{
    //Handling error of adding an arc to a node that doesn't exist
    if(start >= autom->order || end >= autom->order)
        errx(1, "Trying to add an arc to an inexistant node\n");

    //Insering the letter of the arc in the alphabet set of the automaton
    insert_set(&(autom->alphabet), letter);

    struct list* search = find_list(autom, start);
    while(search->next_arc != NULL)
    {
        //Checking that the arc doesn't already exist
        if(search->next_arc->arc->end == end
                && strcmp(search->next_arc->arc->letter, letter) == 0)
            return;
        search = search->next_arc;
    }

    //Creating new arc
    struct arc* a = malloc(sizeof(struct arc));
    a->end = end;
    a->letter = letter;
    struct list* l = malloc(sizeof(struct list));
    l->arc = a;
    l->next_arc = NULL;
    l->next_node = NULL;
    search->next_arc = l;
}

//Thompson algorithm that builds the automaton from an the AST regex
void Thompson(automaton* autom, size_t origin, size_t destination,
        btree* regex)
{
    //Concatenation case
    if(strcmp(regex->key, ".") == 0)
    {
        add_state_automaton(autom);
        add_state_automaton(autom);
        size_t p = autom->order - 2;
        size_t r = autom->order - 1;
        add_arc_automaton(autom, p, r, "ε");
        Thompson(autom, origin, p, regex->child1);
        Thompson(autom, r, destination, regex->child2);

    }
    //Union case
    else if(strcmp(regex->key, "+") == 0)
    {
        add_state_automaton(autom);
        add_state_automaton(autom);
        size_t p1 = autom->order - 2;
        size_t p2 = autom->order - 1;
        Thompson(autom, p1, p2, regex->child1);
        add_arc_automaton(autom, origin, p1, "ε");
        add_arc_automaton(autom, p2, destination, "ε");

        add_state_automaton(autom);
        add_state_automaton(autom);
        size_t r1 = autom->order - 2;
        size_t r2 = autom->order - 1;
        Thompson(autom, r1, r2, regex->child2);
        add_arc_automaton(autom, origin, r1, "ε");
        add_arc_automaton(autom, r2, destination, "ε");
    }
    //Kleene star case
    else if(strcmp(regex->key, "*") == 0)
    {
        add_arc_automaton(autom, origin, destination, "ε");
        add_state_automaton(autom);
        add_state_automaton(autom);
        size_t p = autom->order - 2;
        size_t r = autom->order - 1;
        Thompson(autom, p, r, regex->child2);
        add_arc_automaton(autom, origin, p, "ε");
        add_arc_automaton(autom, r, destination, "ε");
        add_arc_automaton(autom, r, p, "ε");
    }
    //Leaf case (or letter case)
    else
    {
        add_arc_automaton(autom, origin, destination, regex->key);
    }
}

//Build enfa from btree
void build_enfa(automaton* autom, btree* regex)
{
    add_state_automaton(autom);
    add_state_automaton(autom);
    insert_set(&(autom->initial_states), "0");
    insert_set(&(autom->final_states), "1");
    Thompson(autom, 0, 1, regex);
}

//Returns set of epsilon closure of a state of the automaton
set* get_epsilon_closure(automaton* autom, char* origin)
{
    //Initializing sets
    set* incoming = new_set(4);
    insert_set(&incoming, origin);
    set* result = new_set(4);

    char* val;
    int s;
    //We keep on going while the incoming set isn't empty
    while(incoming->len > 0)
    {
        //Poping random value from set
        val = pop_set(incoming);

        //If node already in result, we continue
        if(search_set(result, val) == 1)
            continue;

        //Inserting val in the result set
        insert_set(&result, val);

        list* l = find_list(autom, atoi(val));

        //Going through adjlist to add the states that can be reached using
        //an epsilon transition to the incoming set
        while(l->next_arc != NULL)
        {
            l = l->next_arc;
            if(strcmp(l->arc->letter, "ε") != 0)
                continue;

            //Dynamically allocating a string for the node number
            s = (int)((ceil(log10(l->arc->end))+1)*sizeof(char));
            char* str = malloc(s);

            sprintf(str, "%zu", l->arc->end);

            insert_set(&incoming, str);
        }
    }
    return result;
}

//Transform a enfa into a nfa
automaton* to_nfa(automaton* autom)
{
    //Initialising new automaton
    automaton* nfa = new_automaton();
    nfa->order = autom->order;
    union_set(&nfa->initial_states, autom->initial_states);
    union_set(&nfa->final_states, autom->final_states);
    union_set(&nfa->alphabet, autom->alphabet);

    //Removing the epsilon letter from the alphabet
    delete_set(nfa->alphabet, "ε");

    //Initialzing adjlists
    nfa->adjlists = malloc(sizeof(struct list));
    nfa->adjlists->arc = NULL;
    nfa->adjlists->next_arc = NULL;
    nfa->adjlists->next_node = NULL;

    //Creating an adjlist for each node
    list* search = nfa->adjlists;
    for(size_t i = 0; i < nfa->order; ++i)
    {
        struct list* l = malloc(sizeof(struct list));
        l->next_arc = NULL;
        l->next_node = NULL;
        l->arc = NULL;
        search->next_node = l;
        search = search->next_node;

    }

    int si;
    //For each state of the automaton
    for(size_t i = 0; i < nfa->order; ++i)
    {
        //Dynamically allocating a string for the node number
        si = (int)((ceil(log10(i+1))+1)*sizeof(char));
        char* str = malloc(si);
        sprintf(str, "%zu", i);

        //Getting the epsilon closure of the node
        set* s = get_epsilon_closure(autom, str);

        //For each element in the epsilon closure set
        for(size_t j = 0; j < s->capacity; ++j)
        {
            data* cur = s->elements[j]->next;
            while(cur != NULL)
            {
                //If the final state is present in the set, add the node the
                //final state se
                if(search_set(autom->final_states, cur->key) == 1)
                {
                    insert_set(&(nfa->final_states), str);
                }

                // if the arc letter is different than epsilo, we add it to the
                // automaton
                list* l = find_list(autom, atoi(cur->key));
                while(l->next_arc != NULL)
                {
                    l = l->next_arc;
                    if(strcmp(l->arc->letter, "ε") == 0)
                        continue;

                    add_arc_automaton(nfa, i, l->arc->end,l->arc->letter);
                }

                cur = cur->next;
            }
        }
    }

    return nfa;
}

//Get accessible states from origin
set* get_accessible_states(automaton* autom, char* origin)
{
    //Initializing sets
    set* incoming = new_set(4);
    insert_set(&incoming, origin);
    set* result = new_set(4);

    char* val;
    int s;
    //We keep on going while the incoming set isn't empty
    while(incoming->len > 0)
    {
        //Poping random value from set
        val = pop_set(incoming);

        //If node already in result, we continue
        if(search_set(result, val) == 1)
            continue;

        //Inserting val in the result set
        insert_set(&result, val);

        //Adding the nodes val is connected to
        list* l = find_list(autom, atoi(val));
        while(l->next_arc != NULL)
        {
            l = l->next_arc;
            //Dynamically allocating a string for the node number
            if(l->arc->end == 0)
                s = 0;
            else
                s = (int)((ceil(log10(l->arc->end))+1)*sizeof(char));
            char* str = calloc(s, sizeof(char));

            sprintf(str, "%zu", l->arc->end);
            insert_set(&incoming, str);
        }
    }
    return result;
}

//Returns 1 if origin is an accessible state, 0 otherwise
int is_accessible(automaton* autom, char* origin)
{
    set* ini = autom->initial_states;
    for(size_t i = 0; i < ini->capacity; ++i)
    {
        data* cur = ini->elements[i]->next;
        while(cur != NULL)
        {
            set* s = get_accessible_states(autom, cur->key);
            if(search_set(s, origin) == 1)
                return 1;
            cur = cur->next;
        }
    }
    return 0;
}

//Returns 1 if origin is a co_accessible state, 0 otherwise
int is_co_accessible(automaton* autom, char* origin)
{
    set* s = get_accessible_states(autom, origin);

    //For each element in the epsilon closure set
    for(size_t j = 0; j < s->capacity; ++j)
    {
        data* cur = s->elements[j]->next;
        while(cur != NULL)
        {
            //If the final state is present in the set, return True
            if(search_set(autom->final_states, cur->key) == 1)
            {
                return 1;
            }

            cur = cur->next;
        }
    }
    return 0;
}

//Returns 1 if a state is useful, 0 otherwise
int is_useful(automaton* autom, char* origin)
{
    return is_accessible(autom, origin) && is_co_accessible(autom, origin);
}

//Prunes automaton
automaton* prune_automaton(automaton* autom)
{
    set* v = new_set(4);
    int s = 0;
    ssize_t ne[autom->order];
    size_t count = 0;

    for(size_t i = 0; i < autom->order; ++i)
    {
        char str[s];
        sprintf(str, "%zu", i);
        s = (int)((ceil(log10(i+1))+1)*sizeof(char));

        if(is_useful(autom, str) == 0)
        {
            insert_set(&v, str);
            ne[i] = -1;
        }
        else
        {
            ne[i] = count;
            ++count;
        }
    }

    automaton* a = new_automaton();

    for(size_t i = 0; i < count; ++i)
    {
        add_state_automaton(a);
    }


    char str[s];
    for(size_t i = 0; i < autom->order; ++i)
    {
        sprintf(str, "%zu", i);

        if(ne[i] == -1)
            continue;

        if(search_set(autom->initial_states, str) == 1)
        {
            char* per = malloc(s);
            sprintf(per, "%zu", ne[i]);
            insert_set(&a->initial_states, per);
        }

        if(search_set(autom->final_states, str) == 1)
        {
            char* per = malloc(s);
            sprintf(per, "%zu", ne[i]);
            insert_set(&a->final_states, per);
        }


        list* l = find_list(autom, i);
        while(l->next_arc != NULL)
        {
            l = l->next_arc;
            sprintf(str, "%zu", l->arc->end);
            if(ne[l->arc->end] != -1)
            {
                add_arc_automaton(a, ne[i], ne[l->arc->end], l->arc->letter);
            }
        }
    }

    return a;
}

//Returns index to insert in + parsed string
size_t insert_index(const char* delim, char* s, size_t val)
{
    char* p = strtok(s, delim);
    size_t i = 0;
    while(p != NULL && (size_t) atoi(p) < val)
    {
        i += 1 + strlen(p);
        p = strtok(NULL, delim);
    }
    return i;
}

//Returns a + parsed string of the reachable states from the state
char* get_reachable_states(automaton* a, char* origins, char* letter)
{
    if(strcmp(origins, "∅") == 0)
        return "∅";
    GString* gs = g_string_new("");
    char delim[] = "+";
    char *ptr = strtok(origins, delim);
    size_t state;
    int s = (int)((ceil(log10(a->order))+1)*sizeof(char));
    char str[s];
    while(ptr != NULL)
    {
        state = atoi(ptr);
        list* l = find_list(a, state)->next_arc;
        while(l != NULL)
        {
            if(strcmp(l->arc->letter, letter) == 0)
            {
                char* s = malloc(strlen(gs->str));
                strcpy(s, gs->str);
                size_t ins = insert_index(delim, s, l->arc->end);

                sprintf(str, "%zu+", l->arc->end);
                g_string_insert(gs, ins, str);
            }
            l = l->next_arc;
        }
        ptr = strtok(NULL, delim);
    }
    if(strlen(gs->str) == 0)
        return "∅";
    char* res = malloc(strlen(gs->str));
    strcpy(res, gs->str);
    return res;
}

//Inserts element in string array
int add_element_to_string_array(char*** array, size_t size, char* val)
{
    size_t i = 0;
    char** a = *array;
    while(i < size)
    {
        if(strcmp(a[i], val) == 0)
        {
            return 0;
        }
        i++;
    }

    a = realloc(*array, (size + 1) * sizeof(char*));
    a[size] = val;
    *array = a;

    return 1;
}

size_t get_state(char** all_states, char* val, size_t size)
{
    size_t i = 0;
    while(i < size && strcmp(all_states[i], val) != 0)
    {
        i++;
    }
    return i;
}

void update_sets(automaton* nfa, automaton* a, char* node, char* origins)
{
    char delim[] = "+";
    char *ptr = strtok(origins, delim);

    while(ptr != NULL)
    {
        if(search_set(nfa->initial_states, ptr))
        {
            insert_set(&(a->initial_states), node);
        }

        if(search_set(nfa->final_states, ptr))
        {
            insert_set(&(a->final_states), node);
        }
        ptr = strtok(NULL, delim);
    }
}

//Determinize automaton
automaton* determinize(automaton* nfa)
{
    automaton* a = new_automaton();

    set* q = new_set(4);

    GString* gs = g_string_new("");
    set* inter = nfa->initial_states;
    for(size_t i = 0; i < inter->capacity; ++i)
    {
        data* cur = inter->elements[i]->next;
        while(cur != NULL)
        {
            char* s = malloc(strlen(gs->str));
            strcpy(s, gs->str);
            size_t ins = insert_index("+", s, (size_t) atoi(cur->key));
            g_string_insert(gs, ins, cur->key);
            g_string_insert(gs, ins + strlen(cur->key), "+");
            cur = cur->next;
        }
    }

    insert_set(&q ,gs->str);

    char** all_states = NULL;
    inter = nfa->alphabet;
    char* val;
    char* str;
    while(q->len != 0)
    {
        val = pop_set(q);
        if(add_element_to_string_array(&all_states, a->order, val) == 1)
        {
            add_state_automaton(a);
        }

        size_t node = get_state(all_states, val, a->order);
        if(node == 0)
        {
            str = malloc(1);
        }
        else
        {
            int s = (int)((ceil(log10(node))+1)*sizeof(char));
            str = malloc(s);
        }
        sprintf(str, "%zu", node);


        char* test2 = malloc(strlen(val));
        strcpy(test2, val);
        update_sets(nfa, a, str, test2);

        for(size_t i = 0; i < inter->capacity; ++i)
        {
            data* cur = inter->elements[i]->next;
            while(cur != NULL)
            {
                char* test = malloc(strlen(val));
                strcpy(test, val);
                char* succ = get_reachable_states(nfa, test, cur->key);
                if(add_element_to_string_array(&all_states,
                            a->order, succ) == 1)
                {
                    add_state_automaton(a);
                    insert_set(&q, succ);
                }

                size_t node_succ = get_state(all_states, succ, a->order);
                add_arc_automaton(a, node, node_succ, cur->key);
                cur = cur->next;
            }
        }

    }

    return a;
}

int accepts_from(automaton* a, char* cur_states, char* word)
{
    if(strcmp(word, "") == 0)
    {
        char delim[] = "+";
        char *ptr = strtok(cur_states, delim);
        while(ptr != NULL)
        {
            if(search_set(a->final_states, ptr) == 1)
                return 1;
            ptr = strtok(NULL, delim);
        }
        return 0;
    }
    char inter[2] = {};
    inter[0] = word[0];
    char* succ = get_reachable_states(a, cur_states, inter);
    if(strcmp(succ, "∅") == 0)
        return 0;
    return accepts_from(a, succ, ++word);
}

int accepts_word(automaton* a, char* origins, char* word)
{
    char* inter = malloc(strlen(origins));;
    strcpy(inter, origins);
    char* inter_word = malloc(strlen(word));
    strcpy(inter_word, word);
    int res = accepts_from(a, inter, inter_word);
    free(inter);
    free(inter_word);
    return res;
}

char* get_origins(automaton* a)
{
    GString* gs = g_string_new("");
    set* inter = a->initial_states;
    for(size_t i = 0; i < inter->capacity; ++i)
    {
        data* cur = inter->elements[i]->next;
        while(cur != NULL)
        {
            char* s = malloc(strlen(gs->str));
            strcpy(s, gs->str);
            size_t ins = insert_index("+", s, (size_t) atoi(cur->key));
            g_string_insert(gs, ins, cur->key);
            g_string_insert(gs, ins + strlen(cur->key), "+");
            cur = cur->next;
        }
    }
    return gs->str;
}

automaton* create_dfa(btree* ast)
{
    automaton* a = new_automaton();

    build_enfa(a, ast);
    automaton* nfa = to_nfa(a);
    automaton* p = prune_automaton(nfa);
    automaton* d = determinize(p);

    free_automaton(a);
    free_automaton(nfa);
    free_automaton(p);

    return d;
}

void free_automaton(automaton* autom)
{
    free_set(autom->initial_states);
    free_set(autom->final_states);
    free_set(autom->alphabet);
    list* l;
    list* curr;
    while(autom->adjlists != NULL)
    {
        l = autom->adjlists;
        autom->adjlists = autom->adjlists->next_node;
        while(l != NULL)
        {
            curr = l;
            l = l->next_arc;
            free(curr->arc);
            free(curr);
        }
    }
    free(autom);
}


void print_automaton(automaton* autom)
{
    printf("---------------automaton---------------\n");

    printf("Automaton number of states: %zu\n", autom->order);

    printf("Initial States:\n{ ");
    set* set = autom->initial_states;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");

    printf("Final States:\n{ ");
    set = autom->final_states;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");



    printf("Alphabet:\n{ ");
    set = autom->alphabet;
    for(size_t i = 0; i < set->capacity; ++i)
    {
        data* c = set->elements[i]->next;
        while(c != NULL)
        {
            printf("%s ", c->key);
            c = c->next;
        }
    }
    printf("}\n");

    printf("Adjlists:\n");
    list* l = autom->adjlists->next_node;
    for(size_t i = 0; i < autom->order; ++i)
    {
        printf("%zu -> |", i);
        list* arcs = l->next_arc;
        while(arcs != NULL)
        {
            printf(" (%s, %zu) |", arcs->arc->letter, arcs->arc->end);
            arcs = arcs->next_arc;
        }
        printf("\n");
        l = l->next_node;
    }

    printf("------------------end------------------\n");
}


void print_dot_automaton(automaton* autom)
{
    printf("digraph G {\n\t node [shape=circle]\n\n");

    list* l = autom->adjlists->next_node;
    for(size_t i = 0; i < autom->order; ++i)
    {
        list* arcs = l->next_arc;
        while(arcs != NULL)
        {
            printf("\t %zu->%zu [ label=\"%s\" ];\n", i,
                    arcs->arc->end, arcs->arc->letter);
            arcs = arcs->next_arc;
        }
        printf("\n");
        l = l->next_node;
    }

    for(size_t i = 0; i < autom->initial_states->capacity; ++i)
    {
        data* c = autom->initial_states->elements[i]->next;
        while(c != NULL)
        {
            printf("\t %s [style=filled]\n", c->key);
            c = c->next;
        }
    }
    for(size_t i = 0; i < autom->final_states->capacity; ++i)
    {
        data* c = autom->final_states->elements[i]->next;
        while(c != NULL)
        {
            printf("\t %s [shape=doublecircle]\n", c->key);
            c = c->next;
        }
    }


    printf("\t rankdir = \"LR\";\n}\n");
}
