#include <cs50.h>
#include <stdio.h>

int get_starting_population(void);
int get_ending_population(void);
int calc_years(void);
int ending_size = get_ending_population(void);
int starting_size = get_starting_population(void);


int main(void)
{
    int years = calc_years();
    printf("Years: %i\n", years); //prints out number of years to reach a certain population
}

int get_starting_population(void)
{
    int starting_size;
    do
    {
        starting_size = get_int("Enter Starting Population: ");
        //To get starting population size
    }
    while (starting_size < 9); //to ensure starting size is greater than 9
    return starting_size;
}


int get_ending_population(void){ // takes starting size
    int ending_size;

    do
    {
        ending_size = get_int("Enter Ending Population: ");
        //To get ending population size
    }
    while (ending_size < starting_size); // ensures ending size is greater than starting size
    return ending_size;
}

int calc_years(void) {

    int birth_rate = starting_size / 3; // calculates birth rate
    int death_rate = starting_size / 4; // calculates death rate
    int annual_population = starting_size - death_rate + birth_rate; // removes death rate and birth rate for every year
    int years = ending_size / annual_population; // divides end size by annual population to get total number of years
    return years;
}