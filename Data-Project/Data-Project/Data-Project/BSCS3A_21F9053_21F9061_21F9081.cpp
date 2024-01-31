#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

string header = R"(

                        _____                          _      _______           _       ______     _  _  _                
                       / ____|                        | |    |__   __|         | |     |  ____|   | |(_)| |               
                      | (___   _ __ ___    __ _  _ __ | |_      | |  ___ __  __| |_    | |__    __| | _ | |_  ___   _ __  
                       \___ \ | '_ ` _ \  / _` || '__|| __|     | | / _ \\ \/ /| __|   |  __|  / _` || || __|/ _ \ | '__| 
                       ____) || | | | | || (_| || |   | |_      | ||  __/ >  < | |_    | |____| (_| || || |_| (_) || |    
                      |_____/ |_| |_| |_| \__,_||_|    \__|     |_| \___|/_/\_\ \__|   |______|\__,_||_| \__|\___/ |_|    
                                                                                                                          
                                                                                                     
)";

string smol_header = R"(

                                     __                      ___                 _                    
                                    (_  ._ _   _. ._ _|_      |  _    _|_       |_  _| o _|_  _  ._   
                                    __) | | | (_| |   |_      | (/_ >< |_       |_ (_| |  |_ (_) |    
        
                                                           

)";

string end_header = R"(

                ___                                _                                                                                
                 | |_   _. ._  |        _        _|_ _  ._        _ o ._   _     _      ._   _|_  _    _|_    _   _| o _|_  _  ._   
                 | | | (_| | | |<   \/ (_) |_|    | (_) |    |_| _> | | | (_|   (_) |_| |     |_ (/_ >< |_   (/_ (_| |  |_ (_) |    
                                    /                                      _|                                                       


)";

#define a 26

// Node used for the trie tree. It has 26 child nodes
class Node {
public:

    Node* childNodes[a];
    string value;
    bool  End_Word;

    Node()
    {

        for (int i = 0; i < a; i++)
        {
            childNodes[i] = NULL;
        }
        End_Word = false;
    }
};

struct node
{
    char data;
    node* next;
};

class LLQueueADT
{
private:
    node* front;
    int numItems;

    node* create_node(char val)
    {
        node* temp = new node;
        temp->data = val;
        temp->next = NULL;

        return temp;
    }

    void del_all(node* n)
    {
        if (n == NULL)
            return;

        del_all(n->next);

        delete n;
    }
public:
    LLQueueADT()
    {
        front = NULL;
        numItems = 0;
    }

    bool isempty()
    {
        return (front == NULL);
    }

    void enqueue(char val)
    {
        if (front == NULL)
        {
            front = create_node(val);
        }
        else
        {
            node* newNode = create_node(val);
            node* temp = front;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;

        }
    }

    char dequeue_front()
    {
        char temp = ' ';
        node* tempNode;
        if (isempty())
        {
            cout << "[!]ERROR: UNDERFLOW\n\n";

        }
        else
        {
            temp = front->data;
            tempNode = front;

            front = front->next;
            delete tempNode;
        }

        return temp;
    }

    char dequeue_rear()
    {
        node* prev = NULL;
        node* temp;
        char temp_data = ' ';
        if (isempty())
        {
            cout << "[!]ERROR: UNDERFLOW\n\n";

        }
        else if (front->next == NULL)
        {
            temp_data = front->data;
            temp = front;

            front = front->next;

            delete temp;
        }
        else
        {

            prev = NULL;
            temp = front;

            while (temp->next != NULL)
            {
                prev = temp;
                temp = temp->next;
            }

            temp_data = temp->data;

            prev->next = NULL;

            delete temp;
        }

        return temp_data;
    }

    bool find(char val)
    {
        node* tempNode = front;
        while (tempNode != NULL)
        {
            if (tempNode->data == val)
                return true;

            tempNode = tempNode->next;
        }

        return false;
    }

    void display()
    {
        if (!isempty())
        {
            node* tempNode = front;
            while (tempNode != NULL)
            {
                cout << tempNode->data;
                tempNode = tempNode->next;
            }
            cout << "\n";
        }
        else
        {
            cout << "[!]ERROR: No elements present\n\n";
        }
    }

    void clear()
    {
        del_all(front);
        front = NULL;
        numItems = 0;
    }
};

class Trie_Tree
{
    Node* root;
public:
    Trie_Tree()
    {

        root = new Node;
    }

    Node* insert_key(string value)
    {
        Node* currentNode = root;

        for (int i = 0; i < value.size(); i++)
        {
            if (currentNode->childNodes[value[i] - 'a'] == NULL)
            {

                Node* newNode = new Node();
                currentNode->childNodes[value[i] - 'a'] = newNode;
                currentNode->childNodes[value[i] - 'a']->value = value[i];
            }
            currentNode = currentNode->childNodes[value[i] - 'a'];
        }
        currentNode->End_Word = true;
        return root;
    }

    void find_words(Node* root, string key, string sug[], int& count)
    {
        if (count >= 10)
        {
            return;
        }

        if (root->End_Word == true)
        {
            sug[count] = key;
            count++;
        }

        for (int i = 0; i < 26; i++)
        {
            Node* find = root->childNodes[i];
            if (find != NULL)
            {
                find_words(find, key + find->value, sug, count);
            }
        }
    }

    void suggestions(string key, string sug[], int& count)
    {
        Node* temp_node = root;
        for (int i = 0; i < key.size(); i++)
        {
            if (temp_node->childNodes[key[i] - 'a'] != NULL)
            {
                temp_node = temp_node->childNodes[key[i] - 'a'];
            }
            else
            {
                return;
            }
        }

        find_words(temp_node, key, sug, count);
    }

    void read_from_file()
    {
        ifstream read;
        string data;
        read.open("outfile.txt");
        while (!read.eof())
        {
            read >> data;
            insert_key(data); 
        }
        read.close();
    }
};

class char_int_array
{
private:
    int* list, out_of_range;
    int max_size;

public:

    char_int_array()
    {
        max_size = 40;
        out_of_range = 0;

        list = new int[max_size];

        for (int i = 0; i < max_size; i++)
        {
            list[i] = 0;
        }
    }

    int& operator[](char index)
    {
        int i = index;

        if (index == ' ')
        {
            return list[26]; // 26th position for spaces
        }

        if (index == '.')
        {
            return list[37]; // 37th position for fullstop
        }

        if (index == ',')
        {
            return list[38]; // 38th position for comma
        }

        if (index == '?')
        {
            return list[39]; // 37th position for question
        }

        if (i >= 'a' && i <= 'z')
        {
            i = index - 'a';
            return list[i];
        }
        else if (i >= '0' && i <= '9')
        {
            i = (i - '0') + 27;
            return list[i];
        }
        else
        {
            cout << "\n\nERROR\n\n";
            return out_of_range;
        }
    }

};

class char_string_array
{
private:
    string* list, out_of_range;
    int max_size;

public:

    char_string_array()
    {
        max_size = 40;
        out_of_range = "";

        list = new string[max_size];

        for (int i = 0; i < max_size; i++)
        {
            list[i] = "";
        }
    }

    string& operator[](char index)
    {
        int i = index;

        if (index == ' ')
        {
            return list[26]; // 26th position for spaces
        }

        if (index == '.')
        {
            return list[37]; // 37th position for fullstop
        }

        if (index == ',')
        {
            return list[38]; // 38th position for comma
        }

        if (index == '?')
        {
            return list[39]; // 39th position for question mark
        }

        if (i >= 'a' && i <= 'z')
        {
            i = index - 'a';
            return list[i];
        }
        else if (i >= '0' && i <= '9')
        {
            i = (i - '0') + 27;
            return list[i];
        }
        else
        {
            cout << "\n\nERROR\n\n";
            return out_of_range;
        }
    }

};

struct huffman_nodes
{
    char character;
    int freq;
    huffman_nodes* left;
    huffman_nodes* right;
};

// used for forming huffman tree
class min_heap
{
private:
    huffman_nodes** arr;
    int max_size, count;

    void swap_num(huffman_nodes*& n1, huffman_nodes*& n2)
    {
        huffman_nodes* temp = n1;
        n1 = n2;
        n2 = temp;
    }

    void min_heapify(huffman_nodes** arr, int size, int i)
    {
        int smallest = i;
        int l = (i * 2) + 1;
        int r = (i * 2) + 2;

        if (l < size && arr[l]->freq != -1 && arr[l]->freq < arr[smallest]->freq)
        {
            smallest = l;
        }

        if (r < size && arr[r]->freq != -1 && arr[r]->freq < arr[smallest]->freq)
        {
            smallest = r;
        }

        if (smallest != i)
        {
            swap_num(arr[smallest], arr[i]);

            min_heapify(arr, size, smallest);
        }
    }

    void heapify_up(huffman_nodes** arr, int size, int i)
    {
        if (i == 0)
            return;

        int parent = (i - 1) / 2;

        min_heapify(arr, size, parent);

        heapify_up(arr, size, parent);


    }

public:

    min_heap(int size)
    {
        max_size = size;
        count = 0;
        arr = new huffman_nodes * [size];

        for (int i = 0; i < max_size; i++)
        {
            arr[i] = new huffman_nodes;
            arr[i]->character = ' ';
            arr[i]->freq = -1;
            arr[i]->left = NULL;
            arr[i]->right = NULL;
        }

    }

    void insert(char c, int f)
    {
        if (!is_full())
        {

            if (count == 0)
            {
                arr[0]->character = c;
                arr[0]->freq = f;
                count++;
            }
            else
            {
                arr[count]->character = c;
                arr[count]->freq = f;
                count++;
                heapify_up(arr, count, count - 1);
            }
        }
        else
        {
            cout << "[!]ERROR: The heap is full.\n\n";
        }
    }

    void insert_node(huffman_nodes* new_node)
    {
        arr[count] = new_node;
        count++;
        heapify_up(arr, count, count - 1);
    }

    huffman_nodes* getMin()
    {
        if (!is_empty())
        {
            return arr[0];
        }
        else
        {
            return NULL;
        }
    }

    void extractMin()
    {
        if (!is_empty())
        {
            arr[0] = arr[count - 1];
            count--;
            min_heapify(arr, count, 0);
        }
    }

    bool is_full()
    {
        return (max_size == count);
    }

    bool is_empty()
    {
        return (count == 0);
    }

    bool is_one()
    {
        return (count == 1);
    }

    huffman_nodes* huffman_coding()
    {
        huffman_nodes* l, * r, * new_node;

        while (!is_one())
        {
            l = getMin();
            extractMin();

            r = getMin();
            extractMin();

            new_node = new huffman_nodes;

            new_node->character = '^';
            new_node->freq = l->freq + r->freq;
            new_node->left = l;
            new_node->right = r;

            insert_node(new_node);

        }

        return getMin();
    }


};

void FindHuffmanCode(huffman_nodes* root, char_string_array& huffman_codes, string code = "")
{
    if (!root)
        return;

    if (root->left == NULL && root->right == NULL)
        huffman_codes[root->character] = code;


    FindHuffmanCode(root->right, huffman_codes, code + "1");
    FindHuffmanCode(root->left, huffman_codes, code + "0");
}

void GenerateHuffmanCodes(char_int_array& char_count, char_string_array& huffman_codes)
{
    min_heap heap(40);

    for (char i = 'a'; i <= 'z'; i++)
    {
        if (char_count[i] != 0)
            heap.insert(i, char_count[i]);
    }

    if (char_count[' '] != 0)
        heap.insert(' ', char_count[' ']);

    for (char i = '0'; i <= '9'; i++)
    {
        if (char_count[i] != 0)
            heap.insert(i, char_count[i]);
    }

    if (char_count['.'] != 0)
        heap.insert('.', char_count['.']);

    if (char_count[','] != 0)
        heap.insert(',', char_count[',']);

    if (char_count['?'] != 0)
        heap.insert('?', char_count['?']);

    FindHuffmanCode(heap.huffman_coding(), huffman_codes);

}

huffman_nodes* ReadHuffmanCodesFromFile(string file_name, char_int_array& char_count)
{
    ifstream fin(file_name + "_charCount.txt");
    char alphabet;
    int freq;

    min_heap heap(40);

    fin >> freq;

    if (freq != 0)
    {
        char_count[' '] = freq;
    }

    do
    {
        fin >> alphabet;
        fin >> freq;

        char_count[alphabet] = freq;

    } while (!fin.eof());

    for (char i = 'a'; i <= 'z'; i++)
    {
        if (char_count[i] != 0)
            heap.insert(i, char_count[i]);
    }

    if (char_count[' '] != 0)
        heap.insert(' ', char_count[' ']);

    for (char i = '0'; i <= '9'; i++)
    {
        if (char_count[i] != 0)
            heap.insert(i, char_count[i]);
    }

    if (char_count['.'] != 0)
        heap.insert('.', char_count['.']);

    if (char_count[','] != 0)
        heap.insert(',', char_count[',']);

    if (char_count['?'] != 0)
        heap.insert('?', char_count['?']);


    return heap.huffman_coding();
}

void DecodeText(string file_name, LLQueueADT& allText, huffman_nodes* tree)
{
    ifstream fin(file_name + ".txt");
    huffman_nodes* temp = tree;
    char c;


    do
    {
        fin >> c;

        if (c == '0') // go to left
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }

        if (temp->character != '^')
        {
            allText.enqueue(temp->character);
            temp = tree;
        }
    } while (!fin.eof());

    fin.close();

}

bool CheckFileExist(string file_name)
{
    bool open;
    ifstream check_file(file_name + ".txt");

    open = check_file.is_open();

    check_file.close();

    return open;
}

bool IsFileEmpty(string file_name)
{
    bool open;
    char temp;
    ifstream check_file(file_name + ".txt");

    check_file >> temp;
    open = check_file.eof();

    check_file.close();

    return open;
}

void ReadTextFromFile(string file_name, LLQueueADT& allText, char_int_array& char_count)
{
    char last_char;
    if (IsFileEmpty(file_name) == false)
    {
        huffman_nodes* huffman_tree = ReadHuffmanCodesFromFile(file_name, char_count);
        DecodeText(file_name, allText, huffman_tree);

        last_char = allText.dequeue_rear();

        // adds a space at the end of text to avoid any exceptions
        if (last_char == ' ')
        {
            allText.enqueue(' ');
        }
        else
        {
            allText.enqueue(last_char);
            allText.enqueue(' ');
            char_count[' ']++;
        }

    }
}

void EncodeText_StoreCharCount(string file_name, LLQueueADT& allText, char_int_array count, char_string_array& codes)
{
    ofstream fout(file_name + ".txt");
    char c;


    do
    {
        c = allText.dequeue_front();

        fout << codes[c];
    } while (!allText.isempty());

    fout.close();

    fout.open(file_name + "_charCount.txt");

    // writes the number of blank spaces
    fout << count[' '];


    for (char i = 'a'; i <= 'z'; i++)
    {
        if (count[i] != 0)
        {
            fout << ' ' << i << ' ';
            fout << count[i];
        }
    }

    for (char i = '0'; i <= '9'; i++)
    {
        if (count[i] != 0)
        {
            fout << ' ' << i << ' ';
            fout << count[i];
        }
    }

    char i = '.';

    if (count[i] != 0)
    {
        fout << ' ' << i << ' ';
        fout << count[i];
    }

    i = ',';

    if (count[i] != 0)
    {
        fout << ' ' << i << ' ';
        fout << count[i];
    }

    i = '?';

    if (count[i] != 0)
    {
        fout << ' ' << i << ' ';
        fout << count[i];
    }



    fout.close();

}

void WriteTextToFile(string file_name, LLQueueADT& allText, char_int_array& char_count)
{
    char_string_array huffman_codes;

    GenerateHuffmanCodes(char_count, huffman_codes);

    EncodeText_StoreCharCount(file_name, allText, char_count, huffman_codes);
}

void SelectWord(LLQueueADT& allText, string word, char_int_array& char_count)
{
    char removed_char;
    do
    {
        removed_char = allText.dequeue_rear();

        char_count[removed_char]--;

    } while (removed_char != ' ' && !allText.isempty());

    if (!allText.isempty())
    {
        allText.enqueue(' ');
        char_count[' ']++;
    }


    for (int i = 0; i < word.size(); i++)
    {
        allText.enqueue(word[i]);
        char_count[word[i]]++;
    }

    allText.enqueue(' ');
    char_count[' ']++;

}

bool IsInvalidChars(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == ',' || str[i] == '?')
            return true;
    }

    return false;
}

void WritingModule(string file_name, LLQueueADT& allText, Trie_Tree& trie, char_int_array& char_count)
{

    int count = 0, selected_word = 0;
    char input = ' ';
    string data = "", suggestions[10];

    if (!allText.isempty()) // if the text is not empty
        allText.display();

    while (input != '=')
    {
        count = 0;
        input = _getch();

        if (input != '=') // exits the writing module when = is entered
        {
            if ((input >= 'a' && input <= 'z') || (input >= '0' && input <= '9') || input == ' ' || input == '.' || input == ',' || input == '?')
            {

                char_count[input]++;

                if (input != ' ')
                {
                    data += input;
                }
                else
                {
                    data = "";
                }

                allText.enqueue(input);
            }

            system("cls");

            cout << setw(60) << " " << "--- " << file_name << ".txt ---" << setw(30) << "Press \'=\' to save file" << " \n\n\n";
            allText.display();



            if (data != "" && !IsInvalidChars(data))
            {
                trie.suggestions(data, suggestions, count);

                if (input == '\\')
                    selected_word = (selected_word + 1) % count;

                cout << "\n\n\n";
                for (int i = 0; i < count; i++)
                {
                    if (selected_word == i)
                        cout << "->";
                    cout << suggestions[i] << endl;
                }
                if (count != 0) // makes sure there is at least one suggestion
                {
                    if (input == ';')
                    {
                        SelectWord(allText, suggestions[selected_word], char_count);
                        selected_word = 0;

                        system("cls");

                        cout << setw(60) << " " << "--- " << file_name << ".txt ---" << setw(30) << "Press \'=\' to save file" << " \n\n\n";
                        allText.display();
                        data = "";
                    }
                    else
                    {
                        cout << "\n\n\nPress \'\\\' to move to next word & \';\' to select it.";
                    }

                }
                else
                {
                    cout << "\n\n\n[!] No suggestions found.";
                }


            }
            else
            {
                cout << "\n\n\n[!] No suggestions found.";
            }

        }

    }

    WriteTextToFile(file_name, allText, char_count);
}

void start_screen()
{
    cout << header << "\n\n\n\n\n";

    cout << setw(57) << " " << "Press any key to continue";
    _getch();

}

void instructions()
{
    system("cls");
    cout << smol_header;
    cout << setw(60) << " " << "--- INSTRUCTIONS ---\n\n\n";

    cout << setw(40) << " " << "1. You can only enter alphabets, numbers and" << endl;
    cout << setw(40) << " " << "   only three special character i.e. \'.\', \',\' and \'?\' " << "\n\n";

    cout << setw(40) << " " << "2. Press \'=\' to save the file." << "\n\n";

    cout << setw(40) << " " << "3. Press \'\\\' to move to next suggestion." << "\n\n";

    cout << setw(40) << " " << "4. Press \';\' to select the suggestion." << "\n\n\n\n";

    cout << setw(57) << " " << "Press any key to continue";
    _getch();


}

void end_screen()
{
    cout << end_header << "\n\n\n\n\n";

    cout << setw(60) << " " << "Press any key to exit";
    _getch();

    cout << "\n\n\n\n\n\n\n\n\n\n\n";
}

char menu()
{
    char option;

    cout << smol_header;
    cout << setw(60) << " " << "--- MENU ---\n\n\n";

    cout << setw(60) << " " << "1. New File" << endl;
    cout << setw(60) << " " << "2. Open File" << endl;
    cout << setw(60) << " " << "3. Exit" << endl;

    cout << "\n\n\n" << setw(58) << " " << "[+] Select any option";
    do
    {
        // keeps getting input until valid input is entered;
        option = _getch();

    } while (option < '1' || option > '3');

    return option;
}

int main()
{
    Trie_Tree trie_tree;
    LLQueueADT allText;

    int option;
    char input = ' ';
    string file_name, data = "";
    char_int_array char_count;


    trie_tree.read_from_file();

    start_screen();

    instructions();

    // keeps the app running until exit is selected
    do
    {
        system("cls");
        option = menu();

        system("cls");
        switch (option)
        {
        case '1':
            cout << setw(20) << "--- NEW FILE ---";

            cout << "\n\n\nEnter file name: ";
            getline(cin, file_name);

            // removes whitespaces
            file_name.erase(std::remove_if(file_name.begin(), file_name.end(), ::isspace), file_name.end());


            if (CheckFileExist(file_name))
            {
                cout << "\n\n\n[!]ERROR: File already exists.\n\n";
                cout << "[+]INSTRUCTION: Please, use the OPEN FILE option.";

            }
            else
            {
                system("cls");
                cout << setw(60) << " " << "--- " << file_name << ".txt ---" << setw(30) << "Press \'=\' to save file" << " \n\n\n";
                WritingModule(file_name, allText, trie_tree, char_count);
            }

            break;

        case '2':

            cout << setw(20) << "--- OPEN FILE ---";

            cout << "\n\n\nEnter file name: ";
            getline(cin, file_name);

            // removes whitespaces
            file_name.erase(std::remove_if(file_name.begin(), file_name.end(), ::isspace), file_name.end());

            if (CheckFileExist(file_name))
            {
                ReadTextFromFile(file_name, allText, char_count);

                system("cls");
                cout << setw(60) << " " << "--- " << file_name << ".txt ---" << setw(30) << "Press \'=\' to save file" << " \n\n\n";
                WritingModule(file_name, allText, trie_tree, char_count);
            }
            else
            {
                cout << "\n\n\n[!]ERROR: File does not exist." << endl;
            }

            break;

        case '3':
            end_screen();
            exit(1);

        default:
            break;
        }

        cout << "\n\n\n\nPress ENTER to continue";
        _getch();

    } while (true);

    return 0;
}