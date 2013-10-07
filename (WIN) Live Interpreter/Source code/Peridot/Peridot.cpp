#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <map>

using namespace std;

ifstream source_file;
string source_data;

int ARRAY_LENGTH = 65536;

unsigned char* main_array;
int main_array_ptr = 0;	

int main(int argc, char *argv[])
{
	string filename = "spoint.p";

	if(argc > 1)
		filename = argv[1];
	
	main_array = new unsigned char[ARRAY_LENGTH];
	
	unsigned int source_data_ptr = 0;
	stack<int> equal_loop_stack;
	map<int, int> equal_jump_table;
	stack<int> n_equal_loop_stack;
	map<int, int> n_equal_jump_table;
	stack<int> if_equal_loop_stack;
	map<int, int> if_equal_jump_table;
	stack<int> if_not_equal_loop_stack;
	map<int, int> if_not_equal_jump_table;
	stack<int> if_greater_loop_stack;
	map<int, int> if_greater_jump_table;
	stack<int> if_less_loop_stack;
	map<int, int> if_less_jump_table;

	stack<int> pos_stack;
	stack<unsigned char> val_stack;

	int error_count = 0;

	source_file.open(filename.c_str());

	memset(main_array, 0, ARRAY_LENGTH);

	if(!source_file.good())
	{
		cout << filename << " file not found. Aborting!" << endl;
		return 0;
	}

	while(!source_file.eof())
	{
		string file_row;
        getline(source_file, file_row);
		source_data += file_row;
	}

	for (unsigned int i = 0; i < source_data.length(); i++)
    {
		main_array[i] = 0;

        switch (source_data[i])
        {
            case '[':
                equal_loop_stack.push(i);
                break;
            case ']':
				if (equal_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched ] at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = equal_loop_stack.top();
					equal_loop_stack.pop();
					
					equal_jump_table.insert(pair<int, int> (openPos, i + 1));
					equal_jump_table.insert(pair<int, int> (i, openPos + 1));
                }
                break;
			case '{':
                n_equal_loop_stack.push(i);
                break;
			case '}':
				if (n_equal_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched } at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = n_equal_loop_stack.top();
					n_equal_loop_stack.pop();
					
					n_equal_jump_table.insert(pair<int, int> (openPos, i + 1));
					n_equal_jump_table.insert(pair<int, int> (i, openPos + 1));
                }
                break;
			case 'E':
                if_equal_loop_stack.push(i);
                break;
			case 'e':
				if (if_equal_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched e at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = if_equal_loop_stack.top();
					if_equal_loop_stack.pop();
					
					if_equal_jump_table.insert(pair<int, int> (openPos, i + 1));
                }
                break;
			case 'N':
                if_not_equal_loop_stack.push(i);
                break;
			case 'n':
				if (if_not_equal_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched n at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = if_not_equal_loop_stack.top();
					if_not_equal_loop_stack.pop();
					
					if_not_equal_jump_table.insert(pair<int, int> (openPos, i + 1));
                }
                break;
			case 'G':
                if_greater_loop_stack.push(i);
                break;
			case 'g':
				if (if_greater_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched g at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = if_greater_loop_stack.top();
					if_greater_loop_stack.pop();
					
					if_greater_jump_table.insert(pair<int, int> (openPos, i + 1));
                }
                break;
			case 'L':
                if_less_loop_stack.push(i);
                break;
			case 'l':
				if (if_less_loop_stack.size() == 0)
                {
					cout << "ERROR: Unmatched l at position " << i << "." << endl;
                    error_count++;
                }
                else
                {
                    int openPos = if_less_loop_stack.top();
					if_less_loop_stack.pop();
					
					if_less_jump_table.insert(pair<int, int> (openPos, i + 1));
                }
                break;
            default:
                break;
        }
    }

	if (equal_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched [ at position " << equal_loop_stack.top() << "." << endl;
        error_count++;
    }

	if (n_equal_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched { at position " << n_equal_loop_stack.top() << "." << endl;
        error_count++;
    }

	if (if_equal_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched E at position " << if_equal_loop_stack.top() << "." << endl;
        error_count++;
    }

	if (if_not_equal_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched N at position " << if_not_equal_loop_stack.top() << "." << endl;
		error_count++;
    }

	if (if_greater_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched G at position " << if_greater_loop_stack.top() << "." << endl;
        error_count++;
    }

	if (if_less_loop_stack.size() > 0)
    {
		cout << "ERROR: Unmatched L at position " << if_less_loop_stack.top() << "." << endl;
        error_count++;
    }

	if(error_count != 0)
		return 0;

	int right_side = 0;
	int left_side = 0;

	while (source_data_ptr < source_data.length())
    {
		switch (source_data[source_data_ptr])
		{
			case '>':
				main_array_ptr++;
				if (main_array_ptr == ARRAY_LENGTH)
					main_array_ptr = 0;
				source_data_ptr++;
				break;
			case '<':
				main_array_ptr--;
				if (main_array_ptr == -1)
					main_array_ptr = ARRAY_LENGTH - 1;
				source_data_ptr++;
				break;
			case '+':
				main_array[main_array_ptr]++;
				source_data_ptr++;
				break;
			case '-':
				main_array[main_array_ptr]--;
				source_data_ptr++;
				break;
			case '.':
				cout << main_array[main_array_ptr];
				source_data_ptr++;
				break;
			case ',':
				cin >> main_array[main_array_ptr];
				source_data_ptr++;
				break;
			case '[':
				if (main_array[main_array_ptr] == 0)
					source_data_ptr = equal_jump_table[source_data_ptr];
				else
					source_data_ptr++;
				break;
			case ']':
				if (main_array[main_array_ptr] == 0)
					source_data_ptr++;
				else
					source_data_ptr = equal_jump_table[source_data_ptr];
				break;
			case '{':
				if (main_array[main_array_ptr] != 0)
					source_data_ptr = n_equal_jump_table[source_data_ptr];
				else
					source_data_ptr++;
				break;
			case '}':
				if (main_array[main_array_ptr] != 0)
					source_data_ptr++;
				else
					source_data_ptr = n_equal_jump_table[source_data_ptr];
				break;
			case '/':
				main_array[main_array_ptr] += 10;
				source_data_ptr++;
				break;
			case '\\':
				main_array[main_array_ptr] -= 10;
				source_data_ptr++;
				break;
			case 'z':
				main_array[main_array_ptr] = 0;
				source_data_ptr++;
				break;
			case 'Z':
				memset(main_array, 0, ARRAY_LENGTH);
				source_data_ptr++;
				break;
			case '|':
				main_array_ptr = 0;
				source_data_ptr++;
				break;
			case '@':
				main_array_ptr -= main_array[main_array_ptr];
				source_data_ptr++;
				break;
			case '#':
				main_array_ptr += main_array[main_array_ptr];
				source_data_ptr++;
				break;
			case 'P':
				pos_stack.push(main_array_ptr);
				source_data_ptr++;
				break;
			case 'p':
				if(!pos_stack.empty())
					pos_stack.pop();
				else
				{
					cout << endl << "ERROR: Unable to pop from pointer stack - stack is empty. Command 'p' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'j':
				if(!pos_stack.empty())
					main_array_ptr = pos_stack.top();
				else
				{
					cout << endl << "ERROR: Unable to jump to position from pointer stack - stack is empty. Command 'j' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'J':
				if(!pos_stack.empty())
				{
					main_array_ptr = pos_stack.top();
					pos_stack.pop();
				}
				else
				{
					cout << endl << "ERROR: Unable to jump (and pop) to position from pointer stack - stack is empty. Command 'J' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'V':
				val_stack.push(main_array[main_array_ptr]);
				source_data_ptr++;
				break;
			case 'v':
				if(!val_stack.empty())
					val_stack.pop();
				else
				{
					cout << endl << "ERROR: Unable to pop from value stack - stack is empty. Command 'v' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'i':
				if(!val_stack.empty())
					main_array[main_array_ptr] = val_stack.top();
				else
				{
					cout << endl << "ERROR: Unable to put value from stack - stack is empty. Command 'i' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'I':
				if(!val_stack.empty())
				{
					main_array[main_array_ptr] = val_stack.top();
					val_stack.pop();
				}
				else
				{
					cout << endl << "ERROR: Unable to put (and pop) value from stack - stack is empty. Command 'I' at position " << source_data_ptr << "." << endl;
					return 0;
				}
				source_data_ptr++;
				break;
			case 'E':
				right_side = main_array_ptr != ARRAY_LENGTH - 1 ? main_array_ptr + 1 : 0;
				if (main_array[main_array_ptr] == main_array[right_side])
					source_data_ptr++;
				else
					source_data_ptr = if_equal_jump_table[source_data_ptr];
				break;
			case 'N':
				right_side = main_array_ptr != ARRAY_LENGTH - 1 ? main_array_ptr + 1 : 0;
				if (main_array[main_array_ptr] != main_array[right_side])
					source_data_ptr++;
				else
					source_data_ptr = if_not_equal_jump_table[source_data_ptr];
				break;
			case 'G':
				right_side = main_array_ptr != ARRAY_LENGTH - 1 ? main_array_ptr + 1 : 0;
				if (main_array[main_array_ptr] > main_array[right_side])
					source_data_ptr++;
				else
					source_data_ptr = if_greater_jump_table[source_data_ptr];
				break;
			case 'L':
				right_side = main_array_ptr != ARRAY_LENGTH - 1 ? main_array_ptr + 1 : 0;
				if (main_array[main_array_ptr] < main_array[right_side])
					source_data_ptr++;
				else
					source_data_ptr = if_less_jump_table[source_data_ptr];
				break;
			default:
				source_data_ptr++;
				break;
		}
    }

	delete [] main_array;

	return 0;
}