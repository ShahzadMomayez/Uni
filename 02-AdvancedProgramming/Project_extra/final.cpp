#include <iostream>
#include <vector>

using namespace std;

#define  MAXIMUM_NUMBER_OF_MOVES 4

long int sum_numbers(vector<int> list_of_numbers )
{
    long int total_sum = 0;
    for (int counter = 0; counter < list_of_numbers.size(); counter++)
        total_sum += list_of_numbers[counter];
    return total_sum;
}

void sum_rows_of_table(int max_row , int max_column , vector<long int> & row_sums, vector<vector<int> > farm)
{
    long int sum = 0;
    for (int move = 0; move < MAXIMUM_NUMBER_OF_MOVES; move++)
    {
        for (int row_counter = 0; row_counter < max_row; row_counter++) 
        {
            sum = sum_numbers(farm[row_counter]);
            row_sums.push_back(sum);
            sum = 0;
        }
    }
}

void find_max_row(int & max_row , vector<long int> & row_sums ,int  max_column , int & row , int & row_with_max_sum)
{
    for (int move = 0; move < MAXIMUM_NUMBER_OF_MOVES; move++)
    {
        for (int row_counter = 0; row_counter < max_row; row_counter++) 
        {
            if (row_sums[row_counter] > row_with_max_sum)
            {
                row_with_max_sum = row_sums[row_counter];
                row = row_counter;
            }
        }
    }
}
 
void find_max_column( int & max_row , int & max_column , int &column , int & column_with_max_sum , vector<vector<int> > farm) 
{
    int sum = 0; 
    for (int move = 0; move < MAXIMUM_NUMBER_OF_MOVES; move++) 
    {
        for (int column_counter = 0; column_counter < max_column; column_counter++) 
        {
            for (int row_counter = 0; row_counter < max_row; row_counter++) 
            {
                sum += farm[row_counter][column_counter];
            }
            if (sum > column_with_max_sum) 
            {
                column_with_max_sum = sum;
                column = column_counter;
            }
            sum = 0;
        }
    }
}

void calculate_harvest(int & max_row, int & max_column, long int& harvest ,int & column_with_max_sum , int & row_with_max_sum , int & row , int & column , vector<vector<int> > farm) 
{
    for (int move = 0; move < MAXIMUM_NUMBER_OF_MOVES; move++)
    {
        if (column_with_max_sum > row_with_max_sum) 
        {
            harvest += column_with_max_sum;
            for (int row_counter = 0; row_counter < max_row; row_counter++)
            {
                farm[row_counter][column] = 0;
            }
        }
        else 
        {
            harvest += row_with_max_sum;
            for (int column_counter = 0; column_counter < max_column; column_counter++) 
            {
                farm[row][column_counter] = 0;
            }
        }
      
    }
  
}

void get_input(int& max_column , int& max_row , vector<vector<int> > & farm)
{
    int  product;
    for (int row_counter = 0; row_counter < max_row; row_counter++) 
    {
        for (int column_counter = 0; column_counter < max_column; column_counter++) 
        {
            cin >> product;
            farm[row_counter][column_counter] = product;
        }
    }
}

int main() 
{
    vector<vector<int> > farm;
    int max_row , max_column;
    vector<long int> row_sums;
    long int harvest = 0;
    cin >> max_row >> max_column;
    farm = vector < vector < int > >(max_row, vector<int>(max_column));
    int row_with_max_sum = 0;
    int row = 0;
    int column = 0;
    int column_with_max_sum = 0;

    get_input(max_column, max_row, farm);
    sum_rows_of_table(max_row, max_column, row_sums , farm);
    find_max_row(max_row, row_sums, max_column, row, row_with_max_sum);
    find_max_column(max_row, max_column, column, column_with_max_sum , farm);
    calculate_harvest(max_row, max_column, harvest, column_with_max_sum, row_with_max_sum, row, column, farm);
    cout << harvest;
    return 0;
    cout << "Hello there! I'm unreachable!" << endl;
} 

