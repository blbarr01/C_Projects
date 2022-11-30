#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

struct track
{
    int number;
    int visited;
};

typedef struct track track;
int size;
track *sequence;

void MainPrompt();
void EnterParams();
void FIFO();
void SSTF();
void Scan();
void C_Scan();
void ResetVisted();
void PrintSequence(); // testing utility
int NullCheck();

int main(int argc, char *argv[])
{
    int selection;
    while (1)
    {
        MainPrompt();
        printf("enter selection: ");
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            EnterParams();
            break;
        case 2:
            FIFO();
            break;
        case 3:
            SSTF();
            break;
        case 4:
            Scan();
            break;
        case 5:
            C_Scan();
            break;
        case 6:
            exit(EXIT_SUCCESS);
            break;

        default:
            break;
        }
    }

    return 0;
}

void MainPrompt()
{
    printf("Disk Scheduling\n");
    printf("------------------\n");
    printf("1.) enter parameters\n");
    printf("2.) Calculate distance to traverse tracks using FIFO\n");
    printf("3.) Calculate distance to traverse tracks using SSTF\n");
    printf("4.) Calculate distance to traverse tracks using Scan\n");
    printf("5.) Calculate distance to traverse tracks using C-Scan\n");
    printf("6.) Quit Program \n");
}

void EnterParams()
{
    printf("enter size of sequence:  ");
    scanf("%d", &size);
    sequence = (track *)malloc(sizeof(track) * size);
    printf("enter starting track: ");
    scanf("%d", &sequence[0].number);
    printf("enter sequence of tracks to seek: ");
    for (int i = 1; i < size; i++)
    {
        scanf("%d", &sequence[i].number);
    }
    // PrintSequence();
    printf("\n\n");
}

void FIFO()
{
    if (NullCheck())
    {
        return;
    }

    ResetVisted();
    int tdt = 0; // total distance traveled
    int visited_order[size];
    // manually set the first one; this is a consequence of the following for loop
    visited_order[0] = sequence[0].number;
    sequence[0].visited = 1;
    for (int i = 1; i < size; i++)
    {
        tdt += abs(sequence[i].number - sequence[i - 1].number);
        visited_order[i] = (sequence + i)->number;
        sequence[i].visited = 1;
    }
    printf("\ntraversal order: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", visited_order[i]);
    }

    printf("\ntotal distance traveled %d \n\n", tdt);
}

// shortest seek first
void SSTF()
{
    int tdt = 0;
    int shortest_dist = INT_MAX;
    int tracks_traversed = 0;
    int curr_track;
    int visited_order[size];
    int ph; // place holder
    if (NullCheck())
    {
        return;
    }
    ResetVisted();

    // manually handle the first one
    curr_track = sequence[0].number;
    visited_order[0] = sequence[0].number;
    sequence[0].visited = 1;
    tracks_traversed++;

    while (tracks_traversed < size)
    {
        /* code */

        // iterate through the array and find the closest next track
        for (int i = 1; i < size; i++)
        {
            if (sequence[i].visited != 1 && abs(curr_track - sequence[i].number) < shortest_dist)
            {
                shortest_dist = abs(curr_track - sequence[i].number);
                ph = i;
            }
        }
        // set the new current track; this is for the conditional if statement
        curr_track = sequence[ph].number;
        // mark as visited
        sequence[ph].visited = 1;
        // load the track into the visited order
        visited_order[tracks_traversed] = sequence[ph].number;
        // increment the number of tracks traversed
        tracks_traversed++;
        // update total distance traveled
        tdt += shortest_dist;
        // reset shortest distance so the conditional works properly
        shortest_dist = INT_MAX;
    }

    printf("visited order: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", visited_order[i]);
    }
    printf("\ntotal distance traveled is: %d \n\n", tdt);
}

