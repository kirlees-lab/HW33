#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ArraySizeException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Array must have size 4x4!";
    }
};

class ArrayDataException : public exception
{
private:
    string message;

public:
    ArrayDataException(int row, int col)
    {
        message = "Invalid data at cell [" +
            to_string(row) + "][" +
            to_string(col) + "]";
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class ArrayValueCalculator
{
public:
    int doCalc(const vector<vector<string>>& arr)
    {
        if (arr.size() != 4)
        {
            throw ArraySizeException();
        }

        for (int i = 0; i < 4; i++)
        {
            if (arr[i].size() != 4)
            {
                throw ArraySizeException();
            }
        }

        int sum = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                try
                {
                    size_t pos;
                    int value = stoi(arr[i][j], &pos);

                    if (pos != arr[i][j].size())
                    {
                        throw invalid_argument("Invalid characters");
                    }

                    sum += value;
                }
                catch (const exception& e)
                {
                    throw_with_nested(ArrayDataException(i, j));
                }
            }
        }

        return sum;
    }
};

int main()
{
    ArrayValueCalculator calculator;

    vector<vector<string>> arr =
    {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try
    {
        int result = calculator.doCalc(arr);
        cout << "Result: " << result << endl;
    }
    catch (const ArraySizeException& e)
    {
        cout << "Size error: " << e.what() << endl;
    }
    catch (const ArrayDataException& e)
    {
        cout << "Data error: " << e.what() << endl;

        try
        {
            rethrow_if_nested(e);
        }
        catch (const exception& nested)
        {
            cout << "Reason: " << nested.what() << endl;
        }
        catch (...)
        {
            cout << "Unknown conversion error." << endl;
        }
    }
}
