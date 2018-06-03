/*
 *
 * Project by Ava Nemanic
 * 2/18/2018
 * COP3503 - UF
 *
 */



#include <iostream>

void printMagicSquare (int ** magicSquare, int size) {
    /*
     * Resources used:
     *      Formatting of print statements: http://www.cplusplus.com/reference/cstdio/printf/
     *      Sum of diagonals: http://c-plus-plus-help.blogspot.com/2012/12/program-to-find-sum-of-individual.html
     *
     */
    //Prints out the magic square
    for(int row = 0; row < size; row++) {
        for(int col =0; col < size; col++) {
            printf("%3d ", magicSquare[row][col]);
        }
        std::cout << "\n";
    }

    //Checks the sum for each row and prints it
    std::cout << "\nChecking the sums of every row:\t\t";
    for (int row = 0; row < size; row++) { //Iterates through each row and column
        int sum = 0;
        for (int col = 0; col < size; col++) {
            sum += magicSquare[row][col]; //Adds each value in all the rows to the total sum
        }
        printf("%3d ", sum); //Prints the sum of rows
    }

    //Checks the sum for each column and prints it
    std::cout << "\nChecking the sums of every column:\t";
    for (int col = 0; col < size; col++) {
        int sum = 0;
        for (int row = 0; row < size; row++) {
            sum += magicSquare[row][col];//Adds each value in all of the columns to the total sum
        }
        printf("%3d ", sum);//Prints the sum of columns
    }

    std::cout << "\nChecking the sums of every diagonal:\t";
    int sum = 0;
    for(int row = 0; row < size; row++ ) {
        for(int column = 0; column < size; column++) {
            if(row == column) {
                sum += magicSquare[row][column];
            }
        }
    }
    printf("%3d ", sum);

    //Resets sum for second diagonal
    sum = 0;
    for(int row = 0; row < size; row++) {
        for(int column = 0; column < size; column++) {
            if(row + column == size - 1) {
                sum += magicSquare[row][column];
            }
        }
    }
    printf("%3d ", sum);
}



//Rotates the square counter-clockwise
void rotateSquare (int ** magicSquare, int size) {
    /*
     * Resources:
     *      Rotate array counter-clockwise: https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
     *                                      https://www.youtube.com/watch?v=G9lQQlVeMao
     */
    for (int row = 0; row < size / 2; row++) {
        for (int column = row; column < size - row - 1; column++) {
            int temp = magicSquare[row][column]; //Temporary value
            //Moves right values to the top
            magicSquare[row][column] = magicSquare[column][size - row - 1];
            //Moves bottom values to the right
            magicSquare[column][size - row - 1] = magicSquare[size - row - 1][size - column - 1];
            //Moves left values to the bottom
            magicSquare[size - row - 1][size - column - 1] = magicSquare[size - column - 1][row];
            //Sets original value in the new position
            magicSquare[size - column - 1][row] = temp;
        }
    }
}



//Method to flip the magic square across the diagonal
void squareFlip (int ** magicSquare, int size) {
    /*
     * Resources: https://www.geeksforgeeks.org/mirror-matrix-across-diagonal/
     */
    for (int row = 0; row < size; row++) {
        for (int column = 0; column <= row; column++) {
            //Sets the values of the matrix above the diagonal to the values below the diagonal
            magicSquare[row][column] = magicSquare[row][column] + magicSquare[column][row] -
                                       (magicSquare[column][row] = magicSquare[row][column]);
        }
    }
}



//Method to create additional magic square based on magic constant algorithm
//Found here: https://en.wikipedia.org/wiki/Magic_constant
void additionalSquare (int ** magicSquare, int size) {
    //Takes values from original magic square and modifies them based on the magic constant
    int magicConstant = (size * ((size * size) + 1)) / 2;
    int g = magicConstant + 13;
    int q = (g - magicConstant) / 4;

    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            magicSquare[row][column] += q;
        }
    }
}



void createMagicSquares (int ** magicSquare, int size){

    //Variable to keep track of number of magic squares created
    int squareCount = 0;

    /*
     * Resources used:
     *      Magic squares: https://en.wikipedia.org/wiki/Magic_square
     *                     https://www.geeksforgeeks.org/magic-square/
     *                     https://en.wikipedia.org/wiki/Siamese_method
     */

    //Beginning positions of rows and columns
    int row = 0;
    int column = (size / 2);

    //Fills the magic square based on the size inputted with Siamese method above
    for (int num = 1; num <= size * size; num++){
        magicSquare[row][column] = num; //Places the first number in the first position
        --row; ++column; //Sets next position to be up and to the right

        //If the row goes out of bounds, this resets it to be within the inputted size
        if (row < 0) {
            row = size - 1;
        }
        //Resets the column to be within inputted size
        if (column > size - 1) {
            column = 0;
        }

        //Checks to see if the position in the magic square is already occupied
        if (magicSquare[row][column] != 0) {
            column--; row += 2; //If it is occupied, moves the position up a column and down two rows

            if (row >= size) {
                row -= size;//Resets row to be within inputted size
            }
            if (column < 0) {//Resets column to be within inputted size
                column += size;
            }
        }
    }

    //Creates 10 magic squares
    //First magic square is simply printed
    ++squareCount;
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Second magic square is first rotated once
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Third magic square is first rotated twice
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Fourth magic square is first rotated three times
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Fifth magic square is created by flipping the last magic square across the diagonal
    squareCount++;
    squareFlip(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Sixth magic square is the fifth rotated once
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Seventh magic square is the fifth rotated twice
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);

    //Eighth is the fifth rotated three times
    squareCount++;
    rotateSquare(magicSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(magicSquare, size);


    //Creates and initializes a second magic square based on first created square
    auto ** secondSquare = new int * [size];
    for (int row = 0; row < size; row++){
        secondSquare [row] = new int[size];
    }
    //Initialize all values in array to the first magic square
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            secondSquare[row][col] = magicSquare[row][col];
        }
    }

    //Runs method to modify second square with magic constant values
    additionalSquare(secondSquare, size);

    //Ninth square is modified original magic square based on magic constant
    squareCount++;
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(secondSquare, size);

    //Tenth square is ninth square rotated once
    squareCount++;
    rotateSquare(secondSquare, size);
    std::cout << "\n\nMagic Square #" << squareCount << " is: \n\n";
    printMagicSquare(secondSquare, size);
}



int main() {
/*
 * Resources: Checking for bad input:
 *            https://stackoverflow.com/questions/18728754/checking-input-value-is-an-integer
 */

    int size = 0;
    std::cout << "Enter the size of a magic square: ";
    std::cin >> size;

    //Checks to make sure the input is an integer
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid input! Enter the size of a magic square: ";
        std::cin >> size;
    }
    //If the input is an integer, ensures it is within the acceptable range
    while((size < 3) || (size > 15) || (size % 2 == 0)) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid input! Enter the size of a magic square: ";
        std::cin >> size;
    }

    //Creates pointer array to be used for magic squares
    auto ** magicSquare = new int * [size];
    for (int row = 0; row < size; row++){
        magicSquare [row] = new int[size];
    }

    //Initializes all values in the array to 0
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            magicSquare [row][col] = 0;
        }
    }

    //Method to create the 10 magic squares
    createMagicSquares(magicSquare, size);


    return 0;
}