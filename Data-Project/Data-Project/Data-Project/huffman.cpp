#include <iostream>
using namespace std;

struct huffman_nodes
{
    char character;
    int freq;
    huffman_nodes* left;
    huffman_nodes* right;
};


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

    void min_heapify(huffman_nodes **arr, int size, int i)
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

    void heapify_up(huffman_nodes **arr, int size, int i)
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
        arr = new huffman_nodes*[size];

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
        huffman_nodes *l, *r, *new_node;
        
        while (!is_one())
        {
            l = getMin();
            extractMin();

            r = getMin();
            extractMin();

            new_node = new huffman_nodes;

            new_node->character = '$';
            new_node->freq = l->freq + r->freq;
            new_node->left = l;
            new_node->right = r;

            insert_node(new_node);
            
        }
        
        return getMin();
    }

    
};

void printHuffmanCode(huffman_nodes* root, string code = "")
{
    if (!root)
        return;

    if (root->left == NULL && root->right == NULL)
        cout << root->character << " : " << code << endl;


    printHuffmanCode(root->right, code + "1");
    printHuffmanCode(root->left, code + "0");
}



int main()
{
    min_heap huffman(26);
    huffman_nodes* huffman_tree;

    huffman.insert('a' ,5);
    huffman.insert('b' ,9);
    huffman.insert('c' ,12);
    huffman.insert('d' ,13);
    huffman.insert('e' ,16);
    huffman.insert('f' ,45);


    huffman_tree = huffman.huffman_coding();

    //cout << "\n\n" << huffman_tree->right->right->freq << endl;

    printHuffmanCode(huffman_tree);
}