void Scan()
{
    if (NullCheck())
    {
        return;
    }
    int dir,
        curr_track,
        next_track,
        shortest_dist,
        ph,      // placeholder
        swt = 0, // something was traversed; the flag
        tdt = 0, // total distance traveled
        tracks_traversed = 0;
    ResetVisted();
    do
    {
        /* code */
        printf("Enter initial direction: (0 = decreasing, 1 = increasing ) \n");
        scanf("%d", &dir);
        if ((dir != 0) && (dir != 1))
        {
            printf("not a valid input \n");
        }
    } while ((dir != 0) && (dir != 1));

    curr_track = sequence[0].number;
    sequence[0].visited = 1;
    tracks_traversed++;
    printf("size: %d\n", size );
    printf("tracks traversed: %d ", sequence[0].number);
    while (tracks_traversed < size)
    {
        shortest_dist = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            if (dir == 1) // increasing direction
            {
                if (sequence[i].visited == 0)
                {
                    if (sequence[i].number > curr_track && abs(curr_track - sequence[i].number) < shortest_dist)
                    {
                        shortest_dist = abs(curr_track - sequence[i].number);
                        ph = i;
                        swt = 1;
                    }
                }
            }
            else // decreasing direction
            {
                if (sequence[i].visited == 0)
                {
                    if (sequence[i].number < curr_track && abs(curr_track - sequence[i].number) < shortest_dist)
                    {
                        shortest_dist = abs(curr_track - sequence[i].number);
                        ph = i;
                        swt = 1;
                    }
                }
            }
        }
        if (swt != 0)
        {
            sequence[ph].visited = 1;
            tracks_traversed++;
            tdt += shortest_dist;
            curr_track = sequence[ph].number;
            printf("%d ", sequence[ph].number);
            swt = 0;
        }
        else{
            dir = (dir == 1) ? 0 : 1; 
        }
    }
    printf("\ntotal distance traversed: %d \n\n", tdt); 
    return;
}

void C_Scan()
{
    NullCheck();
    ResetVisted();
    int curr_track,
        max_tack = 0,
        tdt = 0, // total distance traveled 
        dist = 0,
        lrgst_track = 0,
        lrgst_trk_flag = 0,
        swt = 0, // something was traversed -flag 
        ph, // placeholder 
        shortest_dist,
        num_traversed = 0;

    // set first track as current track; mark first track as visited 
    curr_track = sequence[0].number;
    sequence[0].visited = 1;
    num_traversed++; 
    printf("tracks traversed: %d ", curr_track);
    while (num_traversed < size)
    {
        
        shortest_dist = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            if (sequence[i].visited == 0)
            {
                dist = abs(sequence[i].number - curr_track);
                //if the value we are inspection is greater than the current track
                // i.e on the way up
                if ((sequence[i].number > curr_track) && (dist < shortest_dist))
                {
                    shortest_dist = dist;
                    ph = i;
                    swt = 1;
                }
                
            }
            
        }
        if (swt == 1)
        {   
            
            sequence[ph].visited = 1; 
            num_traversed++;
            if (lrgst_trk_flag ==1)
            {
                shortest_dist = abs(lrgst_track - sequence[ph].number);
                lrgst_trk_flag = 0;
                
            }
            
            tdt += shortest_dist;
            swt = 0;
            curr_track = sequence[ph].number;
            printf("%d ", curr_track);
        }
        else{
            lrgst_track = curr_track;
            lrgst_trk_flag = 1;
            curr_track = 0;

        }

    }
    printf("\ntotal Distance traveled: %d \n\n", tdt);
    
}

void ResetVisted()
{
    for (int i = 0; i < size; i++)
    {
        sequence[i].visited = 0;
    }
}

void PrintSequence()
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", sequence[i].number);
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", sequence[i].visited);
    }

    printf("\n\n");
}

int NullCheck()
{
    if (sequence == NULL)
    {
        printf("sequence not allocated returning to main \n\n");
        return 1;
    }

    return 0;
}
