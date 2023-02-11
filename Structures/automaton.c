struct ENFA* new_enfa(set* allstates, set* initial_states, set* final_states,
        set* alphabet, dict* edges)
{

}


void add_state(struct ENFA* enfa)
{
    int add_state = atoi(max_set(enfa->all_states) + 1);
    insert_set(enfa->all_sates, add_state);
    for(size_t i = 0; i < enfa->alphabet->capacity; ++i)
    {
        data* curr = set->elements->next;
        while(curr != NULL)
        {
            insert_dict(enfa->next_states, "", new_set(4));
            curr = curr->next;
        }
    }
}
