### Usage:
    ./I18n [OPTIONS]
This program tries to guess an integer from 1 to 100 that you guessed

### Arguments:
>**-r** - display of numbers in the Roman system
**\-\-help** - help message output

### Functions:
    int main(int argc, char *argv[])
>the main function that implements the game process
    
    char *to_roman(int num)
>converting arabic integers from 1 to 100 into roman

    int from_roman(char *rom)
>converting roman integerss from 1 to 100 into arabic
